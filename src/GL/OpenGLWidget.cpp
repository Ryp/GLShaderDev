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

#include <QDebug> // FIXME not here

#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimer>

#include <gli/core/load_dds.hpp>
#include <gli/gli.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OpenGLWidget.h"
#include "Math.hpp"
#include "Shader/ShaderProgram.h"
#include "Project/IInputItemManager.h"
#include "Exceptions/GlsdException.hpp"

#include "Model/ModelLoader.h" // FIXME not here
#include "ShaderInputView/InputItem/TextureInputItem.h" // FIXME not here
#include "ShaderInputView/InputItem/FloatInputItem.h" // FIXME not here

const float OpenGLWidget::NearPlane = 0.1f;
const float OpenGLWidget::FarPlane = 1000.0f;
const float OpenGLWidget::VerticalDeadAngle = 0.01f;
const float OpenGLWidget::DefaultFov = 80.0f;
const float OpenGLWidget::MinFov = 20.0f;
const float OpenGLWidget::MaxFov = 140.0f;
const float OpenGLWidget::MouseWheelSpeed = 0.10f;

OpenGLWidget::OpenGLWidget(const QGLFormat& fmt, QWidget* parent)
: QGLWidget(fmt, parent),
  _viewportSize(size().width(), size().height()),
  _shader(0),
  _inputs(0),
  _refreshTimer(new QTimer(this)),
  _autoRefresh(false), // FIXME Get this param from project
  _fov(DefaultFov),
  _ModelMatrix(glm::mat4(1.0f)),
  _ViewMatrix(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)), glm::vec3(0.0f, 0.0f, -3.0f))),
  _MV(_ViewMatrix * _ModelMatrix),
  _MVP(_ProjectionMatrix * _MV),
  _pitch(0.0f),
  _yaw(0.0f),
  _isDraggingMouse(false)
{
  updateProjectionMatrix();

  _time.start();
  _refreshTimer->setInterval(30); // FIXME
  connect(_refreshTimer, SIGNAL(timeout()), this, SLOT(updateGL()));

  setMinimumHeight(200); // FIXME
  setMinimumWidth(200);
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::setShader(ShaderProgram* prgm)
{
  _shader = prgm;
  updateGL();
}

void OpenGLWidget::setInputs(IInputItemManager* inputs)
{
  _inputs = inputs;
  updateGL();
}

const QColor& OpenGLWidget::getBgrColor() const
{
  return (_bgrColor);
}

void OpenGLWidget::resetTime()
{
  _time.restart();
}

void OpenGLWidget::setAutoRefresh(bool enabled)
{
  _autoRefresh = enabled;

  if (_autoRefresh)
    _refreshTimer->start();
  else
    _refreshTimer->stop();
}

void OpenGLWidget::changeBackgroundColor(const QColor& color)
{
  float	c[3];

  c[0] = static_cast<float>(color.red()) / 255.0f;
  c[1] = static_cast<float>(color.green() / 255.0f);
  c[2] = static_cast<float>(color.blue() / 255.0f);

  _bgrColor = color;

  makeCurrent();
  glClearColor(c[0], c[1], c[2], 1.0f);
  updateGL();
}

void	OpenGLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!_shader)
    return;

  _shader->bind();
  GLuint vertexLocation = _shader->getAttribLocation("vertex");
  GLuint normalLocation = _shader->getAttribLocation("normal");
  GLuint uvLocation = _shader->getAttribLocation("uv");

  glUniformMatrix4fv(_shader->getUniformLocation("MV"), 1, GL_FALSE, &_MV[0][0]);
  glUniformMatrix4fv(_shader->getUniformLocation("MVP"), 1, GL_FALSE, &_MVP[0][0]);

  if (_autoRefresh)
    glUniform1f(_shader->getUniformLocation("time"), static_cast<GLfloat>(_time.elapsed()) / 1000.0f);

  // FIXME FIXME FIXME
  glUniform3f(_shader->getUniformLocation("LightPosition_worldspace"), 3.0f, 3.0f, 3.0f);

  if (_inputs)
  {
    for (IInputItemManager::InputItems::iterator it = _inputs->getInputItems().begin(); it != _inputs->getInputItems().end(); ++it)
    {
      IShaderInputItem* item = *it;

      qDebug() << "Binding input: " << QString(item->getInputName().c_str());
      if (item->isEnabled())
	item->bind(_shader);
    }
  }

  glUniform2ui(_shader->getUniformLocation("screenSize"), _viewportSize[0], _viewportSize[1]);

  glEnableVertexAttribArray(vertexLocation);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glEnableVertexAttribArray(normalLocation);
  glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
  glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glEnableVertexAttribArray(uvLocation);
  glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
  glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glDrawArrays(GL_TRIANGLES, 0, _model->getTriangleCount() * 3);

  glDisableVertexAttribArray(vertexLocation);
  glDisableVertexAttribArray(normalLocation);
  glDisableVertexAttribArray(uvLocation);
}

void	OpenGLWidget::initializeGL()
{
  if (glewInit() != GLEW_OK)
    throw (GlsdException("glewInit() failed"));

  glEnable(GL_DEPTH_TEST);
  //   glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  ModelLoader	ml;
  _model = ml.load("../rc/model/quad.obj");

  if (_inputs) // FIXME not here
  {
    TextureInputItem* textureInput = new TextureInputItem("tex");
    textureInput->setTextureFile("../rc/texture/noise.dds");
    textureInput->load();

    FloatInputItem* floatInput = new FloatInputItem("b");
    floatInput->setValue(0.5f);

    _inputs->getInputItems().push_back(textureInput);
    _inputs->getInputItems().push_back(floatInput);
  }

  glGenBuffers(1, &_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, _model->getVertexBufferSize(), _model->getVertexBuffer(), GL_STATIC_DRAW);

  glGenBuffers(1, &_normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, _model->getNormalBufferSize(), _model->getNormalBuffer(), GL_STATIC_DRAW);

  glGenBuffers(1, &_uvBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, _model->getUVBufferSize(), _model->getUVBuffer(), GL_STATIC_DRAW);

  emit glInitialized();
}

void	OpenGLWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, qMax(h, 1));
  _viewportSize[0] = w;
  _viewportSize[1] = h;

  updateProjectionMatrix();
}

void OpenGLWidget::wheelEvent(QWheelEvent* event)
{
  float	delta = - static_cast<float>(event->delta()) * MouseWheelSpeed; // NOTE delta() deprecated in next versions of Qt

  if ((event->modifiers() & Qt::ControlModifier) > 0)
    delta *= 0.2f;
  _fov += delta;
  if (_fov > MaxFov)
    _fov = MaxFov;
  if (_fov < MinFov)
    _fov = MinFov;

  updateProjectionMatrix();
  updateGL();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
  {
    _isDraggingMouse = true;
    _cursorPos = event->pos();
  }
  QWidget::mousePressEvent(event);
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
    _isDraggingMouse = false;
  QWidget::mouseReleaseEvent(event);
}

void	OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
  QPoint newPos = event->pos();

  if (_isDraggingMouse)
    mouseMoved(newPos - _cursorPos, (event->modifiers() & Qt::ControlModifier) > 0);
  _cursorPos = newPos;
}

void OpenGLWidget::mouseMoved(const QPoint& offset, bool slow)
{
  float	yawAmount = (static_cast<float>(offset.x()) / static_cast<float>(size().width() / 2)) * 1.5f * ((slow) ? (0.2f) : (1.0f));
  float	pitchAmount = (static_cast<float>(offset.y()) / static_cast<float>(size().height() / 2)) * 1.5f * ((slow) ? (0.2f) : (1.0f));

  _yaw = fmod(_yaw + yawAmount, 2.0f * M_PI);
  _pitch += pitchAmount;
  if (_pitch > (M_PI / 2.0f - VerticalDeadAngle))
    _pitch = (M_PI / 2.0f - VerticalDeadAngle);
  if (_pitch < (VerticalDeadAngle - M_PI / 2.0f))
    _pitch = (VerticalDeadAngle - M_PI / 2.0f);

  _ModelMatrix = glm::mat4(1.0f);
  _ModelMatrix = glm::rotate(_ModelMatrix, RadToDeg(_pitch), glm::vec3(1.0f, 0.0f, 0.0f));
  _ModelMatrix = glm::rotate(_ModelMatrix, RadToDeg(_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
  _MV = _ViewMatrix * _ModelMatrix;
  _MVP = _ProjectionMatrix * _MV;
  updateGL();
}

void OpenGLWidget::updateProjectionMatrix()
{
  _ProjectionMatrix = glm::perspective(_fov, static_cast<float>(_viewportSize.ratio()), NearPlane, FarPlane);
  _MVP = _ProjectionMatrix * _MV;
}
