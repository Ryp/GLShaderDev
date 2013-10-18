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

#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <string>
#include <GL/gl.h>

class ShaderObject
{
public:
  enum ShaderType {
    None = 0,
    VertexShader = GL_VERTEX_SHADER,
    TesselationControlShader = GL_TESS_CONTROL_SHADER,
    TesselationEvaluationShader = GL_TESS_EVALUATION_SHADER,
    GeometryShader = GL_GEOMETRY_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
    ComputeShader = None/* FIXME GL_COMPUTE_SHADER */
  };

public:
  ShaderObject();
  ~ShaderObject();

public:
  bool			compile(const std::string& code, ShaderType type);
  void			destroy();
  GLuint		getHandle() const;
  ShaderType		getType() const;
  const std::string&	getErrorLog() const;
  bool			isCompiled() const;

private:
  GLuint		_handle;
  ShaderType		_type;
  std::string		_log;
  bool			_isCompiled;
};

#endif // SHADEROBJECT_H
