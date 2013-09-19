#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class OpenGLWidget;
class BuildOutput;
class CodeEditor;
QT_END_NAMESPACE

class GLShaderDev : public QMainWindow
{
  Q_OBJECT
public:
  GLShaderDev();
  virtual ~GLShaderDev();

public slots:
  void	newProject();
  void	openProject();
  void	clearProjectRecent();
  void	closeProject();

  void	newFile();
  void	openFile();
  void	clearFileRecent();
  void	saveFileAll();
  void	saveFile();
  void	saveFileAs();

  void	buildShader();

  void	onTabClosed(int index);

  void	about();

private:
  void	initializeActions();
  void	initializeDockWidgets();

private:
  CodeEditor*	_editor;
  BuildOutput*	_output;
  OpenGLWidget*	_glview;
};

#endif // GLSHADERDEV_H
