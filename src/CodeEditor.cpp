#include <QFile>
#include <QFileInfo>

#include <QMenu>
#include <QMessageBox>

#include "CodeEditor.h"

CodeEditor::CodeEditor(QWidget *parent)
: QTabWidget(parent)
{
  setTabsClosable(true);
  connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabClosed(int)));
}

CodeEditor::~CodeEditor() {}

void CodeEditor::onTabClosed(int index)
{
  QWidget*	tabItem;

  if (index == -1)
    return;
  tabItem = widget(index);
  removeTab(index);
  tabItem->deleteLater();
}

void CodeEditor::onTabCodeTouched()
{
  QWidget*	widget = qobject_cast<QWidget*>(sender());
  int		index;

  if (!widget)
    return ;
  if ((index = indexOf(widget)) == -1)
    return ;
  setTabIcon(index, QIcon(":/document-save.png"));
}

void CodeEditor::closeCurrentTab()
{
  onTabClosed(currentIndex());
}

void CodeEditor::save()
{
  saveTab(currentIndex());
}

void CodeEditor::saveAll()
{
  for (int i = 0; i < count(); ++i)
    saveTab(i);
}

void CodeEditor::openFile(const QString& file)
{
  QFile*	f = new QFile(file);
  QFileInfo	info(*f);

  for (int i = 0; i < count(); ++i)
  {
    if ((qobject_cast<CodeWidget*>(widget(i)))->getFilename() == file)
    {
      setCurrentIndex(i);
      return ;
    }
  }
  if (!info.exists())
  {
    QMessageBox::warning(this, tr("Error"), tr("Could not open: ") + file, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    return ;
  }
  if (!f->open(QIODevice::ReadWrite | QIODevice::Text))
    return ;
  CodeWidget* tab = new CodeWidget(file, this);
  connect(tab, SIGNAL(onCodeTouched()), this, SLOT(onTabCodeTouched()));

  tab->setText(f->readAll());
  tab->setModifiedState(false);
  addTab(tab, info.fileName());
  setCurrentWidget(tab);
}

void CodeEditor::saveTab(int index)
{
  CodeWidget*	tabWidget = qobject_cast<CodeWidget*>(widget(index));

  if (!tabWidget)
    return ;
  tabWidget->setModifiedState(false);
  setTabIcon(index, QIcon());
}

#include "CodeEditor.moc"
