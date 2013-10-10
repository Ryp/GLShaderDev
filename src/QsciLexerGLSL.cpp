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

#include <qsciscintilla.h>
#include <QDebug>

#include "QsciLexerGLSL.h"

QsciLexerGLSL::QsciLexerGLSL(QObject *parent)
: QsciLexerCustom(parent)
{
  _defaultFont.setFamily("Monospace");
  _defaultFont.setPointSize(9);
  QFont ft(_defaultFont);

  ft.setBold(true);

  _styles[Default] = QsciStyle(Default);
  _styles[Default].setDescription("Default");
  _styles[Default].setFont(defaultFont(0));

  _styles[Comment] = QsciStyle(Comment);
  _styles[Comment].setDescription("Comment");
  _styles[Comment].setColor("#888888");
  _styles[Comment].setFont(defaultFont(0));

  _styles[Keyword] = QsciStyle(Keyword);
  _styles[Keyword].setDescription("Keyword");
  _styles[Keyword].setFont(ft);

  _styles[Operator] = QsciStyle(Operator);
  _styles[Operator].setDescription("Operator");
  _styles[Operator].setColor("#2288ff");
  _styles[Operator].setFont(ft);

}

QsciLexerGLSL::~QsciLexerGLSL() {}

const char* QsciLexerGLSL::language() const
{
  return ("GLSL");
}

// const char* QsciLexerGLSL::lexer() const
// {
//   return ("cpp");
// }

QStringList QsciLexerGLSL::autoCompletionWordSeparators() const
{
  QStringList	cws;

  cws << ".";
  return (cws);
}

const char *QsciLexerGLSL::blockStartKeyword(int *style) const
{
  if (style)
    *style = Keyword;
  return ("case catch class default do else for if while");
}

const char *QsciLexerGLSL::blockStart(int *style) const
{
  if (style)
    *style = Operator;
  return ("{");
}

const char *QsciLexerGLSL::blockEnd(int *style) const
{
  if (style)
    *style = Operator;
  return ("}");
}

int QsciLexerGLSL::braceStyle() const
{
  return (Operator);
}

void QsciLexerGLSL::styleText(int start, int end)
{
  char* range = new char[end - start + 1];
  editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, range);
  QString text(range);
  delete range;

  startStyling(start);

  QStringList list = text.split("\n");

  for (int i = 0; i < list.size(); i++)
  {
    QString	line = list.at(i);
    int		len = line.size();
    int		style;

    if (line.startsWith("//"))
      style = Comment;
    else
      style = Default;

//     qDebug() << "Styling" << len << "bytes" << description(style);
    setStyling(len, style);
    if (i < list.size() - 1)
      setStyling(1, Default); // Newline char style
  }
}

QString QsciLexerGLSL::description(int style) const
{
  if (style < 0 || style >= MaxStyle)
    style = 0;
  return (_styles.at(style).description());
}

QFont QsciLexerGLSL::defaultFont(int style) const
{
  if (style < 0 || style >= MaxStyle)
    style = 0;
  return (_styles.at(style).font());
}

QColor QsciLexerGLSL::defaultColor(int style) const
{
  if (style < 0 || style >= MaxStyle)
    style = 0;
  return (_styles.at(style).color());
}

QColor QsciLexerGLSL::defaultPaper(int style) const
{
  return QsciLexer::defaultPaper(style);
}

bool QsciLexerGLSL::defaultEolFill(int style) const
{
  return QsciLexer::defaultEolFill(style);
}

const char* QsciLexerGLSL::keywords(int set) const
{
  static_cast<void>(set);
  return ("in out varying uniform");
}

const char* QsciLexerGLSL::wordCharacters() const
{
  return ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");
}

QsciLexerGLSL::QsciLexerGLSL(const QsciLexerGLSL& other)
: QsciLexerCustom()
{
  static_cast<void>(other);
}

QsciLexerGLSL& QsciLexerGLSL::operator=(const QsciLexerGLSL& other)
{
  static_cast<void>(other);
  return (*this);
}

#include "QsciLexerGLSL.moc"
