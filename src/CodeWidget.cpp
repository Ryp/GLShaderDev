#include <iostream> // FIXME

#include "CodeWidget.h"
#include "QsciLexerGLSL.h"

#include <qscilexercpp.h> // FIXME

CodeWidget::CodeWidget(const QString& filename, QWidget *parent)
: QsciScintilla(parent),
  _filename(filename),
  _isModified(false)
{
  QFont font = this->font();
  font.setFamily("Monospace");
  setFont(font);
  setMarginsFont(font);
  setMarginLineNumbers(0, true);
  setSelectionToEol(true);
  setCaretWidth(2);
  
  onTextChanged();

/*SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 0);
  SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 0);
  SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 1);
  SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 1);*/

  QsciLexer* lexer = new QsciLexerGLSL(this);
  lexer->setDefaultFont(font);
  lexer->setFont(font);

  setLexer(lexer);

  connect(this, SIGNAL(linesChanged()), this, SLOT(onLinesChanged()));
  connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
  setTabWidth(2);
}

CodeWidget::~CodeWidget() {}

QString CodeWidget::getCode()
{
  return (text());
}

const QString& CodeWidget::getFilename() const
{
  return (_filename);
}

void CodeWidget::setModifiedState(bool state)
{
  _isModified = state;
}

void CodeWidget::onLinesChanged()
{
  setMarginWidth(0, fontMetrics().width(QString::number(lines())) + 6);
}

void CodeWidget::onTextChanged()
{
  if (_isModified ^ isModified())
  {
    _isModified = !_isModified;
    emit onCodeTouched();
  }
}

#include "CodeWidget.moc"
