#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QtGui/QMainWindow>

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
};

#endif // GLSHADERDEV_H
