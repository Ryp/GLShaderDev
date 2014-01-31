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

#ifndef OUTPUTPARSER_H
#define OUTPUTPARSER_H

#include <list>
#include <string>
#include <map>

#include "GLInfo.h"

class OutputParser
{
public:
  typedef struct {
    int		line;
    int		column;
    int		errNo;
    std::string	content;
  } Error;

public:
  OutputParser(GLInfo::Vendor vendor = GLInfo::Unknown);
  ~OutputParser();

public:
  const std::list<Error>&	parse(const std::string& output);

private:
  void	parseUnknown(const std::string& output);
  void	parseATI(const std::string& output);
  void	parseATIErrorLocation(std::string string, int *line, int *col);
  void	parseATIErrNo(std::string& string, int *errNo);
  void	parseNvidia(const std::string& output);

private:
  std::list<Error>							_errors;
  GLInfo::Vendor							_vendor;
  std::map<GLInfo::Vendor, void (OutputParser::*)(const std::string&)>	_parsers;
};

#endif // OUTPUTPARSER_H
