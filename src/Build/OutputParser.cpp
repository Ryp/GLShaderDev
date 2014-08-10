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

static void buildShortenedString(const std::string& content, OutputItem& item)
{
    QString lineString;

    if (item.lineNo)
        lineString = QString(":%1:%2").arg(item.lineNo).arg(item.columnNo);
    item.shortenedString = QString("%1: %2 [%3]").arg(lineString).arg(QString::fromStdString(content)).arg(item.errNo);
    if (item.type == OutputItem::ErrorItem)
        item.shortenedString.prepend("Error");
    else if (item.type == OutputItem::WarningItem)
        item.shortenedString.prepend("Warning");
}

OutputParser::OutputParser(GLInfo::Vendor vendor)
: _vendor(vendor)
{
    _parsers[GLInfo::Vendor::Unknown] = &OutputParser::parseUnknown;
    _parsers[GLInfo::Vendor::ATI] = &OutputParser::parseATI;
    _parsers[GLInfo::Vendor::Nvidia] = &OutputParser::parseNvidia;
    _parsers[GLInfo::Vendor::Intel] = &OutputParser::parseIntel;
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
    std::istringstream  iss(output);
    std::string         line;

    while (std::getline(iss, line))
    {
        OutputItem  error(line.c_str(), OutputItem::StandardItem);

        error.file = fileAbsPath.c_str();
        _errors.push_back(error);
    }
}

void OutputParser::parseATI(const std::string& output, const std::string& fileAbsPath)
{
    std::istringstream  iss(output);
    std::string         line;
    std::size_t         pos;

    std::getline(iss, line); // Skip first line saying "following errors.."
    while (std::getline(iss, line))
    {
        OutputItem  error(line.c_str(), OutputItem::ErrorItem);

        error.file = fileAbsPath.c_str();
        line = line.substr(7); // Remove "ERROR: "
        if ((pos = line.find("error(")) != 0 && pos != std::string::npos)
        {
            parseATIErrorLocation(line.substr(0, pos), error);
            line = line.substr(pos);
        }
        line = line.substr(7); // Remove "error(#"
        parseATIErrNo(line, error);

        buildShortenedString(line, error);
        error.isDeferencable = true;
        _errors.push_back(error);
    }
    _errors.pop_back(); // Remove GLSL error saying "X compilation errors, no code generated"
}

void OutputParser::parseATIErrorLocation(std::string string, OutputItem& item)
{
    std::istringstream  iss;

    std::replace(string.begin(), string.end(), ':', ' ');
    iss.str(string);
    iss >> item.columnNo;
    iss >> item.lineNo;
}

void OutputParser::parseATIErrNo(std::string& string, OutputItem& item)
{
    std::size_t         pos;

    pos = string.find(')');
    item.errNo = string.substr(0, pos).c_str();
    string = string.substr(pos + 2);
}

void OutputParser::parseNvidia(const std::string& output, const std::string& fileAbsPath)
{
    std::istringstream  iss(output);
    std::string         line;

    while (std::getline(iss, line))
    {
        OutputItem  item(line.c_str());

        item.file = fileAbsPath.c_str();
        parseNvidiaLine(line, item);
        _errors.push_back(item);
    }
}

void OutputParser::parseNvidiaLine(const std::string& output, OutputItem& item)
{
    std::size_t pos;
    std::string detail;
    std::string wrnStr("warning");
    std::string errStr("error");

    if ((pos = output.find(':')) == std::string::npos)
        return;
    parseNvidiaLocation(output.substr(0, pos), item);
    detail = output.substr(pos + 2);
    if (detail.find(errStr) == 0)
    {
        detail = detail.substr(errStr.size() + 1);
        item.type = OutputItem::ErrorItem;
        item.isDeferencable = true;
    }
    else if (detail.find(wrnStr) == 0)
    {
        detail = detail.substr(wrnStr.size() + 1);
        item.type = OutputItem::WarningItem;
        item.isDeferencable = true;
    }
    if ((pos = detail.find(':')) != std::string::npos)
    {
        item.errNo = detail.substr(0, pos).c_str();
        detail = detail.substr(pos + 2);
    }
    buildShortenedString(detail, item);
}

void OutputParser::parseNvidiaLocation(std::string locationString, OutputItem& item)
{
    std::istringstream  iss;

    std::replace(locationString.begin(), locationString.end(), '(', ' ');
    std::replace(locationString.begin(), locationString.end(), ')', ' ');
    iss.str(locationString);
    iss >> item.columnNo;
    iss >> item.lineNo;
}


void OutputParser::parseIntel(const std::string& output, const std::string& fileAbsPath)
{
    std::istringstream  iss(output);
    std::string         line;

    while (std::getline(iss, line))
        parseIntelLine(line, fileAbsPath);
}

void OutputParser::parseIntelLine(const std::string& string, const std::string& fileAbsPath)
{
    OutputItem  item(string.c_str());
    std::string errstr(": error: ");
    std::size_t errpos;

    item.file = fileAbsPath.c_str();
    if ((errpos = string.find(errstr)) != std::string::npos)
    {
        item.type = OutputItem::ErrorItem;
        parseIntelErrorLocation(string.substr(0, errpos), item);
        parseIntelErrorNo(string.substr(0, errpos), item);
        buildShortenedString(string.substr(errpos + errstr.size()), item);
        item.isDeferencable = true;
    }
    else
        item.type = OutputItem::StandardItem;
    _errors.push_back(item);
}

void OutputParser::parseIntelErrorLocation(std::string string, OutputItem& item)
{
    std::istringstream  iss;

    std::replace(string.begin(), string.end(), ':', ' ');
    std::replace(string.begin(), string.end(), '(', ' ');
    iss.str(string);
    iss >> item.columnNo;
    iss >> item.lineNo;
}

void OutputParser::parseIntelErrorNo(const std::string& string, OutputItem& item)
{
    std::size_t         opos;
    std::size_t         cpos;

    opos = string.find('(');
    cpos = string.find(')');
    if (opos == std::string::npos || cpos == std::string::npos)
        return;
    item.errNo = string.substr(opos + 1, cpos - opos - 1).c_str();
}
