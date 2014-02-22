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

#include <QDebug> // FIXME

#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QMessageBox>

#include "ProjectManager.h"
#include "Exceptions/ProjectException.hpp"

ProjectManager::ProjectManager()
: _currentProject(0)
{}

ProjectManager::~ProjectManager()
{
  for (ProjectContainer::const_iterator it = _openedProjects.begin(); it != _openedProjects.end(); ++it)
    delete it->second;
}

void ProjectManager::openProject(const QString& filename)
{
  ShaderProject* newProj = 0;

  if (_openedProjects[filename])
    return;

  try
  {
    newProj = new ShaderProject(filename);
  }
  catch (const ProjectException& e)
  {
    delete newProj;
    throw (e);
  }

  _openedProjects[filename] = newProj;
  _currentProject = newProj;
}

void ProjectManager::close(const QString& filename)
{
  ShaderProject* proj;

  if (!(proj = _openedProjects[filename]))
    return;

  proj->close();
  delete proj;
  _openedProjects.erase(filename);
}

void ProjectManager::closeAll()
{
  while (_openedProjects.size() > 0)
    close(_openedProjects.begin()->first);
}

ShaderProject* ProjectManager::getCurrentProject()
{
  return (_currentProject);
}
