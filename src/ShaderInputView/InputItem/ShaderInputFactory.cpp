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

#include "TextureInputItem.h"
#include "FloatInputItem.h"

#include "ShaderInputFactory.h"

ShaderInputFactory::ShaderInputFactory() {}

ShaderInputFactory::~ShaderInputFactory() {}

TextureInputItem* ShaderInputFactory::createTexture()
{
  TextureInputItem* item = new TextureInputItem("texture");

  return (item);
}

FloatInputItem* ShaderInputFactory::createFloat()
{
  FloatInputItem* item = new FloatInputItem("float");

  return (item);
}
