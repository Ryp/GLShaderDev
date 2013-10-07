#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <Qsci/qsciscintilla.h>
#include <QString>

class CodeWidget : public QsciScintilla
{
  Q_OBJECT
public:
  CodeWidget(const QString& filename, QWidget *parent = 0);
  ~CodeWidget();

public:
  QString		getCode();
  const QString&	getFilename() const;

public slots:
  void	onLinesChanged();

private:
  QString	_filename;
};

#endif // CODEWIDGET_H
