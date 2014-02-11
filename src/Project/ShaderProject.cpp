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

#include <QDebug>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

#include "ShaderProject.h"
#include "Exceptions/ProjectException.hpp"

const QString ShaderProject::ShaderProjectExtension = ".glsd";

ShaderProject::ShaderProject()
: _file(""),
  _name(QObject::tr("New shader project"))
{}

ShaderProject::ShaderProject(const QString& fileName)
: _file(fileName)
{
  QFile*	f = new QFile(fileName);
  QFileInfo	fileInfo(*f);

  // File existence etc....

  //
  _name = parseProjectName(fileInfo.fileName());
}

ShaderProject::~ShaderProject() {}

QString ShaderProject::parseProjectName(const QString& projectFile)
{
  if (projectFile.size() <= ShaderProjectExtension.size() || !projectFile.endsWith(ShaderProjectExtension))
    throw (ProjectException("invalid file name: " + projectFile.toStdString()));
  else
    return (projectFile.left(projectFile.size() - ShaderProjectExtension.size()));
}
