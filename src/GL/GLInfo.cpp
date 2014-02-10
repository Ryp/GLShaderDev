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

#include <algorithm>
#include <sstream>

#include "GLHeaders.hpp"
#include "GLInfo.h"

GLInfo::GLInfo()
: _vendor(Unknown),
  _vendorString("N/A"),
  _rendererString("N/A"),
  _glVersionString("N/A"),
  _glslVersionString("N/A"),
  _glslMajorVersion(0),
  _glslMinorVersion(0)
{
  // TODO Complete the enum list
  _vendorID["ATI"] = ATI;
  _vendorID["NVIDIA"] = Nvidia;
  _vendorID["SGI"] = SGI;
}

GLInfo::~GLInfo() {}

void GLInfo::updateInfos()
{
  GLint		nExtensions = 0;

  _vendorString = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  _rendererString = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  _glVersionString = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  _glslVersionString = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
  parseGLSLVersion(_glslVersionString);

  glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
  _extensions = std::vector<std::string>(nExtensions);
  for (GLint i = 0; i < nExtensions; ++i)
    _extensions[i] = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));

  std::stringstream	ss(_vendorString);
  std::string		vendorSubstring;

  ss >> vendorSubstring;
  _vendor = _vendorID[vendorSubstring];
}

GLInfo::Vendor GLInfo::getVendor() const
{
  return (_vendor);
}

const std::string& GLInfo::getVendorString() const
{
  return (_vendorString);
}

const std::string& GLInfo::getRendererString() const
{
  return (_rendererString);
}

const std::string& GLInfo::getOpenGLVersionString() const
{
  return (_glVersionString);
}

const std::string& GLInfo::getGLSLVersionString() const
{
  return (_glslVersionString);
}

int GLInfo::getGLSLMajorVersion() const
{
  return (_glslMajorVersion);
}

int GLInfo::getGLSLMinorVersion() const
{
  return (_glslMinorVersion);
}

const std::vector< std::string >& GLInfo::getExtensions() const
{
  return (_extensions);
}

void GLInfo::parseGLSLVersion(std::string glslVersionString)
{
  std::stringstream	ss;

  std::replace(glslVersionString.begin(), glslVersionString.end(), '.', ' ');
  ss.str(glslVersionString);
  ss >> _glslMajorVersion;
  ss >> _glslMinorVersion;
}
