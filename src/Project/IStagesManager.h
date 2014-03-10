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

#ifndef ISTAGESITEMMANAGER_H
#define ISTAGESITEMMANAGER_H

#include <map>

#include <QString>

#include "GL/Shader/ShaderObject.h"

class IStagesManager
{
public:
  typedef std::map<ShaderObject::ShaderType, QString>	Stages;

public:
  virtual ~IStagesManager() {}
  virtual const Stages&	getStages() const = 0;
  virtual void		addShaderObject(ShaderObject::ShaderType type, const QString& filename) = 0;
  virtual void		delShaderObject(ShaderObject::ShaderType type) = 0;
};

#endif // ISTAGESITEMMANAGER_H
