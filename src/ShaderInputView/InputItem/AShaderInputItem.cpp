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

#include "AShaderInputItem.h"

AShaderInputItem::AShaderInputItem(Type type, const std::string& name)
:   _handle(0),
    _enabled(true),
    _isLoaded(false),
    _type(type),
    _name(name)
{}

AShaderInputItem::~AShaderInputItem() {}

GLuint AShaderInputItem::getHandle() const
{
    return (_handle);
}

IShaderInputItem::Type AShaderInputItem::getType() const
{
    return (_type);
}

const std::string& AShaderInputItem::getInputName() const
{
    return (_name);
}

void AShaderInputItem::setInputName(const std::string& name)
{
    _name = name;
}

bool AShaderInputItem::isEnabled() const
{
    return (_enabled);
}

void AShaderInputItem::setEnabled(bool enabled)
{
    _enabled = enabled;
}

void AShaderInputItem::toggle()
{
    _enabled = !_enabled;
}

bool AShaderInputItem::isLoaded() const
{
    return (_isLoaded);
}
