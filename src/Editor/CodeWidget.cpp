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
  apis->add("void");
  apis->add("bool");
  apis->add("int");
  apis->add("uint");
  apis->add("float");
  apis->add("double");

  apis->add("vec2");
  apis->add("vec3");
  apis->add("vec4");
  apis->add("dvec2");
  apis->add("dvec3");
  apis->add("dvec4");
  apis->add("bvec2");
  apis->add("bvec3");
  apis->add("bvec4");
  apis->add("ivec2");
  apis->add("ivec3");
  apis->add("ivec4");
  apis->add("uvec2");
  apis->add("uvec3");
  apis->add("uvec4");

  apis->add("mat2");
  apis->add("mat3");
  apis->add("mat4");
  apis->add("mat2x2");
  apis->add("mat2x3");
  apis->add("mat2x4");
  apis->add("mat3x2");
  apis->add("mat3x3");
  apis->add("mat3x4");
  apis->add("mat4x2");
  apis->add("mat4x3");
  apis->add("mat4x4");

  apis->add("dmat2");
  apis->add("dmat3");
  apis->add("dmat4");
  apis->add("dmat2x2");
  apis->add("dmat2x3");
  apis->add("dmat2x4");
  apis->add("dmat3x2");
  apis->add("dmat3x3");
  apis->add("dmat3x4");
  apis->add("dmat4x2");
  apis->add("dmat4x3");
  apis->add("dmat4x4");

  apis->add("sampler1D");
  apis->add("image1D");
  apis->add("sampler2D");
  apis->add("image2D");
  apis->add("sampler3D");
  apis->add("image3D");
  apis->add("samplerCube");
  apis->add("imageCube");
  apis->add("sampler2DRect");
  apis->add("image2DRect");
  apis->add("sampler1DArray");
  apis->add("image1DArray");
  apis->add("sampler2DArray");
  apis->add("image2DArray");
  apis->add("samplerBuffer");
  apis->add("imageBuffer");
  apis->add("sampler2DMS");
  apis->add("image2DMS");
  apis->add("sampler2DMSArray");
  apis->add("image2DMSArray");
  apis->add("samplerCubeArray");
  apis->add("imageCubeArray");
  apis->add("sampler1DShadow");
  apis->add("sampler2DShadow");
  apis->add("sampler2DRectShadow");
  apis->add("sampler1DArrayShadow");
  apis->add("sampler2DArrayShadow");
  apis->add("samplerCubeShadow");
  apis->add("samplerCubeArrayShadow");

  apis->add("isampler2D");
  apis->add("iisam2D");
  apis->add("isampler3D");
  apis->add("iisam3D");
  apis->add("isamplerCube");
  apis->add("iisamCube");
  apis->add("isampler2DRect");
  apis->add("iisam2DRect");
  apis->add("isampler1DArray");
  apis->add("iisam1DArray");
  apis->add("isampler2DArray");
  apis->add("iisam2DArray");
  apis->add("isamplerBuffer");
  apis->add("iisamBuffer");
  apis->add("isampler2DMS");
  apis->add("iisam2DMS");
  apis->add("isampler2DMSArray");
  apis->add("iisam2DMSArray");
  apis->add("isamplerCubeArray");
  apis->add("iisamCubeArray");

  apis->add("const");
  apis->add("in");
  apis->add("out");
  apis->add("attribute");
  apis->add("uniform");
  apis->add("varying");
  apis->add("buffer");
  apis->add("shared");

  //AuxiliaryQualifierStorage

  apis->add("dot");
  apis->add("mix");
  apis->add("pow");
  apis->add("fma");
  apis->add("sqrt");
  apis->add("log");
  apis->add("log2");
  apis->add("exp");
  apis->add("exp2");

  apis->add("radians");
  apis->add("degrees");
  apis->add("sin");
  apis->add("cos");
  apis->add("tan");
  apis->add("asin");
  apis->add("acos");
  apis->add("atan");

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
