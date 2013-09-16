#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QtGui/QMainWindow>

class BuildOutput;
class CodeEditor;

class GLShaderDev : public QMainWindow
{
  Q_OBJECT
public:
  GLShaderDev();
  virtual ~GLShaderDev();

public slots:
  void	open();
  void	onTabClosed(int index);

private:
  CodeEditor*	_editor;
  BuildOutput*	_output;
};

#endif // GLSHADERDEV_H
