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

#ifndef SHADERPROJECT_H
#define SHADERPROJECT_H

#include <QString>
#include <map>

#include "GL/Shader/ShaderObject.h"

class ShaderProject
{
  static const QString ShaderProjectExtension;
public:
  explicit ShaderProject(); // NOTE may throw ProjectException
  ShaderProject(const QString& fileName); // NOTE may throw ProjectException
  ~ShaderProject();

public:
  static QString	parseProjectName(const QString& projectFile);

private:
  QString					_file;
  QString					_name;
  std::map<ShaderObject::ShaderType, QString>	_shaderObjects;
};

#endif // SHADERPROJECT_H
