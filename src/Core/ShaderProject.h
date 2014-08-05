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

#ifndef SHADERPROJECT_H
#define SHADERPROJECT_H

#include "Xml/IXmlSerializable.h"
#include "OpenGL/GlslProperties.h"

class ShaderProject : public IXmlSerializable
{
public:
    explicit ShaderProject();
    ~ShaderProject();

    ShaderProject(const ShaderProject& other);
    ShaderProject& operator=(const ShaderProject& other);

private:
    virtual void    serialize(ptree& node) override;
    virtual void    deserialize(const ptree& node) override;

private:
    std::string     _projectFile;
    GlContextInfo   _contextVersion;
};

#endif // SHADERPROJECT_H
