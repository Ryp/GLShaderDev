#include "GLShaderDev.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QFileDialog>
#include <QtGui/QDockWidget>
#include <QtGui/QTreeWidget>

#include <QtOpenGL/QGLContext>

#include "CodeEditor.h"
#include "BuildOutput.h"
#include "OpenGLWidget.h"

GLShaderDev::GLShaderDev()
: _editor(new CodeEditor(this)),
  _output(new BuildOutput(this))
{
  resize(1000, 800);
  setWindowIcon(QIcon(":/application-icon.png"));

  setCentralWidget(_editor);
  connect(_editor, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabClosed(int)));
  statusBar()->showMessage("5sec Random message", 5000);

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
  QAction* newProjectAction = new QAction(QIcon(":/project-development-new-template.png"), tr("New Project"), this);
  connect(newProjectAction, SIGNAL(triggered()), SLOT(newProject()));

  QAction* openProjectAction = new QAction(QIcon(":/project-open.png"), tr("Open Project..."), this);
  connect(openProjectAction, SIGNAL(triggered()), SLOT(openProject()));

  QAction* newFileAction = new QAction(QIcon(":/document-new.png"), tr("New..."), this);
  newFileAction->setShortcut(tr("Ctrl+N"));
  connect(newFileAction, SIGNAL(triggered()), SLOT(newFile()));

  QAction* openFileAction = new QAction(QIcon(":/document-open.png"), tr("Open..."), this);
  openFileAction->setShortcut(tr("Ctrl+O"));
  connect(openFileAction, SIGNAL(triggered()), SLOT(openFile()));

  QAction* saveFileAction = new QAction(QIcon(":/document-save.png"), tr("Save"), this);
  saveFileAction->setShortcut(tr("Ctrl+S"));
  connect(saveFileAction, SIGNAL(triggered()), SLOT(saveFile()));

  QAction* quitAction = new QAction(QIcon(":/application-exit.png"), tr("Quit"), this);
  quitAction->setShortcut(tr("Ctrl+Q"));
  connect(quitAction, SIGNAL(triggered()), SLOT(close()));

  QMenu* menu;
  menu = menuBar()->addMenu(tr("Project"));
  menu->addAction(newProjectAction);
  menu->addAction(openProjectAction);

  menu = menuBar()->addMenu(tr("File"));
  menu->addAction(newFileAction);
  menu->addAction(openFileAction);
  menu->addAction(saveFileAction);
  menu->addSeparator();
  menu->addAction(quitAction);
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
  }
}

void GLShaderDev::saveFile()
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

#include "GLShaderDev.moc"
