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

#include <string>

#include <QListWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>

#include "GLInfoDialog.h"
#include "GLHeaders.hpp"

GLInfoDialog::GLInfoDialog(QWidget *parent)
: QDialog(parent)
{
  QVBoxLayout*	layout = new QVBoxLayout;
  QFormLayout*	versionLayout = new QFormLayout;
  QGroupBox*	versionsBox = new QGroupBox(tr("General"));
  QListWidget*	extensionsList = new QListWidget;
  QVBoxLayout*	extensionslayout = new QVBoxLayout;
  QGroupBox*	extensionsBox = new QGroupBox(tr("Extensions supported"));
  QLabel*	label;
  GLint		nExtensions;

  QFont font = this->font();
  font.setBold(true);

  label = new QLabel(QString(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
  label->setFont(font);
  versionLayout->addRow(tr("Vendor:"), label);

  label = new QLabel(QString(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
  label->setFont(font);
  versionLayout->addRow(tr("Renderer:"), label);

  label = new QLabel(QString(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
  label->setFont(font);
  versionLayout->addRow(tr("GL Version:"), label);

  label = new QLabel(QString(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))));
  label->setFont(font);
  versionLayout->addRow(tr("GLSL Version:"), label);

  versionsBox->setLayout(versionLayout);

  glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
  for (GLint i = 0; i < nExtensions; ++i)
  {
    const char* ext = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
    extensionsList->addItem(QString(ext));
  }

  // NOTE this could be improved using a QTreeWidget and grouping by extension class

  extensionslayout->addWidget(extensionsList);
  extensionsBox->setLayout(extensionslayout);

  layout->addWidget(versionsBox);
  layout->addWidget(extensionsBox);

  setLayout(layout);
  setWindowTitle(tr("OpenGL Info"));
}

GLInfoDialog::~GLInfoDialog() {}
