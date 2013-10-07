#include <iostream> // FIXME

#include "CodeWidget.h"
#include "QsciLexerGLSL.h"

CodeWidget::CodeWidget(const QString& filename, QWidget *parent)
: QsciScintilla(parent),
  _filename(filename)
{
  QFont font = this->font();
  font.setFamily("Monospace");
  setFont(font);
  setMarginsFont(font);
  setMarginLineNumbers(0, true);
  setSelectionToEol(true);
  setCaretWidth(2);

/*SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 0);
  SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 0);
  SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 1);
  SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 1);*/

  QsciLexer* lexer = new QsciLexerGLSL(this);
  lexer->setDefaultFont(font);
  lexer->setFont(font);

  setLexer(lexer);

  connect(this, SIGNAL(linesChanged()), this, SLOT(onLinesChanged()));
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

void CodeWidget::onLinesChanged()
{
  setMarginWidth(0, fontMetrics().width(QString::number(lines())) + 6);
}

#include "CodeWidget.moc"
