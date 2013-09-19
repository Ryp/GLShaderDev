#include "GLShaderDev.h"

#include <QtCore/QTimer>
#include <QtCore/QSettings>

#include <QtOpenGL/QGLContext>

#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QFileDialog>
#include <QtGui/QDockWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QMessageBox>

#include "CodeEditor.h"
#include "BuildOutput.h"
#include "OpenGLWidget.h"

GLShaderDev::GLShaderDev()
: _editor(new CodeEditor(this)),
  _output(new BuildOutput(this))
{
  resize(1000, 800);
  setWindowIcon(QIcon(":/glsd-icon.png"));

  setCentralWidget(_editor);
  connect(_editor, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabClosed(int)));
  statusBar()->showMessage(tr("5sec Random message"), 5000);

  QGLFormat glFormat;
  glFormat.setVersion(4, 2);
  glFormat.setProfile(QGLFormat::CoreProfile);
  glFormat.setSampleBuffers(true);
  _glview = new OpenGLWidget(glFormat, this);

  initializeActions();
  initializeDockWidgets();
}

GLShaderDev::~GLShaderDev() {}

void GLShaderDev::initializeActions()
{
  QMenu* recent;

  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(QIcon(":/document-new.png"), tr("&New..."), this, SLOT(newFile()), QKeySequence::New);
  fileMenu->addAction(QIcon(":/document-open.png"), tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
  recent = fileMenu->addMenu(QIcon(":/document-open-recent.png"), tr("Open &Recent"));

  for (int i = 0; i < MaxRecentFiles; ++i)
    (_recentFileActions[i] = recent->addAction(tr("..."), this, SLOT(openRecentFile())))->setVisible(true);
  (_recentFileActions[MaxRecentFiles] = recent->addSeparator())->setVisible(true);
  (_recentFileActions[MaxRecentFiles + 1] = recent->addAction(tr("&Clear List"), this, SLOT(clearFileRecent())))->setEnabled(false);
  updateRecentFiles();

  fileMenu->addSeparator();
  fileMenu->addAction(QIcon(":/document-save-all.png"), tr("Save Al&l"), this, SLOT(saveFileAll()), tr("Ctrl+L"));
  fileMenu->addAction(QIcon(":/document-save.png"), tr("&Save"), this, SLOT(saveFile()), QKeySequence::Save);
  fileMenu->addAction(QIcon(":/document-save-as.png"), tr("Save &As..."), this, SLOT(saveFileAs()), QKeySequence::SaveAs);
  fileMenu->addSeparator();
  fileMenu->addAction(QIcon(":/application-exit.png"), tr("&Quit"), this, SLOT(close()), QKeySequence::Quit);

  QMenu* projectMenu = menuBar()->addMenu(tr("&Project"));
  projectMenu->addAction(QIcon(":/project-development-new-template.png"), tr("&New Project"), this, SLOT(newProject()));
  projectMenu->addAction(QIcon(":/project-open.png"), tr("&Open Project..."), this, SLOT(openProject()));
  recent = projectMenu->addMenu(QIcon(":/document-open-recent.png"), tr("Open &Recent"));
  QAction* clearProjectRecentAction = recent->addAction(tr("&Clear List"), this, SLOT(clearProjectRecent()));
  clearProjectRecentAction->setEnabled(false);
  projectMenu->addSeparator();
  projectMenu->addAction(QIcon(":/project-development-close.png"), tr("&Close Project"), this, SLOT(closeProject()));

  menuBar()->addMenu("|")->setEnabled(false);

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(QIcon(":/glsd-icon.png"), tr("&About GLShaderDev"), this, SLOT(about()));
  helpMenu->addAction(QIcon(":/qt-icon.png"), tr("About &Qt"), qApp, SLOT(aboutQt()));
}

void GLShaderDev::initializeDockWidgets()
{
  QDockWidget *compile = new QDockWidget(tr("Build log"), this);
  compile->setAllowedAreas(Qt::BottomDockWidgetArea);
  compile->setFeatures(QDockWidget::DockWidgetVerticalTitleBar | (compile->features() & ~QDockWidget::DockWidgetFloatable));
  compile->setWidget(_output);
  addDockWidget(Qt::BottomDockWidgetArea, compile);

  QDockWidget *dockWidget = new QDockWidget(tr("OpenGL View"), this);
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setWidget(_glview);
  addDockWidget(Qt::RightDockWidgetArea, dockWidget);
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

void GLShaderDev::openFile()
{
  // TODO
  QString fileName = QFileDialog::getOpenFileName();

  if (!fileName.isEmpty())
  {
    _editor->openFile(fileName);
    addRecentFile(fileName);
  }
}

void GLShaderDev::openRecentFile()
{
  QAction*	action = qobject_cast<QAction*>(sender());

  if (action)
    _editor->openFile(action->data().toString());
}

void GLShaderDev::clearFileRecent()
{
  QSettings	settings;

  settings.setValue("recentFiles", QStringList());
  updateRecentFiles();
}

void GLShaderDev::saveFileAll()
{
  // TODO
}

void GLShaderDev::saveFile()
{
  // TODO
}

void GLShaderDev::saveFileAs()
{
  // TODO
}

void GLShaderDev::buildShader()
{
  // TODO
}

void GLShaderDev::onTabClosed(int index)
{
  if (index == -1)
    return;

  QWidget* tabItem = _editor->widget(index);
  _editor->removeTab(index);
  delete tabItem;
}

void GLShaderDev::about()
{
  QMessageBox::about(this, tr("About GLShaderDev"), tr("<b>GLShaderDev</b> is a GLSL shader editor"));
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

void GLShaderDev::addRecentFile(QString filename)
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

#include "GLShaderDev.moc"
