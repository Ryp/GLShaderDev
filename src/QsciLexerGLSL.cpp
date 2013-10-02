#include <qsciscintilla.h>
#include <QDebug>

#include "QsciLexerGLSL.h"

QsciLexerGLSL::QsciLexerGLSL(QObject *parent)
: QsciLexerCustom(parent)
{
  _styles[Default] = QsciStyle(Default);
  _styles[Default].setDescription("Default");
  _styles[Default].setFont(defaultFont(0));

  _styles[Comment] = QsciStyle(Comment);
  _styles[Comment].setDescription("Comment");
  _styles[Comment].setColor("#888888");
  _styles[Comment].setFont(defaultFont(0));

  _styles[GLKeyword] = QsciStyle(GLKeyword);
  _styles[GLKeyword].setDescription("GLKeyword");
  _styles[GLKeyword].setFont(defaultFont(0));
}

QsciLexerGLSL::~QsciLexerGLSL() {}

const char* QsciLexerGLSL::language() const
{
  return ("GLSL");
}

QString QsciLexerGLSL::description(int style) const
{
  if (style < 0 || style >= MaxStyle)
    style = 0;
  return (_styles.at(style).description());
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

    qDebug() << "Styling" << len << "bytes" << description(style);
    setStyling(len, style);
    if (i < list.size() - 1)
      setStyling(1, Default); // Newline char style
  }
}

QFont QsciLexerGLSL::defaultFont(int style) const
{
  QFont	ft;

  static_cast<void>(style);
  ft.setFamily("Monospace");
  ft.setPointSize(9);
  return (ft);
}

QColor QsciLexerGLSL::color(int style) const
{
  if (style < 0 || style >= MaxStyle)
    style = 0;
  return (_styles.at(style).color());
}

QFont QsciLexerGLSL::font(int style) const
{
  if (style < 0 || style >= MaxStyle)
    style = 0;
  return (_styles.at(style).font());
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
