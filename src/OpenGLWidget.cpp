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

#include <QKeyEvent>

#include "OpenGLWidget.h"
#include "Exceptions/GlsdException.hpp"

OpenGLWidget::OpenGLWidget(const QGLFormat& fmt, QWidget *parent)
: QGLWidget(fmt, parent)
{}

OpenGLWidget::~OpenGLWidget() {}

QSize OpenGLWidget::sizeHint() const
{
  return (QSize(300, 300));
}

void OpenGLWidget::setShader(ShaderProgram& prgm)
{
  _shader = &prgm;
}

void	OpenGLWidget::initializeGL()
{
  if (glewInit() != GLEW_OK)
    throw (GlsdException("glewInit() failed"));

  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  if (!prepareShaderProgram(":/simple.vert", ":/simple.frag"))
    return;

  GLfloat points[] =
  { -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f,  0.5f, 0.0f };

  glGenBuffers(1, &_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * (3 * sizeof(*points)), points, GL_STATIC_DRAW);
}

void	OpenGLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _shader->bind();
  GLuint vertexLocation = _shader->getAttribLocation("vertex");

  glEnableVertexAttribArray(vertexLocation);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glVertexAttribPointer(
    vertexLocation,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(vertexLocation);
}

void	OpenGLWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, qMax( h, 1 ));
}

void	OpenGLWidget::keyPressEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    default:
      QGLWidget::keyPressEvent(e);
  }
}

void OpenGLWidget::configureShader()
{
  // FIXME
}

bool OpenGLWidget::prepareShaderProgram( const QString& vertexShaderPath,
				     const QString& fragmentShaderPath )
{
  ShaderObject	v;
  ShaderObject	f;
  QFile		vFile(vertexShaderPath);
  QFile		fFile(fragmentShaderPath);

  vFile.open(QIODevice::ReadOnly);
  fFile.open(QIODevice::ReadOnly);

  _shader = new ShaderProgram;

  v.compile(std::string(vFile.readAll()), ShaderObject::VertexShader);
  f.compile(std::string(fFile.readAll()), ShaderObject::FragmentShader);

  if (!v.isCompiled())
    throw (GlsdException("V did not compile"));
  if (!f.isCompiled())
    throw (GlsdException("F did not compile"));

  _shader->attach(v);
  _shader->attach(f);

  if (!_shader->link())
    throw (GlsdException("Program failed to link"));

  return true;
}

