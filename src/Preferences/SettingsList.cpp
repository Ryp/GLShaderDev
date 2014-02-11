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

#include "SettingsList.h"

SettingsList::SettingsList()
{

}

SettingsList::~SettingsList()
{

}

QVariant* SettingsList::getSetting(const QString& index)
{
  if (_settings.find(index) != _settings.end())
    return _settings[index];
  
  return 0;
}

void SettingsList::setSetting(const QString& index, QVariant* value)
{
  if (value)
    _settings[index] = value;
  else
    _settings.erase(index);
}

const std::map< QString, QVariant* >& SettingsList::getList() const
{
  return _settings;
}
