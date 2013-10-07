#include "CodeWidget.h"
#include "QsciLexerGLSL.h"

CodeWidget::CodeWidget(const QString& filename, QWidget *parent)
: QsciScintilla(parent),
  _filename(filename),
  _lexer(new QsciLexerGLSL(this))
{
  QFont font = this->font();
  font.setFamily("Monospace");

  setFont(font);
  setMarginsFont(font);
  setMarginLineNumbers(0, true);
  setSelectionToEol(true);
  setCaretWidth(2);
  setTabWidth(2);
  setCaretLineVisible(true);
  setCaretLineBackgroundColor(QColor(0xf8, 0xf8, 0xf8));

  _lexer->setDefaultFont(font);
  _lexer->setFont(font);
  setLexer(_lexer);

  connect(this, SIGNAL(linesChanged()), this, SLOT(onLinesChanged()));
}

CodeWidget::~CodeWidget() {}

const QString& CodeWidget::getFilename() const
{
  return (_filename);
}

void CodeWidget::onLinesChanged()
{
  setMarginWidth(0, fontMetrics().width(QString::number(lines())) + 6);
}

#include "CodeWidget.moc"
