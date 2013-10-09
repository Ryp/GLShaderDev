#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QMainWindow>
#include <QMutex>

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
  void	closeEvent(QCloseEvent* event);

  void	newProject();
  void	openProject();
  void	clearProjectRecent();
  void	closeProject();

  void	newFile();
  void	openFileDialog();
  void	openRecentFile();
  void	clearFileRecent();
  void	saveFileAs();

  void	buildCurrentProject();

  void	about();

private:
  enum { MaxRecentFiles = 9 };

private:
  CodeEditor*	_editor;
  BuildOutput*	_output;
  QDockWidget*	_buildOutputDock;
  OpenGLWidget*	_glview;
  QAction*	_recentFileActions[MaxRecentFiles + 2];
  QMutex	_buildMutex;
};

#endif // GLSHADERDEV_H
