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

#include "GL/GLHeaders.hpp"
#include "GL/Shader/ShaderProgram.h"

#include "FloatInputItem.h"

FloatInputItem::FloatInputItem(const std::string& name)
:   AShaderInputItem(IShaderInputItem::Type::Float, name)
{
    _isLoaded = true;
}

FloatInputItem::~FloatInputItem() {}

void FloatInputItem::setValue(GLfloat value)
{
    _value = value;
}

GLfloat FloatInputItem::getValue() const
{
    return (_value);
}

void FloatInputItem::load()
{
    // NOTE nothing has to be performed
}

void FloatInputItem::reload()
{
    // NOTE nothing has to be performed
}

void FloatInputItem::unload()
{
    // NOTE nothing has to be performed
}

void FloatInputItem::bind(ShaderProgram* prgm)
{
    glUniform1f(prgm->getUniformLocation(getInputName()), _value);
}
