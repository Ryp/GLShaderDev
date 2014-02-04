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

#include "Model/Model.h" // FIXME not here
#include "Vector.hpp"

#include <QGLWidget>
#include <QTime>

class ShaderProgram;

class OpenGLWidget : public QGLWidget
{
  Q_OBJECT
private:
  static const float NearPlane;
  static const float FarPlane;
  static const float VerticalDeadAngle;
  static const float DefaultFov;
  static const float MinFov;
  static const float MaxFov;
  static const float MouseWheelSpeed;

public:
  OpenGLWidget(const QGLFormat& fmt, QWidget *parent = 0);
  ~OpenGLWidget();

public:
  QSize	sizeHint() const;
  void	setShader(ShaderProgram* prgm);
  int	getTime() const;
  void	resetTime();

public slots:
  void	changeBackgroundColor(const QColor& color);
  void	takeScreenshot();

protected:
  void	initializeGL();
  void	resizeGL(int w, int h);
  void	paintGL();
  void	wheelEvent(QWheelEvent* event);
  void	mousePressEvent(QMouseEvent* event);
  void	mouseReleaseEvent(QMouseEvent* event);
  void	mouseMoveEvent(QMouseEvent* event);

private:
  void	mouseMoved(const QPoint& offset, bool slow);
  void	updateProjectionMatrix();

signals:
  void	glInitialized();

private:
  Vect2u		_viewportSize;
  ShaderProgram*	_shader;
  GLuint		_vertexBuffer;
  GLuint		_normalBuffer;
  QTime			_clock;
  Model*		_model; // FIXME debug
  float			_fov;
  glm::mat4		_ModelMatrix;
  glm::mat4		_ViewMatrix;
  glm::mat4		_ProjectionMatrix;
  glm::mat4		_MVP;
  float			_pitch;
  float			_yaw;
  bool			_isDraggingMouse;
  QPoint		_cursorPos;
};

#endif // OPENGLWIDGET_H
