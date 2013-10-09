#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>

class OpenGLWidget : public QGLWidget
{
  Q_OBJECT
public:
  OpenGLWidget(const QGLFormat& fmt, QWidget *parent = 0);
  ~OpenGLWidget();

public:
  QSize	sizeHint() const;
  void	setShader(QGLShaderProgram& prgm);

protected:
  virtual void initializeGL();
  virtual void resizeGL(int w, int h);
  virtual void paintGL();
  virtual void keyPressEvent(QKeyEvent* e);

private:
  void	configureShader();
  bool prepareShaderProgram( const QString& vertexShaderPath,
			     const QString& fragmentShaderPath );

  QGLShaderProgram	_shader;
  QGLBuffer		_vertexBuffer;
};

#endif // OPENGLWIDGET_H
