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
  void			setModifiedState(bool state);

public slots:
  void	onLinesChanged();
  void	onTextChanged();

signals:
  void	onCodeTouched();

private:
  QString	_filename;
  bool		_isModified;
};

#endif // CODEWIDGET_H
