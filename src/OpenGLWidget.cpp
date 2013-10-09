#include <iostream>
#include <QKeyEvent>

#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(const QGLFormat& fmt, QWidget *parent)
: QGLWidget(fmt, parent)
{}

OpenGLWidget::~OpenGLWidget() {}

QSize OpenGLWidget::sizeHint() const
{
  return (QSize(300, 300));
}

void OpenGLWidget::setShader(QGLShaderProgram& prgm)
{
  prgm.bind();
  prgm.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);
  prgm.enableAttributeArray("vertex");
}

void	OpenGLWidget::initializeGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  if (!prepareShaderProgram(":/simple.vert", ":/simple.frag"))
    return;

  // We need us some vertex data. Start simple with a triangle ;-)
  float points[] = { -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f,
    0.0f,  0.5f, 0.0f, 1.0f };
    _vertexBuffer.create();
    _vertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    if (!_vertexBuffer.bind())
    {
      qWarning() << "Could not bind vertex buffer to the context";
      return;
    }
    _vertexBuffer.allocate( points, 3 * 4 * sizeof( float ) );

    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if (!_shader.bind())
    {
      qWarning() << "Could not bind shader program to context";
      return;
    }

    // Enable the "vertex" attribute to bind it to our currently bound
    // vertex buffer.
    _shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);
    _shader.enableAttributeArray("vertex");
}

void	OpenGLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
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
  // First we load and compile the vertex shader...
  bool result = _shader.addShaderFromSourceFile( QGLShader::Vertex, vertexShaderPath );
  if ( !result )
    qWarning() << _shader.log();

  // ...now the fragment shader...
  result = _shader.addShaderFromSourceFile( QGLShader::Fragment, fragmentShaderPath );
  if ( !result )
    qWarning() << _shader.log();

  // ...and finally we link them to resolve any references.
  result = _shader.link();
  if ( !result )
    qWarning() << "Could not link shader program:" << _shader.log();

  return result;
}

#include "OpenGLWidget.moc"
