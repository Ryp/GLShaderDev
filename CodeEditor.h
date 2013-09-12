#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <qt4/QtGui/QTabWidget>
#include "CodeWidget.h"

class CodeEditor : public QTabWidget
{
  Q_OBJECT
public:
  CodeEditor(QWidget *parent = 0);
  ~CodeEditor();

public:
  void	openFile(const QString& file);

private:
  CodeWidget*	_codeWidget;
};

#endif // CODEEDITOR_H
