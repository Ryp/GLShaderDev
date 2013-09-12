#ifndef SHADERLEXER_H
#define SHADERLEXER_H

#include <Qsci/qscilexercustom.h>

class ShaderLexer : public QsciLexerCustom
{
public:
  ShaderLexer(QObject *parent = 0);
  ~ShaderLexer();

public:
  virtual void styleText(int start, int end);
  virtual QString description(int style) const;
  virtual const char* language() const;
};

#endif // SHADERLEXER_H
