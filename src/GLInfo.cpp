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

#include "GLHeaders.hpp"
#include "GLInfo.h"

GLInfo::GLInfo()
: _vendor("N/A"),
  _renderer("N/A"),
  _glVersion("N/A"),
  _glslVersion("N/A")
{}

GLInfo::~GLInfo() {}

void GLInfo::updateInfos()
{
  GLint		nExtensions = 0;

  _vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  _renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  _glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  _glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
  _extensions = std::vector<std::string>(nExtensions);
  for (GLint i = 0; i < nExtensions; ++i)
    _extensions[i] = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
}

const std::string& GLInfo::getVendor() const
{
  return (_vendor);
}

const std::string& GLInfo::getRenderer() const
{
  return (_renderer);
}

const std::string& GLInfo::getOpenGLVersion() const
{
  return (_glVersion);
}

const std::string& GLInfo::getGLSLVersion() const
{
  return (_glslVersion);
}

const std::vector< std::string >& GLInfo::getExtensions() const
{
  return (_extensions);
}
