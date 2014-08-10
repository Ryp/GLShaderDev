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

#ifndef ISHADERINPUTITEM_H
#define ISHADERINPUTITEM_H

#include <string>

#include "GL/GLHeaders.hpp"

class ShaderProgram;

class IShaderInputItem
{
public:
    enum class Type {
        None,
        Texture,
        Float
    };

public:
    virtual ~IShaderInputItem() {}

    virtual GLuint              getHandle() const = 0;
    virtual Type                getType() const = 0;
    virtual const std::string&  getInputName() const = 0;
    virtual void                setInputName(const std::string& name) = 0;

public:
    virtual bool    isEnabled() const = 0;
    virtual void    setEnabled(bool enabled) = 0;
    virtual void    toggle() = 0;
    virtual bool    isLoaded() const = 0;

    virtual void    load() = 0;
    virtual void    reload() = 0;
    virtual void    unload() = 0;
    virtual void    bind(ShaderProgram* prgm) = 0;
};

#endif // ISHADERINPUTITEM_H
