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
#include <QListWidget>

#include "CodeEditor.h"

GLShaderDev::GLShaderDev()
: _editor(new CodeEditor(this))
{
  resize(600, 800);
  setCentralWidget(_editor);
  QAction* a = new QAction(this);
  a->setText("Quit");
  a->setShortcut(tr("Ctrl+Q"));
  connect(a, SIGNAL(triggered()), SLOT(close()));

  QAction* b = new QAction(this);
  b->setText("Open...");
  b->setShortcut(tr("Ctrl+O"));
  connect(b, SIGNAL(triggered()), SLOT(open()));

  QMenu* menu = menuBar()->addMenu("File");
  menu->addAction(b);
  menu->addAction(a);

  connect(_editor, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabClosed(int)));

  statusBar()->showMessage("5sec Random message", 5000);

  QDockWidget *compile = new QDockWidget(tr("Build log"), this);
  compile->setAllowedAreas(Qt::BottomDockWidgetArea);
  compile->setFeatures(QDockWidget::DockWidgetVerticalTitleBar | (compile->features() & ~QDockWidget::DockWidgetFloatable));
  QTreeWidget* list = new QTreeWidget(this);
//   new QTreeWidgetItem(tr("Oak"), list);
//   new QTreeWidgetItem(tr("BItch"), list);

  compile->setWidget(list);

  addDockWidget(Qt::BottomDockWidgetArea, compile);
  QDockWidget *dockWidget = new QDockWidget(tr("OpenGL View"), this);
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setWidget(new QListWidget(this));
  addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}

GLShaderDev::~GLShaderDev() {}

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
