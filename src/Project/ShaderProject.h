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

#include <map>

#include <QString>
#include <QStringList>

#include "GL/Shader/ShaderObject.h"

class ShaderProject
{
  static const QString	ShaderProjectExtension;
  static const QString	StageSeparator;
public:
  explicit ShaderProject(); // NOTE may throw ProjectException
  ShaderProject(const QString& fileName); // NOTE may throw ProjectException
  ~ShaderProject();

public:
  typedef std::map<ShaderObject::ShaderType, QString> Stages;

public:
  const QString&	getName() const;
  const QString&	getProjectFile() const;
  const Stages&		getStages() const;
  bool			isValid() const;
  void			addShaderObject(ShaderObject::ShaderType type, const QString& filename);
  void			delShaderObject(ShaderObject::ShaderType type);
  void			close();

private:
  void	loadStages(const QStringList& stages);

private:
  QString	_file;
  QString	_name;
  Stages	_shaderObjects;
};

#endif // SHADERPROJECT_H
