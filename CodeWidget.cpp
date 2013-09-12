#include "CodeWidget.h"
#include "ShaderLexer.h"

#include <qscilexercpp.h> // FIXME

CodeWidget::CodeWidget(QWidget *parent)
: QsciScintilla(parent)
{
  QFont font = this->font();
  font.setFamily("Monospace");
  setFont(font);
  setMarginsFont(font);
  setMarginLineNumbers(0, true);
  onTextChanged();

/*SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 0);
  SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 0);
  SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 1);
  SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 1);*/

  QsciLexer* lexer = new QsciLexerCPP(this);
  lexer->setDefaultFont(font);
  setLexer(lexer);
  connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

  setTabWidth(2);
}

CodeWidget::~CodeWidget() {}

void CodeWidget::onTextChanged()
{
  setMarginWidth(0, fontMetrics().width(QString::number(lines())) + 6);
}

#include "CodeWidget.moc"
