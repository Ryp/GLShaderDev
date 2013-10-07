#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <Qsci/qsciscintilla.h>
#include <QString>

class QsciLexer;

class CodeWidget : public QsciScintilla
{
  Q_OBJECT
public:
  CodeWidget(const QString& filename, QWidget *parent = 0);
  ~CodeWidget();

public:
  const QString&	getFilename() const;

public slots:
  void	onLinesChanged();

private:
  QString	_filename;
  QsciLexer*	_lexer;
};

#endif // CODEWIDGET_H
