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

#include "GL/GLInfo.h"
#include "OutputItem.h"

class OutputParser
{
public:
    OutputParser(GLInfo::Vendor vendor = GLInfo::Vendor::Unknown);
    ~OutputParser();

    typedef void (OutputParser::*OutputParserFunc)(const std::string&, const std::string&);

public:
    const std::list<OutputItem>&    parse(const std::string& output, const std::string& fileAbsPath);

private:
    void    parseUnknown(const std::string& output, const std::string& fileAbsPath);

    void    parseATI(const std::string& output, const std::string& fileAbsPath);
    void    parseATIErrorLocation(std::string string, OutputItem& item);
    void    parseATIErrNo(std::string& string, OutputItem& item);

    void    parseNvidia(const std::string& output, const std::string& fileAbsPath);
    void    parseNvidiaLine(const std::string& output, OutputItem& item);
    void    parseNvidiaLocation(std::string locationString, OutputItem& item);

    void    parseIntel(const std::string& output, const std::string& fileAbsPath);
    void    parseIntelLine(const std::string& string, const std::string& fileAbsPath);
    void    parseIntelErrorLocation(std::string string, OutputItem& item);
    void    parseIntelErrorNo(const std::string& string, OutputItem& item);

private:
    std::list<OutputItem>                       _errors;
    GLInfo::Vendor                              _vendor;
    std::map<GLInfo::Vendor, OutputParserFunc>  _parsers;
};

#endif // OUTPUTPARSER_H
