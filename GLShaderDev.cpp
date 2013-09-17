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
  resize(600, 600);
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
  QAction* quitAction = new QAction(this);
  quitAction->setText("Quit");
  quitAction->setShortcut(tr("Ctrl+Q"));
  connect(quitAction, SIGNAL(triggered()), SLOT(close()));

  QAction* openAction = new QAction(this);
  openAction->setText("Open...");
  openAction->setShortcut(tr("Ctrl+O"));
  connect(openAction, SIGNAL(triggered()), SLOT(open()));

  QMenu* menu = menuBar()->addMenu("File");
  menu->addAction(openAction);
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

void GLShaderDev::open()
{
  QString fileName = QFileDialog::getOpenFileName();

  if (!fileName.isEmpty())
  {
    _editor->openFile(fileName);
  }
}

void GLShaderDev::onTabClosed(int index)
{
  if (index == -1)
    return;

  QWidget* tabItem = _editor->widget(index);
  // Removes the tab at position index from this stack of widgets.
  // The page widget itself is not deleted.
  _editor->removeTab(index);
}

#include "GLShaderDev.moc"
