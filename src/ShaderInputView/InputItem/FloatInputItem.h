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

#ifndef FLOATINPUTITEM_H
#define FLOATINPUTITEM_H

#include "AShaderInputItem.h"

class FloatInputItem : public AShaderInputItem
{
public:
  FloatInputItem(const std::string& name);
  ~FloatInputItem();

public:
  GLfloat	getValue() const;
  void		setValue(GLfloat value);

public:
  virtual void	load();
  virtual void	reload();
  virtual void	unload();
  virtual void	bind(ShaderProgram* prgm);

private:
  GLfloat	_value;
};

#endif // FLOATINPUTITEM_H
