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
  virtual QString	description(int style) const;
  virtual const char*	language() const;
  virtual void		styleText(int start, int end);
  virtual QFont		defaultFont(int style) const;
  virtual QColor	color(int style) const;
  virtual QFont		font(int style) const;

private:
  QsciLexerGLSL(const QsciLexerGLSL& other);
  QsciLexerGLSL& operator=(const QsciLexerGLSL& other);

private:
  enum StyleType {
    Default = 0,
    Comment,
    GLKeyword,
    MaxStyle
  };

private:
  std::map<int, QsciStyle>	_styles;
};

#endif // SHADERLEXER_H
