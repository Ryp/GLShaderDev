#include "ShaderLexer.h"

ShaderLexer::ShaderLexer(QObject *parent)
: QsciLexerCustom(parent)
{}

ShaderLexer::~ShaderLexer() {}

void ShaderLexer::styleText(int start, int end)
{
  static_cast<void>(start);
  static_cast<void>(end);
}

const char* ShaderLexer::language() const
{
  return ("GLSL");
}

QString ShaderLexer::description(int style) const
{
  static_cast<void>(style);
  return ("OpenGL Shading Language");
}
/*
const char *QsciLexerCustom::keywords(int set) const
{
  if (set == 1)
    return
    "and and_eq asm auto bitand bitor bool break case "
    "catch char class compl const const_cast continue "
    "default delete do double dynamic_cast else enum "
    "explicit export extern false float for friend goto if "
    "inline int long mutable namespace new not not_eq "
    "operator or or_eq private protected public register "
    "reinterpret_cast return short signed sizeof static "
    "static_cast struct switch template this throw true "
    "try typedef typeid typename union unsigned using "
    "virtual void volatile wchar_t while xor xor_eq";

  if (set == 3)
    return
    "a addindex addtogroup anchor arg attention author b "
    "brief bug c class code date def defgroup deprecated "
    "dontinclude e em endcode endhtmlonly endif "
    "endlatexonly endlink endverbatim enum example "
    "exception f$ f[ f] file fn hideinitializer "
    "htmlinclude htmlonly if image include ingroup "
    "internal invariant interface latexonly li line link "
    "mainpage name namespace nosubgrouping note overload "
    "p page par param post pre ref relates remarks return "
    "retval sa section see showinitializer since skip "
    "skipline struct subsection test throw todo typedef "
    "union until var verbatim verbinclude version warning "
    "weakgroup $ @ \\ & < > # { }";
  return 0;
}
*/