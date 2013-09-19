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

private:
  void	initializeActions();
  void	initializeDockWidgets();

  void	updateRecentFiles();
  void	addRecentFile(QString filename);

public slots:
  void	newProject();
  void	openProject();
  void	clearProjectRecent();
  void	closeProject();

  void	newFile();
  void	openFile();
  void	openRecentFile();
  void	clearFileRecent();
  void	saveFileAll();
  void	saveFile();
  void	saveFileAs();

  void	buildShader();

  void	onTabClosed(int index);

  void	about();

private:
  enum { MaxRecentFiles = 9 };

private:
  CodeEditor*	_editor;
  BuildOutput*	_output;
  OpenGLWidget*	_glview;
  QAction*	_recentFileActions[MaxRecentFiles + 2];
  QTimer*	_activityTimer;
};

#endif // GLSHADERDEV_H
