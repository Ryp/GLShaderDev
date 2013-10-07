#ifndef QSCILEXERGLSL_H
#define QSCILEXERGLSL_H

#include <qscilexercustom.h>
#include <qscistyle.h>

class QsciLexerGLSL : public QsciLexerCustom
{
  Q_OBJECT
public:
  QsciLexerGLSL(QObject *parent = 0);
  ~QsciLexerGLSL();

public:
  const char*	language() const;
//   const char	*lexer() const;
  QStringList	autoCompletionWordSeparators() const;
  const char*	blockStartKeyword(int *style = 0) const;
  const char*	blockStart(int *style = 0) const;
  const char*	blockEnd(int *style = 0) const;
  int		braceStyle() const;
  void		styleText(int start, int end);
  QString	description(int style) const;
  QFont		defaultFont(int style) const;
  QColor	defaultColor(int style) const;
  QColor	defaultPaper(int style) const;
  bool		defaultEolFill(int style) const;
  const char*	keywords(int set) const;
  const char*	wordCharacters() const;

private:
  QsciLexerGLSL(const QsciLexerGLSL& other);
  QsciLexerGLSL& operator=(const QsciLexerGLSL& other);

private:
  enum StyleType {
    Default = 0,
    Comment,
    Keyword,
    Operator,
    MaxStyle
  };

private:
  std::map<int, QsciStyle>	_styles;
  QFont				_defaultFont;
};

#endif // SHADERLEXER_H
