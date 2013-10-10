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

#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <Qsci/qsciscintilla.h>
#include <QString>

class QsciLexer;

class CodeWidget : public QsciScintilla
{
  Q_OBJECT
public:
  CodeWidget(const QString& filename, QWidget *parent = 0);
  ~CodeWidget();

public:
  const QString&	getFilename() const;

public slots:
  void	onLinesChanged();

private:
  QString	_filename;
  QsciLexer*	_lexer;
};

#endif // CODEWIDGET_H
