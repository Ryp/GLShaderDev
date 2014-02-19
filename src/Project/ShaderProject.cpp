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
#include <QSettings>
#include <QMessageBox>

#include "ShaderProject.h"
#include "Exceptions/ProjectException.hpp"

const QString ShaderProject::ShaderProjectExtension = "glsd";
const QString ShaderProject::StageSeparator = ":";

ShaderProject::ShaderProject()
: _file(""),
  _name(QObject::tr("New shader project"))
{}

ShaderProject::ShaderProject(const QString& fileName)
: _file(fileName)
{
  QFileInfo	info(fileName);

  if (info.suffix().compare(ShaderProjectExtension, Qt::CaseInsensitive))
    throw (ProjectException(QString(QObject::tr("File '%1' has invalid extension").arg(fileName)).toStdString()));
  if (info.completeBaseName().isEmpty())
    throw (ProjectException(QString(QObject::tr("Bad file name '%1'").arg(fileName)).toStdString()));
  _name = info.completeBaseName();

  if (!info.exists())
    throw (ProjectException(QString(QObject::tr("File '%1' does not exists").arg(fileName)).toStdString()));

  QSettings	projectFile(fileName, QSettings::IniFormat);

  loadStages(projectFile.value("stages").toStringList());
}

ShaderProject::~ShaderProject() {}

const QString& ShaderProject::getName() const
{
  return (_name);
}

const QString& ShaderProject::getProjectFile() const
{
  return (_file);
}

const ShaderProject::Stages& ShaderProject::getStages() const
{
  return (_shaderObjects);
}

bool ShaderProject::isValid() const
{
  return (!_shaderObjects.at(ShaderObject::VertexShader).isEmpty() && !_shaderObjects.at(ShaderObject::FragmentShader).isEmpty());
}

void ShaderProject::addShaderObject(ShaderObject::ShaderType type, const QString& filename)
{
  _shaderObjects[type] = filename;
}

void ShaderProject::delShaderObject(ShaderObject::ShaderType type)
{
  _shaderObjects.erase(type);
}

void ShaderProject::build()
{
  for (Stages::const_iterator it = _shaderObjects.begin(); it != _shaderObjects.end(); ++it)
  {
    // TODO
  }
}

void ShaderProject::close()
{
  QStringList			list;
  QFileInfo			info(_file);
  ShaderObject::ShaderType	type;

  for (Stages::const_iterator it = _shaderObjects.begin(); it != _shaderObjects.end(); ++it)
  {
    type = it->first;
    if (type == ShaderObject::VertexShader)
      list.append("Vertex" + StageSeparator + it->second);
    else if (type == ShaderObject::FragmentShader)
      list.append("Fragment" + StageSeparator + it->second);
    else if (type == ShaderObject::GeometryShader)
      list.append("Geometry" + StageSeparator + it->second);
  }

  QSettings	projectFile(_file, QSettings::IniFormat);

  projectFile.setValue("stages", list);
  qDebug() << "Project " << _file << " closed";
}

void ShaderProject::loadStages(const QStringList& stages)
{
  int		len = stages.size();
  int		cutPos;
  QString	item;
  QString	type;

  for (int i = 0; i < len; ++i)
  {
    item = stages[i];
    if ((cutPos = item.indexOf(StageSeparator)) == -1)
      continue;
    type = item.left(cutPos);
    item = item.remove(0, cutPos + StageSeparator.size());
    if (type == "Vertex")
      addShaderObject(ShaderObject::VertexShader, item);
    else if (type == "Fragment")
      addShaderObject(ShaderObject::FragmentShader, item);
    else if (type == "Geometry")
      addShaderObject(ShaderObject::GeometryShader, item);
    else
      qDebug() << "loadStages::Invalid type";
  }
}
