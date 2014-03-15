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

#include <vector>
#include <iostream> // FIXME

#include "ShaderProgram.h"
#include "ShaderObject.h"

ShaderProgram::ShaderProgram()
  : _handle(0)
{
  if (!(_handle = glCreateProgram()))
    std::cerr << "Could not create shader program" << std::endl;
}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::attach(const ShaderObject& object)
{
  glAttachShader(_handle, object.getHandle());
}

void ShaderProgram::detach(const ShaderObject& object)
{
  glDetachShader(_handle, object.getHandle());
}

bool ShaderProgram::link()
{
  GLint		success = GL_FALSE;
  GLint		logLength = 0;

  glLinkProgram(_handle);
  glGetProgramiv(_handle, GL_LINK_STATUS, &success);
  if (success == GL_FALSE)
  {
    glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
      std::vector<GLchar> infoLog(logLength);
      glGetProgramInfoLog(_handle, logLength, &logLength, &infoLog[0]);
      infoLog[logLength - 1] = '\0'; // Overwrite endline
      _log = &infoLog[0];
    }
    destroy();
    return (false);
  }
  retrieveLocations();
  _log = std::string();
  return (true);
}

void ShaderProgram::bind()
{
  if (!_handle)
    //     throw (ShaderProgramException("Invalid shader program"));
    return ;
  glUseProgram(_handle);
}

void ShaderProgram::destroy()
{
  glDeleteProgram(_handle);
}

GLuint ShaderProgram::getHandle() const
{
  return (_handle);
}

const std::string& ShaderProgram::getLog() const
{
  return (_log);
}

GLuint ShaderProgram::getAttribLocation(const std::string& name) const
{
  std::map<std::string, GLuint>::const_iterator	it;

  if ((it = _attribs.find(name)) != _attribs.end())
    return (it->second);
  std::cerr << "Shader attribute \'" << name << "\' does not exist" << std::endl;
  return (-1);
}

GLuint ShaderProgram::getUniformLocation(const std::string& name) const
{
  std::map<std::string, GLuint>::const_iterator	it;

  if ((it = _uniforms.find(name)) != _uniforms.end())
    return (it->second);
  std::cerr << "Shader uniform \'" << name << "\' does not exist" << std::endl;
  return (-1);
}

void ShaderProgram::printDebug()
{
  std::cout << "Attributes:" << std::endl;
  for (std::map<std::string, GLuint>::iterator it = _attribs.begin(); it != _attribs.end(); ++it)
    std::cout << "Name: " << (*it).first << std::endl;
  std::cout << "Uniforms:" << std::endl;
  for (std::map<std::string, GLuint>::iterator it = _uniforms.begin(); it != _uniforms.end(); ++it)
    std::cout << "Name: " << (*it).first << std::endl;
}

void ShaderProgram::retrieveLocations()
{
  GLint		n, maxLen;
  GLint		size, location;
  GLsizei	written;
  GLenum	type;
  GLchar*	name;

  glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLen);
  glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &n);
  name = new GLchar[maxLen];
  for (int i = 0; i < n; ++i)
  {
    glGetActiveAttrib(_handle, i, maxLen, &written, &size, &type, name);
    location = glGetAttribLocation(_handle, name);
    _attribs[name] = location;
  }
  delete[] name;
  glGetProgramiv(_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
  glGetProgramiv(_handle, GL_ACTIVE_UNIFORMS, &n);
  name = new GLchar[maxLen];
  for (int i = 0; i < n; ++i)
  {
    glGetActiveUniform(_handle, i, maxLen, &written, &size, &type, name);
    location = glGetUniformLocation(_handle, name);
    _uniforms[name] = location;
  }
  delete[] name;
}
