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
#include "Shader/ShaderProgram.h"
#include "Exceptions/GlsdException.hpp"
#include "Model/ModelLoader.h" // FIXME not here
#include <glm/gtc/matrix_transform.hpp>

OpenGLWidget::OpenGLWidget(const QGLFormat& fmt, QWidget *parent)
: QGLWidget(fmt, parent),
  _viewportSize(size().width(), size().height()),
  _shader(0)
{
  _clock.start();

  glm::mat4 Projection	= glm::perspective(45.0f, static_cast<float>(_viewportSize.ratio()), 0.1f, 100.0f);
  glm::mat4 View	= glm::mat4(1.0f);
  glm::mat4 Model	= glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)), glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 MV		= View * Model;
  _MVP			= Projection * MV;
  // glm::mat4 Viewport   = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(_viewportSize[0] / 2.0f, _viewportSize[1] / 2.0f, 1.0f)), glm::vec3(1.0f, 1.0f, 0.0f));
}

OpenGLWidget::~OpenGLWidget() {}

QSize OpenGLWidget::sizeHint() const
{
  return (QSize(300, 300)); // FIXME
}

void OpenGLWidget::setShader(ShaderProgram* prgm)
{
  _shader = prgm;

  updateGL();
}

void OpenGLWidget::changeBackgroundColor(const QColor& color)
{
  float	c[3];

  c[0] = static_cast<float>(color.red()) / 255.0f;
  c[1] = static_cast<float>(color.green() / 255.0f);
  c[2] = static_cast<float>(color.blue() / 255.0f);

  makeCurrent();
  glClearColor(c[0], c[1], c[2], 1.0f);
  updateGL();
}

int OpenGLWidget::getTime() const
{
  return (_clock.elapsed());
}

void OpenGLWidget::resetTime()
{
  _clock.start();
}

void	OpenGLWidget::initializeGL()
{
  if (glewInit() != GLEW_OK)
    throw (GlsdException("glewInit() failed"));

  glEnable(GL_DEPTH_TEST);
//   glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);
  glClearColor(0.0f, 0.2f, 0.8f, 1.0f);

  ModelLoader	ml;
  _model = ml.load("/home/ryp/Dev/C++/GLShaderDev/rc/model/suzanne.obj"); // FIXME
  _model->debugDump();

  glGenBuffers(1, &_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, _model->getVertexBufferSize(), _model->getVertexBuffer(), GL_STATIC_DRAW);

  glGenBuffers(1, &_normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, _model->getNormalBufferSize(), _model->getNormalBuffer(), GL_STATIC_DRAW);
}

void	OpenGLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!_shader)
    return;

  _shader->bind();
  GLuint vertexLocation = _shader->getAttribLocation("vertex");
  GLuint normalLocation = _shader->getAttribLocation("normal");

  glUniformMatrix4fv(_shader->getUniformLocation("MVP"), 1, GL_FALSE, &_MVP[0][0]);

  glEnableVertexAttribArray(vertexLocation);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glVertexAttribPointer(
    vertexLocation,     // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized
    0,                  // stride
    (void*)0            // array buffer offset
  );

  glEnableVertexAttribArray(normalLocation);
  glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
  glVertexAttribPointer(
    normalLocation,     // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized
    0,                  // stride
    (void*)0            // array buffer offset
  );

  glDrawArrays(GL_TRIANGLES, 0, _model->getTriangleCount() * 3);

  glDisableVertexAttribArray(vertexLocation);
  glDisableVertexAttribArray(normalLocation);
}

void	OpenGLWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, qMax(h, 1));
  _viewportSize[0] = w;
  _viewportSize[1] = h;

  //FIXME Bullshit-o-meter overflowed
  glm::mat4 Projection	= glm::perspective(45.0f, static_cast<float>(_viewportSize.ratio()), 0.1f, 100.0f);
  glm::mat4 View	= glm::mat4(1.0f);
  glm::mat4 Model	= glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)), glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 MV		= View * Model;
  _MVP			= Projection * MV;
}

void	OpenGLWidget::keyPressEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    default:
      QGLWidget::keyPressEvent(e);
  }
}

