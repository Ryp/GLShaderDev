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

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "Shader/ShaderProgram.h"

#include <QGLWidget>

class OpenGLWidget : public QGLWidget
{
  Q_OBJECT
public:
  OpenGLWidget(const QGLFormat& fmt, QWidget *parent = 0);
  ~OpenGLWidget();

public:
  QSize	sizeHint() const;
  void	setShader(ShaderProgram& prgm);

protected:
  virtual void initializeGL();
  virtual void resizeGL(int w, int h);
  virtual void paintGL();
  virtual void keyPressEvent(QKeyEvent* e);

private:
  void	configureShader();
  bool prepareShaderProgram( const QString& vertexShaderPath,
			     const QString& fragmentShaderPath );

  ShaderProgram*	_shader;
  GLuint		_vertexBuffer;
};

#endif // OPENGLWIDGET_H
