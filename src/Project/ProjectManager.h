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

#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <map>

#include "ShaderProject.h"

class ProjectManager
{
  typedef std::map<QString, ShaderProject*> ProjectContainer;
public:
  ProjectManager();
  ~ProjectManager();

public:
  void			openProject(const QString& filename);
  void			close(const QString& filename);
  void			closeAll();

public:
  ShaderProject*	getCurrentProject();

private:
  ShaderProject*	_currentProject;
  ProjectContainer	_openedProjects;
};

#endif // PROJECTMANAGER_H
