#include "GL/glew.h"
#include "GL/gl.h"

#include <iostream>
#include <QtGui/QKeyEvent>

#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(const QGLFormat& format, QWidget *parent)
: QGLWidget(format, parent)
{}

OpenGLWidget::~OpenGLWidget() {}

QSize OpenGLWidget::sizeHint() const
{
  return (QSize(300, 300));
}

void	OpenGLWidget::initializeGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  if ( !prepareShaderProgram( "simple.vert", "simple.frag" ) )
    return;

  // We need us some vertex data. Start simple with a triangle ;-)
  float points[] = { -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f,
    0.0f,  0.5f, 0.0f, 1.0f };
    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( !m_vertexBuffer.bind() )
    {
      qWarning() << "Could not bind vertex buffer to the context";
      return;
    }
    m_vertexBuffer.allocate( points, 3 * 4 * sizeof( float ) );

    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !m_shader.bind() )
    {
      qWarning() << "Could not bind shader program to context";
      return;
    }

    // Enable the "vertex" attribute to bind it to our currently bound
    // vertex buffer.
    m_shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);
    m_shader.enableAttributeArray("vertex");
}

void	OpenGLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void	OpenGLWidget::resizeGL(int w, int h)
{
  glViewport( 0, 0, w, qMax( h, 1 ) );
}

void	OpenGLWidget::keyPressEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    default:
      QGLWidget::keyPressEvent( e );
  }
}

bool OpenGLWidget::prepareShaderProgram( const QString& vertexShaderPath,
				     const QString& fragmentShaderPath )
{
  // First we load and compile the vertex shader...
  bool result = m_shader.addShaderFromSourceFile( QGLShader::Vertex, vertexShaderPath );
  if ( !result )
    qWarning() << m_shader.log();

  // ...now the fragment shader...
  result = m_shader.addShaderFromSourceFile( QGLShader::Fragment, fragmentShaderPath );
  if ( !result )
    qWarning() << m_shader.log();

  // ...and finally we link them to resolve any references.
  result = m_shader.link();
  if ( !result )
    qWarning() << "Could not link shader program:" << m_shader.log();

  return result;
}

#include "OpenGLWidget.moc"
