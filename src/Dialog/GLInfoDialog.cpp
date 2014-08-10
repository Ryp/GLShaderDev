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

GLInfoDialog::GLInfoDialog(GLInfo& glInfos, QWidget *parent)
:   QDialog(parent),
    _glInfo(glInfos)
{
    QVBoxLayout*    layout = new QVBoxLayout;
    QFormLayout*    versionLayout = new QFormLayout;
    QGroupBox*      versionsBox = new QGroupBox(tr("General"));
    QListWidget*    extensionsList = new QListWidget;
    QVBoxLayout*    extensionslayout = new QVBoxLayout;
    QGroupBox*      extensionsBox = new QGroupBox(tr("Supported extensions"));
    QLabel*         label;

    QFont font = this->font();
    font.setBold(true);

    label = new QLabel(_glInfo.getVendorString().c_str());
    label->setFont(font);
    versionLayout->addRow(tr("Vendor:"), label);

    label = new QLabel(_glInfo.getRendererString().c_str());
    label->setFont(font);
    versionLayout->addRow(tr("Renderer:"), label);

    label = new QLabel(_glInfo.getOpenGLVersionString().c_str());
    label->setFont(font);
    versionLayout->addRow(tr("GL Version:"), label);

    label = new QLabel(_glInfo.getGLSLVersionString().c_str());
    label->setFont(font);
    versionLayout->addRow(tr("GLSL Version:"), label);

    versionsBox->setLayout(versionLayout);

    const std::vector< std::string >& ext = _glInfo.getExtensions();
    for (std::vector<std::string>::const_iterator it = ext.begin(); it != ext.end(); ++it)
    {
        extensionsList->addItem((*it).c_str());
    }

    extensionslayout->addWidget(extensionsList);
    extensionslayout->addWidget(new QLabel(QString("Total: %1").arg(_glInfo.getExtensions().size())), 0, Qt::AlignRight);
    extensionsBox->setLayout(extensionslayout);


    layout->addWidget(versionsBox);
    layout->addWidget(extensionsBox);

    setLayout(layout);
    setWindowTitle(tr("OpenGL Info"));
}

GLInfoDialog::~GLInfoDialog() {}
