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

#include <gli/core/load_dds.hpp>
#include <gli/gli.hpp>

#include "GL/GLHeaders.hpp"
#include "GL/Shader/ShaderProgram.h"

#include "TextureInputItem.h"
#include "Exceptions/ShaderInputException.hpp"

TextureInputItem::TextureInputItem(const std::string& name)
: AShaderInputItem(IShaderInputItem::Texture, name)
{}

TextureInputItem::~TextureInputItem() {}

const std::string& TextureInputItem::getTextureFile() const
{
  return (_textureFile);
}

void TextureInputItem::setTextureFile(const std::string& file)
{
  _textureFile = file;
}

void TextureInputItem::load() // FIXME Handle errors properly
{
  if (_textureFile.empty())
    return;

  gli::texture2D texture(gli::load_dds(_textureFile.c_str()));

  if (texture.empty())
    return;

  glGenTextures(1, &_handle);
  glBindTexture(GL_TEXTURE_2D, _handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(texture.levels() - 1));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
  glTexStorage2D(GL_TEXTURE_2D,
		 GLint(texture.levels()),
		 GLenum(gli::internal_format(texture.format())),
		 GLsizei(texture.dimensions().x),
		 GLsizei(texture.dimensions().y));
  for (gli::texture2D::size_type level = 0; level < texture.levels(); ++level)
  {
    if (gli::is_compressed(texture.format()))
      glCompressedTexSubImage2D(GL_TEXTURE_2D,
				GLint(level),
				0, 0,
				GLsizei(texture[level].dimensions().x),
				GLsizei(texture[level].dimensions().y),
				GLenum(gli::internal_format(texture.format())),
				GLsizei(texture[level].size()),
				texture[level].data());
    else
      glTexSubImage2D(GL_TEXTURE_2D,
		      GLint(level),
		      0, 0,
		      GLsizei(texture[level].dimensions().x),
		      GLsizei(texture[level].dimensions().y),
		      GLenum(gli::external_format(texture.format())),
		      GLenum(gli::type_format(texture.format())),
		      texture[level].data());
  }
  _loaded = true;
}

void TextureInputItem::reload()
{
  unload();
  load();
}

void TextureInputItem::unload()
{
  glDeleteTextures(1, &_handle);
  _loaded = false;
}

void TextureInputItem::bind(ShaderProgram* prgm)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _handle);
  glUniform1i(prgm->getUniformLocation(getInputName()), 0);
}
