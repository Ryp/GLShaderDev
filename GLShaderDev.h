#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QtGui/QMainWindow>

class OpenGLWidget;
class BuildOutput;
class CodeEditor;

class GLShaderDev : public QMainWindow
{
  Q_OBJECT
public:
  GLShaderDev();
  virtual ~GLShaderDev();

public:
  void	initializeActions();
  void	initializeDockWidgets();

public slots:
  void	open();
  void	onTabClosed(int index);

private:
  CodeEditor*	_editor;
  BuildOutput*	_output;
  OpenGLWidget*	_glview;
};

#endif // GLSHADERDEV_H
