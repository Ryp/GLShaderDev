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

#ifndef GLPREVIEWWIDGET_H
#define GLPREVIEWWIDGET_H

#include <QWidget>
#include <QGLWidget>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

class OpenGLWidget;

class GLPreviewWidget : public QWidget
{
  Q_OBJECT
public:
  GLPreviewWidget(const QGLFormat& format, QWidget* parent = 0);
  ~GLPreviewWidget();

public:
  OpenGLWidget*	getGLWidget();

public slots:
  void	backgroundColorButtonClicked();
  void	takeScreenshot();
  void	changeAutoRefresh();

private:
  OpenGLWidget*	_glWigdet;
  QAction*	_refreshAction;
};

#endif // GLPREVIEWWIDGET_H
