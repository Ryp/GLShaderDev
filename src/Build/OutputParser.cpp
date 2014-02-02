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

OutputParser::OutputParser(GLInfo::Vendor vendor)
: _vendor(vendor)
{
  _parsers[GLInfo::Unknown] = &OutputParser::parseUnknown;
  _parsers[GLInfo::ATI] = &OutputParser::parseATI;
  _parsers[GLInfo::Nvidia] = &OutputParser::parseNvidia;
}

OutputParser::~OutputParser() {}

const std::list<OutputItem>& OutputParser::parse(const std::string& output, const std::string& fileAbsPath)
{
  _errors.clear();
  (*this.*(_parsers[_vendor]))(output, fileAbsPath);
  return (_errors);
}

void OutputParser::parseUnknown(const std::string& output, const std::string& fileAbsPath)
{
  std::stringstream	ss(output);
  std::string		line;

  while (std::getline(ss, line))
  {
    OutputItem	error(line.c_str(), OutputItem::StandardItem);

    error.file = fileAbsPath.c_str();
    _errors.push_back(error);
  }
}

void OutputParser::parseATI(const std::string& output, const std::string& fileAbsPath)
{
  std::stringstream	ss(output);
  std::string		line;
  std::size_t		pos;

  std::getline(ss, line); // Skip first line saying "following errors.."
  while (std::getline(ss, line))
  {
    OutputItem	error(line.c_str(), OutputItem::ErrorItem);
    QString	lineString;

    line = line.substr(7); // Remove "ERROR: "
    if ((pos = line.find("error(")) != 0 && pos != std::string::npos)
    {
      parseATIErrorLocation(line.substr(0, pos), &error.lineNo, &error.lineNo);
      line = line.substr(pos);
    }
    line = line.substr(7); // Remove "error(#"
    parseATIErrNo(line, &error.errNo);

    if (error.lineNo)
      lineString = QString(":%1:%2").arg(error.lineNo).arg(error.columnNo);
    error.shortenedString = QString("Error%1: %2 (#%3)").arg(lineString).arg(QString::fromStdString(line)).arg(error.errNo);
    error.isDeferencable = true;
    error.file = fileAbsPath.c_str();
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

void OutputParser::parseNvidia(const std::string& output, const std::string& fileAbsPath)
{
  static_cast<void>(output);
  static_cast<void>(fileAbsPath);

  parseUnknown(output, fileAbsPath); // TODO NVidia parser
}
