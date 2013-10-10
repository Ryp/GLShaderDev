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

#include <iostream>

#include <QFile>
#include <QFileInfo>

#include <QMenu>
#include <QMessageBox>

#include "CodeEditor.h"

CodeEditor::CodeEditor(QWidget *parent)
: QTabWidget(parent)
{
  setTabsClosable(true);
  connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

CodeEditor::~CodeEditor() {}

void CodeEditor::onTabCodeSavePointLeft()
{
  QWidget*	senderWidget = qobject_cast<QWidget*>(sender());
  int		index;

  if ((index = indexOf(senderWidget)) == -1)
    return ;
  setTabIcon(index, QIcon(":/document-save.png"));
}

void CodeEditor::onTabCodeSavePointReached()
{
  QWidget*	senderWidget = qobject_cast<QWidget*>(sender());
  int		index;

  if ((index = indexOf(senderWidget)) == -1)
    return ;
  setTabIcon(index, QIcon());
}

void CodeEditor::closeTab(int index)
{
  CodeWidget*	tabItem;
  int		ret;

  if (index == -1)
    return ;
  if ((tabItem = qobject_cast<CodeWidget*>(widget(index))) == 0)
    return ;
  if (tabItem->isModified())
  {
    if ((ret = QMessageBox::warning(this, tr("Close Document") + " - " + tr("GLShaderDev"), tr("The document \"%1\" has unsaved changes. Would you like to save them?").arg(tabItem->getFilename()), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel)) == QMessageBox::Cancel)
      return ;
    else if (ret == QMessageBox::Yes)
      saveTab(index);
  }
  removeTab(index);
  tabItem->deleteLater();
}

void CodeEditor::closeCurrentTab()
{
  closeTab(currentIndex());
}

void CodeEditor::closeAllTabs()
{
  while (count() > 0)
    closeTab(currentIndex());
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

  connect(tab, SIGNAL(SCN_SAVEPOINTLEFT()), this, SLOT(onTabCodeSavePointLeft()));
  connect(tab, SIGNAL(SCN_SAVEPOINTREACHED()), this, SLOT(onTabCodeSavePointReached()));

  tab->setText(f->readAll());
  f->close();

  tab->SendScintilla(QsciScintilla::SCI_SETSAVEPOINT);

  addTab(tab, info.fileName());
  setCurrentWidget(tab);
}

void CodeEditor::saveTab(int index)
{
  CodeWidget*	tabWidget = qobject_cast<CodeWidget*>(widget(index));

  if (!tabWidget)
    return ;
  if (!tabWidget->isModified())
    return ;

  std::cout << "File saved" << std::endl;
  tabWidget->SendScintilla(QsciScintilla::SCI_SETSAVEPOINT);
}

#include "CodeEditor.moc"
