/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#include "CodeWidget.h"
#include "QsciLexerGLSL.h"
#include <QDebug> // FIXME
#include <Qsci/qsciapis.h>
#include <Qsci/qscilexercpp.h>

CodeWidget::CodeWidget(const QString& filename, QWidget *parent)
: QsciScintilla(parent),
  _filename(filename),
  _lexer(new QsciLexerCPP(this)) // FIXME Use custom lexer instead
{
  QFont ft = this->font();
  ft.setFamily("Monospace");


  setFont(ft);
  setMarginsFont(ft);
  setMarginLineNumbers(0, true);
  setSelectionToEol(true);
  setTabWidth(2);
  setCaretWidth(2);
  setCaretLineVisible(true);
  setCaretLineBackgroundColor(QColor(0xf8, 0xf8, 0xf8));

  setFolding(QsciScintilla::PlainFoldStyle);

  setAutoCompletionThreshold(2);
  setAutoCompletionSource(QsciScintilla::AcsAPIs);

  QsciAPIs* apis = new QsciAPIs(_lexer);
  if (!apis->load("../rc/syntax/glsl-4-30-core.kw"))
    qDebug() << "NOT";
  apis->prepare();

  _lexer->setDefaultFont(ft);
  _lexer->setFont(ft);

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
