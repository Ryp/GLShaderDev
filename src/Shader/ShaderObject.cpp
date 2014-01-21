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

#include <fstream>
#include <vector>
#include <iostream>
#include <GL/glew.h>

#include "ShaderObject.h"
#include "Exceptions/ShaderObjectException.hpp"

ShaderObject::ShaderObject()
  : _handle(0),
    _type(None),
    _isCompiled(false)
{}

ShaderObject::~ShaderObject() {}

bool ShaderObject::compile(const std::string& code, ShaderType type)
{
  GLuint	handle;
  GLint		success = GL_FALSE;
  GLint		logLength = 0;

  if (!(handle = glCreateShader(type)))
    return (false);
  char const * srcPtr = code.c_str();
  glShaderSource(handle, 1, &srcPtr, 0);
  glCompileShader(handle);
  glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE)
  {
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
      std::vector<GLchar> infoLog(logLength);
      glGetShaderInfoLog(handle, logLength, &logLength, &infoLog[0]);
      infoLog[logLength - 2] = '\0'; // Overwrite endline
      _log = &infoLog[0];
    }
    glDeleteShader(handle);
    return (false);
  }
  _isCompiled = true;
  _handle = handle;
  _type = type;
  _log = std::string();
  return (_isCompiled);
}

bool ShaderObject::compileFromFile(const std::string& fileName, ShaderObject::ShaderType type)
{
  std::string	code;
  std::ifstream	file(fileName, std::ios::in);

  if (!file.is_open())
    throw (ShaderObjectException("Could not open file \'" + fileName + "\'"));

  file.seekg(0, std::ios::end);
  code.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&code[0], code.size());
  file.close();
  return (compile(code, type));
}

void ShaderObject::destroy()
{
  glDeleteShader(_handle);
}

GLuint ShaderObject::getHandle() const
{
  return (_handle);
}

ShaderObject::ShaderType ShaderObject::getType() const
{
  return (_type);
}

const std::string& ShaderObject::getErrorLog() const
{
  return (_log);
}

bool ShaderObject::isCompiled() const
{
  return (_isCompiled);
}
