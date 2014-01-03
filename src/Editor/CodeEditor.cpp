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

#include <QFile>
#include <QFileInfo>
#include <QKeyEvent>
#include <QMessageBox>

#include "CodeEditor.h"
#include "Exceptions/GlsdException.hpp"

CodeEditor::CodeEditor(QWidget *parent)
: QTabWidget(parent)
{
  setTabsClosable(true);
  setMovable(true);
  connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

CodeEditor::~CodeEditor() {}

bool CodeEditor::openFile(const QString& file)
{
  QFile*	f = new QFile(file);
  QFileInfo	info(*f);

  for (int i = 0; i < count(); ++i)
  {
    if ((qobject_cast<CodeWidget*>(widget(i)))->getFilename() == file)
    {
      setCurrentIndex(i);
      return (false);
    }
  }
  if (!info.exists())
  {
    QMessageBox::warning(this, tr("Error"), tr("File does not exist: ") + file);
    return (false);
  }
  if (!f->open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QMessageBox::warning(this, tr("Error"), tr("Could not open: ") + f->fileName());
    return (false);
  }

  CodeWidget* tab = new CodeWidget(info.absoluteFilePath(), this);

  connect(tab, SIGNAL(SCN_SAVEPOINTLEFT()), this, SLOT(onTabCodeSavePointLeft()));
  connect(tab, SIGNAL(SCN_SAVEPOINTREACHED()), this, SLOT(onTabCodeSavePointReached()));

  tab->setText(f->readAll());
  f->close();

  tab->SendScintilla(QsciScintilla::SCI_SETSAVEPOINT);

  addTab(tab, info.fileName());
  setCurrentWidget(tab);
  setTabToolTip(currentIndex(), info.absoluteFilePath());
  return (true);
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

void CodeEditor::gotoFile(const QString& file, int line, int column)
{
  CodeWidget*	codeWidgetTab;

  if (!line)
    return;
  --line;
  for (int index = 0; index < count(); ++index)
  {
    if (!(codeWidgetTab = qobject_cast<CodeWidget*>(widget(index))))
      throw GlsdException("Bad widget type");
    if (codeWidgetTab->getFilename() == file)
    {
      focusCode(codeWidgetTab, line, column);
      return;
    }
  }
  // At this point, no matching opened file was found, try to open file
  if (!openFile(file))
    return;
  if (!(codeWidgetTab = qobject_cast<CodeWidget*>(currentWidget())))
    throw GlsdException("Bad widget pointer");
  focusCode(codeWidgetTab, line, column);
}

void CodeEditor::focusCode(CodeWidget* widget, int line, int column)
{
  setCurrentWidget(widget);
  widget->setFocus();
  widget->setCursorPosition(line, column);
}

void CodeEditor::saveTab(int index)
{
  CodeWidget*	tabWidget = qobject_cast<CodeWidget*>(widget(index));

  if (!tabWidget)
    return ;
  if (!tabWidget->isModified())
    return ;

  QFile*	f = new QFile(tabWidget->getFilename());
  QFileInfo	info(*f);

  if (!info.exists())
  {
    QMessageBox::warning(this, tr("Error"), tr("File does not exist: ") + f->fileName());
    return ;
  }
  if (!f->open(QIODevice::WriteOnly | QIODevice::Text))
  {
    QMessageBox::warning(this, tr("Error"), tr("Could not open: ") + f->fileName());
    return ;
  }
  QString	buffer = tabWidget->text();
  qint64	len = buffer.size();

  if (f->write(buffer.toStdString().c_str(), len) == -1)
    throw (GlsdException("QFile::write() failed"));
  f->close();
  std::cout << "File saved: " << tabWidget->getFilename().toStdString() << std::endl; // FIXME Remove debug

  tabWidget->SendScintilla(QsciScintilla::SCI_SETSAVEPOINT);
}

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
