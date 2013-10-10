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

#include "GLShaderDev.h"
#include "CodeEditor.h"
#include "BuildOutput.h"
#include "OpenGLWidget.h"

GLShaderDev::GLShaderDev()
: _editor(new CodeEditor(this)),
  _output(new BuildOutput(this))
{
  resize(1000, 800); // FIXME set sizeHint instead of hardcoding it
  setWindowIcon(QIcon(":/glsd-icon.png"));
  setCentralWidget(_editor);

  initializeOpenGL();
  initializeActions();
  initializeDockWidgets();

  openFile("/home/ryp/Dev/C++/GLShaderDev/rc/shader/simple.vert"); // FIXME Debug only
  openFile("/home/ryp/Dev/C++/GLShaderDev/rc/shader/simple.frag"); // FIXME Debug only
}

GLShaderDev::~GLShaderDev() {}

void GLShaderDev::initializeOpenGL()
{
  QGLFormat	glFormat;

  glFormat.setVersion(4, 2);
  glFormat.setProfile(QGLFormat::CoreProfile);
  glFormat.setSampleBuffers(true);
  _glview = new OpenGLWidget(glFormat, this);
}

void GLShaderDev::initializeActions()
{
  QMenu* recent;
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(QIcon(":/document-new.png"), tr("&New..."), this, SLOT(newFile()), QKeySequence::New);
  fileMenu->addAction(QIcon(":/document-open.png"), tr("&Open..."), this, SLOT(openFileDialog()), QKeySequence::Open);
  recent = fileMenu->addMenu(QIcon(":/document-open-recent.png"), tr("Open &Recent"));

  for (int i = 0; i < MaxRecentFiles; ++i)
    (_recentFileActions[i] = recent->addAction(tr("<Empty>"), this, SLOT(openRecentFile())))->setVisible(true);
  (_recentFileActions[MaxRecentFiles] = recent->addSeparator())->setVisible(true);
  (_recentFileActions[MaxRecentFiles + 1] = recent->addAction(tr("&Clear List"), this, SLOT(clearFileRecent())))->setEnabled(false);
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

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(QIcon(":/glsd-icon.png"), tr("&About GLShaderDev"), this, SLOT(about()));
  helpMenu->addAction(QIcon(":/qt-icon.png"), tr("About &Qt"), qApp, SLOT(aboutQt()));
}

void GLShaderDev::initializeDockWidgets()
{
  QDockWidget *dockWidget = new QDockWidget(tr("OpenGL View"), this);
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setWidget(_glview);
  addDockWidget(Qt::RightDockWidgetArea, dockWidget);
  dockWidget->setFloating(true);

  _buildOutputDock = new QDockWidget(tr("Build log"), this);
  _buildOutputDock->setAllowedAreas(Qt::BottomDockWidgetArea);
  _buildOutputDock->setFeatures(QDockWidget::DockWidgetVerticalTitleBar | _buildOutputDock->features());
  _buildOutputDock->setWidget(_output);
  addDockWidget(Qt::BottomDockWidgetArea, _buildOutputDock);
  _buildOutputDock->hide();
}

void GLShaderDev::updateRecentFiles()
{
  QSettings	settings;
  QStringList	recentFiles = settings.value("recentFiles").toStringList();
  int		listLength = std::min(recentFiles.count(), static_cast<int>(MaxRecentFiles));

  for (int i = 0; i < MaxRecentFiles; ++i)
  {
    if (i < listLength)
    {
      _recentFileActions[i]->setText(tr("&%1 %2 [%3]").arg(i + 1).arg(QFileInfo(recentFiles[i]).fileName()).arg(recentFiles[i]));
      _recentFileActions[i]->setData(recentFiles[i]);
    }
    _recentFileActions[i]->setVisible((i < listLength));
  }
  _recentFileActions[MaxRecentFiles]->setVisible((listLength > 0));
  _recentFileActions[MaxRecentFiles + 1]->setEnabled((listLength > 0));
}

void GLShaderDev::addRecentFile(const QString& filename)
{
  QSettings	settings;
  QStringList	recentFiles = settings.value("recentFiles").toStringList();

  recentFiles.removeAll(filename);
  recentFiles.prepend(filename);
  while (recentFiles.size() > MaxRecentFiles)
    recentFiles.removeLast();
  settings.setValue("recentFiles", recentFiles);
  updateRecentFiles();
}

void GLShaderDev::openFile(const QString& filename)
{
  if (!filename.isEmpty())
  {
    _editor->openFile(filename);
    addRecentFile(filename);
  }
}

void GLShaderDev::closeEvent(QCloseEvent* event)
{
  static_cast<void>(event);
  // FIXME Save opened tabs for next execution
  _editor->closeAllTabs();
  std::cout << "Closing app..." << std::endl;
  // TODO
}

void GLShaderDev::newProject()
{
  // TODO
}

void GLShaderDev::openProject()
{
  // TODO
}

void GLShaderDev::clearProjectRecent()
{
  // TODO
}

void GLShaderDev::closeProject()
{
  // TODO
}

void GLShaderDev::newFile()
{
  // TODO
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
  // TODO
}

void GLShaderDev::buildCurrentProject()
{
  QMutexLocker	sl(&_buildMutex);

  _buildOutputDock->setVisible(true);
  //TODO
}

void GLShaderDev::about()
{
  QMessageBox::about(this, tr("About GLShaderDev"), tr("<b>GLShaderDev</b> is a GLSL shader editor"));
}

#include "GLShaderDev.moc"
