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

#include "ShaderManager.h"

ShaderManager::ShaderManager(unsigned sizeLimit)
  : _sizeLimit(sizeLimit)
{}

ShaderManager::~ShaderManager() {}

void ShaderManager::pushShader(const ShaderProgram& program)
{
  _shaders.push_front(program);
  if (_shaders.size() > _sizeLimit)
    _shaders.pop_back();
}

ShaderManager::ShaderManager(const ShaderManager& other)
{
  static_cast<void>(other);
}

ShaderManager& ShaderManager::operator=(const ShaderManager& other)
{
  static_cast<void>(other);
  return (*this);
}
