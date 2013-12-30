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

#include <sstream>
#include <algorithm>

#include "OutputParser.h"

OutputParser::OutputParser(Vendor vendor)
: _vendor(vendor)
{
  _parsers[Unknown] = &OutputParser::parseUnknown;
  _parsers[ATI] = &OutputParser::parseATI;
  _parsers[Nvidia] = &OutputParser::parseNvidia;
}

OutputParser::~OutputParser() {}

const std::list<OutputParser::Error>& OutputParser::parse(const std::string& output)
{
  _errors.clear();
  (*this.*(_parsers[_vendor]))(output);
  return (_errors);
}

void OutputParser::parseUnknown(const std::string& output)
{
  std::stringstream	ss(output);
  std::string		line;
  Error			error;

  error.line = 0;
  error.column = 0;
  error.errNo = 0;
  while (std::getline(ss, line))
  {
    error.content = line;
    _errors.push_back(error);
  }
}

void OutputParser::parseATI(const std::string& output)
{
  std::stringstream	ss(output);
  std::string		line;
  std::size_t		pos;
  Error			error;

  std::getline(ss, line); // Skip first line saying "following errors.."
  while (std::getline(ss, line))
  {
    error.line = 0;
    error.column = 0;
    error.errNo = 0;

    line = line.substr(7); // Remove "ERROR: "
    if ((pos = line.find("error(")) != 0 && pos != std::string::npos)
    {
      parseATIErrorLocation(line.substr(0, pos), &error.line, &error.column);
      line = line.substr(pos);
    }
    line = line.substr(7); // Remove "error(#"
    parseATIErrNo(line, &error.errNo);
    error.content = line;
    _errors.push_back(error);
  }
  _errors.pop_back(); // Remove GLSL error saying "X compilation errors, no code generated"
}

void OutputParser::parseATIErrorLocation(std::string string, int* line, int* col)
{
  std::stringstream	ss;

  std::replace(string.begin(), string.end(), ':', ' ');
  ss.str(string);
  ss >> *col;
  ss >> *line;
}

void OutputParser::parseATIErrNo(std::string& string, int* errNo)
{
  std::size_t		pos;
  std::stringstream	ss;

  pos = string.find(')');
  ss.str(string.substr(0, pos));
  ss >> *errNo;
  string = string.substr(pos + 2);
}

void OutputParser::parseNvidia(const std::string& output)
{
  static_cast<void>(output);
  // TODO Nvidia shader parser
}
