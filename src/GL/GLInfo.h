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

#ifndef GLINFO_H
#define GLINFO_H

#include <string>
#include <vector>
#include <map>

class GLInfo
{
public:
  enum Vendor {
    Unknown = 0,
    ATI,
    Nvidia,
    SGI
  };

public:
  GLInfo();
  ~GLInfo();

public:
  void	updateInfos();

public:
  Vendor				getVendor() const;
  const std::string&			getVendorString() const;
  const std::string&			getRendererString() const;
  const std::string&			getOpenGLVersionString() const;
  const std::string&			getGLSLVersionString() const;
  int					getGLSLMajorVersion() const;
  int					getGLSLMinorVersion() const;
  const std::vector<std::string>&	getExtensions() const;

private:
  void					parseGLSLVersion(std::string glslVersionString);

private:
  Vendor			_vendor;
  std::string			_vendorString;
  std::string			_rendererString;
  std::string			_glVersionString;
  std::string			_glslVersionString;
  int				_glslMajorVersion;
  int				_glslMinorVersion;
  std::vector<std::string>	_extensions;
  std::map<std::string, Vendor>	_vendorID;
};

#endif // GLINFO_H
