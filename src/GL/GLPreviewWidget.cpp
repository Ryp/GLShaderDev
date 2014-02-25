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

#include <QtGui/QGridLayout>
#include <QtGui/QToolBar>
#include <QtGui/QIcon>
#include <QtGui/QColorDialog>
#include <QtGui/QFileDialog>
#include <QMessageBox>

#include <QAction>

#include "OpenGLWidget.h"
#include "GLPreviewWidget.h"

GLPreviewWidget::GLPreviewWidget(const QGLFormat& format, QWidget* parent)
: QWidget(parent),
  _glWigdet(new OpenGLWidget(format, this))
{
  QGridLayout*	layout = new QGridLayout;
  QToolBar*	toolbar = new QToolBar;

  toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
  toolbar->setIconSize(QSize(16, 16));
  toolbar->addAction(QIcon(":/preferences-desktop-screensaver.png"), tr("&Take Screenshot"), this, SLOT(takeScreenshot()));
  toolbar->addAction(QIcon(":/fill-color.png"), tr("&Background color"), this, SLOT(backgroundColorButtonClicked()));
  toolbar->addSeparator();
  _refreshAction = toolbar->addAction(QIcon(":/view-refresh.png"), tr("&AutoRefresh"), this, SLOT(changeAutoRefresh()));
  _refreshAction->setCheckable(true);

  layout->addWidget(_glWigdet);
  layout->addWidget(toolbar);

  setLayout(layout);
}

GLPreviewWidget::~GLPreviewWidget() {}

OpenGLWidget* GLPreviewWidget::getGLWidget()
{
  return (_glWigdet);
}

void GLPreviewWidget::backgroundColorButtonClicked()
{
  QColor	color = QColorDialog::getColor(_glWigdet->getBgrColor(), this, tr("Text Color"), QColorDialog::DontUseNativeDialog);

  if (color.isValid())
    _glWigdet->changeBackgroundColor(color);
}

void GLPreviewWidget::takeScreenshot() // FIXME Open FileDialog
{
  _glWigdet->paintGL();
  glFlush();
  QImage img = _glWigdet->grabFrameBuffer();

  QFileDialog	dialogFile(this);
  dialogFile.setDefaultSuffix("png");
  QString fileName = dialogFile.getSaveFileName(this, tr("Save Screenshot"), "screenshot.png", ".png");

  if (fileName.isEmpty())
    return;

  if (!img.save(fileName))
  {
    QMessageBox::warning(this, tr("Error"), tr("Failed to save: '%1'").arg(fileName));
  }
}

void GLPreviewWidget::changeAutoRefresh()
{
  _glWigdet->setAutoRefresh(_refreshAction->isChecked());
}
