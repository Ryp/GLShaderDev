/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QMainWindow>

#include "Project/ProjectManager.h"
#include "GL/GLInfo.h"

class GLPreviewWidget;
class GLInfoDialog;
class ShaderInputView;
class ShaderStagesView;
class OpenGLWidget;
class NewFileDialog;
class BuildOutput;
class CodeEditor;

class GLShaderDev : public QMainWindow
{
    Q_OBJECT
public:
    explicit GLShaderDev(const QStringList& args);
    ~GLShaderDev();

private:
    void    initializeContext();
    void    initializeActions();
    void    initializeDockWidgets();

    void    loadSettings();
    void    saveSettings();

    void    updateRecentFiles();
    void    updateRecentProjects();
    void    addRecentFile(const QString& filename);
    void    addRecentProject(const QString& filename);
    void    openFile(const QString& filename);
    void    openProject(const QString& filename);
    void    openProjectFiles(ShaderProject* project);

    void    updateTitleBar();

public slots:
    void    closeEvent(QCloseEvent* event);

    void    newProject();
    void    openProjectDialog();
    void    openRecentProject();
    void    clearProjectRecent();
    void    closeProject();

    void    newFile();
    void    openFileDialog();
    void    openRecentFile();
    void    clearFileRecent();
    void    saveFileAs();

    void    openProjectConfiguration();
    void    buildCurrentProject();

    void    initGLInfo();
    void    showGLInfo();

    void    showPreferences();

    void    about();

private:
    enum { MaxRecentFiles = 9 };
    enum { MaxRecentProjects = 9 };

private:
    CodeEditor*         _editor;
    BuildOutput*        _output;
    QDockWidget*        _buildOutputDock;
    OpenGLWidget*       _glwidget;
    GLPreviewWidget*    _glpreview;
    GLInfoDialog*       _glInfoDialog;
    ShaderStagesView*   _shaderStages;
    ShaderInputView*    _shaderInput;
    NewFileDialog*      _newFileDialog;
    QAction*            _recentFileActions[MaxRecentFiles + 2];
    QAction*            _recentProjectActions[MaxRecentProjects + 2];
    ProjectManager      _projectManager;
    GLInfo              _glInfo;
};

#endif // GLSHADERDEV_H
