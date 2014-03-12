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

#ifndef ASHADERINPUTITEM_H
#define ASHADERINPUTITEM_H

#include "IShaderInputItem.h"

class AShaderInputItem : public IShaderInputItem
{
public:
  AShaderInputItem(Type type, const std::string& name = "");
  virtual ~AShaderInputItem();

public:
  GLuint		getHandle() const;
  Type			getType() const;
  const std::string&	getInputName() const;
  void			setInputName(const std::string& name);

  bool			isEnabled() const;
  void			setEnabled(bool enabled);
  void			toggle();

  bool			isLoaded() const;

  virtual void		load() = 0;
  virtual void		reload() = 0;
  virtual void		unload() = 0;
  virtual void		bind(ShaderProgram* prgm) = 0;

protected:
  GLuint	_handle;
  bool		_enabled;
  bool		_loaded;

private:
  Type		_type;
  std::string	_name;
};

#endif // ASHADERINPUTITEM_H
