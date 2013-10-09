#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QTabWidget>

#include "CodeWidget.h"

class CodeEditor : public QTabWidget
{
  Q_OBJECT
public:
  CodeEditor(QWidget *parent = 0);
  ~CodeEditor();

public slots:
  void	onTabCodeSavePointLeft();
  void	onTabCodeSavePointReached();
  void	closeTab(int index);
  void	closeCurrentTab();
  void	closeAllTabs();
  void	save();
  void	saveAll();

public:
  void	openFile(const QString& file);

private:
  void	saveTab(int index);

private:
  CodeWidget*	_codeWidget;
};

#endif // CODEEDITOR_H
