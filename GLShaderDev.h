#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QMainWindow>

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

private:
  void	initializeOpenGL();
  void	initializeActions();
  void	initializeDockWidgets();

  void	updateRecentFiles();
  void	addRecentFile(const QString& filename);
  void	openFile(const QString& filename);

public slots:
  void	newProject();
  void	openProject();
  void	clearProjectRecent();
  void	closeProject();

  void	newFile();
  void	openFileDialog();
  void	openRecentFile();
  void	clearFileRecent();
  void	saveFileAs();

  void	buildShader();

  void	about();

private:
  enum { MaxRecentFiles = 9 };

private:
  CodeEditor*	_editor;
  BuildOutput*	_output;
  OpenGLWidget*	_glview;
  QAction*	_recentFileActions[MaxRecentFiles + 2];
};

#endif // GLSHADERDEV_H
