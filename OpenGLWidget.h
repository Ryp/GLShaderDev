#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <qt4/QtGui/QWidget>
#include <qt4/QtOpenGL/QGLWidget>

#include <QGLBuffer>
#include <QGLShaderProgram>

class OpenGLWidget : public QGLWidget
{
  Q_OBJECT
public:
  OpenGLWidget(const QGLFormat& format, QWidget *parent = 0);
  ~OpenGLWidget();

public:
  QSize	sizeHint() const;

protected:
  virtual void initializeGL();
  virtual void resizeGL(int w, int h);
  virtual void paintGL();
  virtual void keyPressEvent(QKeyEvent* e);

private:
  bool prepareShaderProgram( const QString& vertexShaderPath,
			     const QString& fragmentShaderPath );
  
  QGLShaderProgram m_shader;
  QGLBuffer m_vertexBuffer;
};

#endif // OPENGLWIDGET_H
