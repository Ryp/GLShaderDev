/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#include <iostream> // FIXME
#include <QSettings>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QFileDialog>
#include <QDockWidget>
#include <QMessageBox>
#include <QSplitter>

#include "GLShaderDev.h"
#include "Editor/CodeEditor.h"
#include "Build/BuildOutput.h"
#include "GL/OpenGLWidget.h"
#include "Dialog/NewFileDialog.h"
#include "Dialog/GLInfoDialog.h"
#include "ShaderStagesView.h"
#include "Exceptions/GlsdException.hpp"
#include "ShaderInputView.h"
#include "Build/OutputParser.h"
#include "Build/OutputModel.h"
#include "GL/Shader/ShaderProgram.h"
#include "GL/GLPreviewWidget.h"

GLShaderDev::GLShaderDev()
: _editor(new CodeEditor(this)),
  _output(new BuildOutput(this)),
  _glInfoDialog(0),
  _newFileDialog(new NewFileDialog(this))
{
  resize(1000, 800); // FIXME set sizeHint instead of hardcoding it
  setWindowIcon(QIcon(":/glsd-icon.png"));
  setCentralWidget(_editor);

  initializeContext();
  initializeActions();
  initializeDockWidgets();

  openFile(QFile("../rc/shader/light.v.glsl").fileName()); // FIXME Debug only
  openFile(QFile("../rc/shader/light.f.glsl").fileName()); // FIXME Debug only
}

GLShaderDev::~GLShaderDev() {}

void GLShaderDev::initializeContext()
{
  QGLFormat	glFormat;

  glFormat.setVersion(4, 2);
  glFormat.setProfile(QGLFormat::CoreProfile);
  glFormat.setSampleBuffers(true); // NOTE this option activates MSAA
  glFormat.setDoubleBuffer(true);

  _glpreview = new GLPreviewWidget(glFormat);
  _glwidget = _glpreview->getGLWidget();

  connect(_glwidget, SIGNAL(glInitialized()), this, SLOT(initGLInfo()));
}

void GLShaderDev::initializeActions()
{
  QSettings	settings;

  QMenu* recent;
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(QIcon(":/document-new.png"), tr("&New..."), _newFileDialog, SLOT(exec()), QKeySequence::New);
  connect(_newFileDialog, SIGNAL(accepted()), this, SLOT(newFile()));
  fileMenu->addAction(QIcon(":/document-open.png"), tr("&Open..."), this, SLOT(openFileDialog()), QKeySequence::Open);
  recent = fileMenu->addMenu(QIcon(":/document-open-recent.png"), tr("Open &Recent"));

  for (int i = 0; i < settings.value("maxRecentFiles").toInt(); ++i)
    (_recentFileActions[i] = recent->addAction(tr("<Empty>"), this, SLOT(openRecentFile())))->setVisible(true);
  (_recentFileActions[settings.value("maxRecentFiles").toInt()] = recent->addSeparator())->setVisible(true);
  (_recentFileActions[settings.value("maxRecentFiles").toInt() + 1] = recent->addAction(tr("&Clear List"), this, SLOT(clearFileRecent())))->setEnabled(false);
  updateRecentFiles();

  fileMenu->addSeparator();
  fileMenu->addAction(QIcon(":/document-save-all.png"), tr("Save Al&l"), _editor, SLOT(saveAll()));
  fileMenu->addAction(QIcon(":/document-save.png"), tr("&Save"), _editor, SLOT(save()), QKeySequence::Save);
  fileMenu->addAction(QIcon(":/document-save-as.png"), tr("Save &As..."), this, SLOT(saveFileAs()), QKeySequence::SaveAs);
  fileMenu->addSeparator();
  fileMenu->addAction(QIcon(":/dialog-close.png"), tr("&Close"), _editor, SLOT(closeCurrentTab()), tr("Ctrl+W"));
  fileMenu->addAction(QIcon(":/dialog-close.png"), tr("Cl&ose All"), _editor, SLOT(closeAllTabs()), tr("Ctrl+Shift+W"));
  fileMenu->addSeparator();
  fileMenu->addAction(QIcon(":/application-exit.png"), tr("&Quit"), this, SLOT(close()), QKeySequence::Quit);

  QMenu* projectMenu = menuBar()->addMenu(tr("&Project"));
  projectMenu->addAction(QIcon(":/project-development-new-template.png"), tr("&New Project"), this, SLOT(newProject()));
  projectMenu->addAction(QIcon(":/project-open.png"), tr("&Open Project..."), this, SLOT(openProject()));
  recent = projectMenu->addMenu(QIcon(":/document-open-recent.png"), tr("Open &Recent"));
  QAction* clearProjectRecentAction = recent->addAction(tr("&Clear List"), this, SLOT(clearProjectRecent()));
  clearProjectRecentAction->setEnabled(false);
  projectMenu->addSeparator();
  projectMenu->addAction(QIcon(":/run-build.png"), tr("&Build Current"), this, SLOT(buildCurrentProject()), tr("F8"));
  projectMenu->addSeparator();
  projectMenu->addAction(QIcon(":/project-development-close.png"), tr("&Close Project"), this, SLOT(closeProject()));

  menuBar()->addMenu("|")->setEnabled(false);

  QMenu* toolsMenu = menuBar()->addMenu(tr("&Tools"));
  toolsMenu->addAction(QIcon(":/preferences-other.png"), tr("&OpenGL Info..."), this, SLOT(showGLInfo()));

  QMenu* settingsMenu = menuBar()->addMenu(tr("&Settings"));
  settingsMenu->addAction(QIcon(":/preferences-other.png"), tr("&Preferences"), this, SLOT(showPreferences()));

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(QIcon(":/glsd-icon.png"), tr("&About GLShaderDev"), this, SLOT(about()));
  helpMenu->addAction(QIcon(":/qt-icon.png"), tr("About &Qt"), qApp, SLOT(aboutQt()));
}

void GLShaderDev::initializeDockWidgets()
{
  QSplitter*		splitter = new QSplitter;
  QTabWidget*		optionTab = new QTabWidget;

  _shaderStages = new ShaderStagesView;
  _shaderInput = new ShaderInputView;

  optionTab->setMovable(true);
  optionTab->addTab(_shaderStages, tr("Build Stages"));
  optionTab->addTab(_shaderInput, tr("Shader Input"));

  splitter->setOrientation(Qt::Vertical);
  splitter->addWidget(_glpreview);
  splitter->addWidget(optionTab);

  QDockWidget *dockWidget = new QDockWidget(tr("OpenGL View"), this);
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setWidget(splitter);
  addDockWidget(Qt::RightDockWidgetArea, dockWidget);
//   dockWidget->setFloating(true); FIXME

  _buildOutputDock = new QDockWidget(tr("Build log"), this);
  _buildOutputDock->setAllowedAreas(Qt::BottomDockWidgetArea);
  _buildOutputDock->setFeatures(QDockWidget::DockWidgetVerticalTitleBar | _buildOutputDock->features());
  _buildOutputDock->setWidget(_output);
  addDockWidget(Qt::BottomDockWidgetArea, _buildOutputDock);
  _buildOutputDock->hide();

  connect(_output, SIGNAL(dereferencableItemActivated(const QString&, int, int)), _editor, SLOT(gotoFile(const QString&, int, int)));
}

void GLShaderDev::updateRecentFiles()
{
  QSettings	settings;
  QStringList	recentFiles = settings.value("recentFiles").toStringList();
  int		listLength = std::min(recentFiles.count(), static_cast<int>(settings.value("maxRecentFiles").toInt()));

  for (int i = 0; i < settings.value("maxRecentFiles").toInt(); ++i)
  {
    if (i < listLength)
    {
      _recentFileActions[i]->setText(tr("&%1 %2 [%3]").arg(i + 1).arg(QFileInfo(recentFiles[i]).fileName()).arg(recentFiles[i]));
      _recentFileActions[i]->setData(recentFiles[i]);
    }
    _recentFileActions[i]->setVisible((i < listLength));
  }
  _recentFileActions[settings.value("maxRecentFiles").toInt()]->setVisible((listLength > 0));
  _recentFileActions[settings.value("maxRecentFiles").toInt() + 1]->setEnabled((listLength > 0));
}

void GLShaderDev::addRecentFile(const QString& filename)
{
  QSettings	settings;
  QStringList	recentFiles = settings.value("recentFiles").toStringList();

  recentFiles.removeAll(filename);
  recentFiles.prepend(filename);
  while (recentFiles.size() > settings.value("maxRecentFiles").toInt())
    recentFiles.removeLast();
  settings.setValue("recentFiles", recentFiles);
  updateRecentFiles();
}

void GLShaderDev::openFile(const QString& filename)
{
  if (filename.isEmpty())
    return;

  QFileInfo	file(filename);

  if (_editor->openFile(file.absoluteFilePath()))
    addRecentFile(file.absoluteFilePath());
}

void GLShaderDev::closeEvent(QCloseEvent* event)
{
  static_cast<void>(event);
  // TODO Save opened tabs for next execution
  _editor->closeAllTabs();
  std::cout << "Closing app..." << std::endl; // TODO
}

void GLShaderDev::newProject()
{
  std::cout << "newProject() not implemented yet" << std::endl; // TODO
}

void GLShaderDev::openProject()
{
  std::cout << "newProject() not implemented yet" << std::endl; // TODO
}

void GLShaderDev::clearProjectRecent()
{
  std::cout << "clearProjectRecent() not implemented yet" << std::endl; // TODO
}

void GLShaderDev::closeProject()
{
  std::cout << "closeProject() not implemented yet" << std::endl; // TODO
}

void GLShaderDev::newFile()
{
  QFile		file(_newFileDialog->getNewFileName());
  QFileInfo	info(file);

  if (info.exists())
    _editor->openFile(info.absoluteFilePath());
  else if (file.open(QIODevice::ReadWrite))
  {
    file.close();
    _editor->openFile(info.absoluteFilePath());
  }
  else
    QMessageBox::warning(this, tr("Error"), tr("Could not create file"));
}

void GLShaderDev::openFileDialog()
{
  openFile(QFileDialog::getOpenFileName());
}

void GLShaderDev::openRecentFile()
{
  QAction*	action = qobject_cast<QAction*>(sender());

  if (action)
    openFile(action->data().toString());
}

void GLShaderDev::clearFileRecent()
{
  QSettings	settings;

  settings.setValue("recentFiles", QStringList());
  updateRecentFiles();
}

void GLShaderDev::saveFileAs()
{
  std::cout << "saveFileAs() not implemented yet" << std::endl; // TODO
}

void GLShaderDev::buildCurrentProject()
{
  ShaderProgram*				prog = new ShaderProgram;
  bool						success = true;
  std::list <std::pair <int, QString > >	stages;
  int						i = 1;
  OutputParser					parser(_glInfo.getVendor());

  _editor->saveAll();
  _output->getModel()->clear();
  _buildOutputDock->setVisible(true);

  stages = _shaderStages->getShaderConfig();
  for (std::list <std::pair <int, QString > >::iterator it = stages.begin(); it != stages.end(); ++it)
  {
    QFile		file(it->second);
    QFileInfo		fileInfo(file);
    ShaderObject*	obj = new ShaderObject;
    QString		str = QString("[%1/%2] Compiling %3...").arg(i).arg(stages.size()).arg(fileInfo.fileName());

    _output->getModel()->addItem(OutputItem(str, OutputItem::InformationItem));
    if (!file.open(QIODevice::ReadOnly))
      throw (GlsdException(std::string("Could not open shader file") + it->second.toStdString())); // TODO proper exception handling
    if (!obj->compile(QString(file.readAll()).toStdString(), static_cast<ShaderObject::ShaderType>(it->first)))
    {
      _output->getModel()->addItems(parser.parse(obj->getErrorLog(), fileInfo.absoluteFilePath().toStdString()));
      success = false;
    }
    prog->attach(*obj);
    ++i;
  }

  _output->getModel()->addItem(OutputItem("Linking shader...", OutputItem::InformationItem));
  if (!prog->link())
  {
    _output->getModel()->addItem(OutputItem(prog->getLog().c_str(), OutputItem::ErrorItem));
    success = false;
  }

  if (!success)
  {
    _output->getModel()->addItem(OutputItem("*** Compilation failed ***", OutputItem::StandardItem));
    return;
  }
  _output->getModel()->addItem(OutputItem("*** Compilation successful ***", OutputItem::StandardItem));
  // FIXME Set shader properly, with attributes correctly bound
  _glwidget->setShader(prog);
}

void GLShaderDev::initGLInfo()
{
  _glInfo.updateInfos();
  _glInfoDialog = new GLInfoDialog(_glInfo, this);
}

void GLShaderDev::showGLInfo()
{
  if (_glInfoDialog)
    _glInfoDialog->show();
}

void GLShaderDev::showPreferences()
{
    _preferencesWidget.show();
}

void GLShaderDev::about()
{
  QMessageBox::about(this, tr("About GLShaderDev"), tr("<b>GLShaderDev</b> is a GLSL shader editor"));
}

