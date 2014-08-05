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

#ifndef XMLCONFIG_H
#define XMLCONFIG_H

#include <string>

#include "IXmlSerializable.h"

class XmlConfig
{
    static const int WhiteSpaceIndent = 4;

public:
    explicit XmlConfig(const std::string& file, IXmlSerializable& object);
    ~XmlConfig() = default;

    XmlConfig(const XmlConfig& other) = delete;
    XmlConfig& operator=(const XmlConfig& other) = delete;

public:
    void    serialize();
    void    deserialize();

private:
    const std::string   _file;
    IXmlSerializable&   _object;
};

#endif // XMLCONFIG_H
