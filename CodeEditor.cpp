#include "CodeEditor.h"
#include <iostream>
#include <QFile>
#include <QFileInfo>

CodeEditor::CodeEditor(QWidget *parent)
: QTabWidget(parent)
{
  setTabsClosable(true);
  _codeWidget = new CodeWidget(this);

  addTab(_codeWidget, "Code");
}

CodeEditor::~CodeEditor() {}

void CodeEditor::openFile(const QString& file)
{
  QFile* f = new QFile(file);
  QFileInfo info(*f);
  if (!f->open(QIODevice::ReadWrite | QIODevice::Text))
    std::cout << "LOLZ.." << std::endl;
  CodeWidget* tab = new CodeWidget(this);
  tab->setText(f->readAll());
  addTab(tab, info.fileName());
}

#include "CodeEditor.moc"
