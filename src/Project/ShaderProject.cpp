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
#include "GL/ShaderUtils.h"
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

  load(projectFile.value("stages").toStringList());
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

void ShaderProject::addShaderObject(ShaderObject::ShaderType type, const QString& filename)
{
  _shaderObjects[type] = filename;
}

void ShaderProject::delShaderObject(ShaderObject::ShaderType type)
{
  _shaderObjects.erase(type);
}

void ShaderProject::close()
{
  save();
}

void ShaderProject::save()
{
  QStringList			list;
  QFileInfo			info(_file);

  for (Stages::const_iterator it = _shaderObjects.begin(); it != _shaderObjects.end(); ++it)
  {
    if (!ShaderUtils::isValidType(it->first))
      throw (ProjectException(QString(QObject::tr("File '%1' is of bad type '%2'").arg(it->second)).arg(it->first).toStdString()));
    list.append(ShaderUtils::getShaderString(it->first) + StageSeparator + it->second);
  }

  QSettings	projectFile(_file, QSettings::IniFormat);

  projectFile.setValue("stages", list);
  qDebug() << "Project " << _file << " closed";
}

void ShaderProject::load(const QStringList& stages)
{
  int		len = stages.size();
  int		cutPos;
  QString	item;
  QString	typeString;

  for (int i = 0; i < len; ++i)
  {
    item = stages[i];
    if ((cutPos = item.indexOf(StageSeparator)) == -1)
      continue;
    typeString = item.left(cutPos);
    item = item.remove(0, cutPos + StageSeparator.size());
    if (!ShaderUtils::getShaderType(typeString))
      throw (ProjectException(QString(QObject::tr("File '%1' is of bad type '%2'").arg(item)).arg(typeString).toStdString()));
    addShaderObject(ShaderUtils::getShaderType(typeString), item);
  }
}
