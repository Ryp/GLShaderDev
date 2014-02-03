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

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <list>
#include "GL/Shader/ShaderProgram.h"

class ShaderManager
{
  static const int DefautSize = 10;
public:
  ShaderManager(unsigned sizeLimit = DefautSize);
  ~ShaderManager();

public:
  void	pushShader(const ShaderProgram& program);

private:
  ShaderManager(const ShaderManager& other);
  ShaderManager& operator=(const ShaderManager& other);

private:
  unsigned			_sizeLimit;
  std::list<ShaderProgram>	_shaders;
};

#endif // SHADERMANAGER_H
