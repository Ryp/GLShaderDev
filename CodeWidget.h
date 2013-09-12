#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <qt4/Qsci/qsciscintilla.h>

class CodeWidget : public QsciScintilla
{
  Q_OBJECT
public:
  CodeWidget(QWidget *parent = 0);
  ~CodeWidget();

public slots:
  void	onTextChanged();
};

#endif // CODEWIDGET_H
