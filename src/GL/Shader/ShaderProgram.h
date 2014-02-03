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

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <map>

#include "ShaderObject.h"

class ShaderProgram
{
public:
  ShaderProgram();
  ~ShaderProgram();

public:
  void			attach(const ShaderObject& object);
  void			detach(const ShaderObject& object);
  bool			link();
  void			bind();
  void			destroy();
  GLuint		getHandle() const;
  const std::string&	getLog() const;
  GLuint		getAttribLocation(const std::string& name) const;
  GLuint		getUniformLocation(const std::string& name) const;

private:
  void			retrieveLocations();

private:
  std::string			_log;
  std::map<std::string, GLuint>	_attribs;
  std::map<std::string, GLuint>	_uniforms;
  GLuint			_handle;
};

#endif // SHADERPROGRAM_H
