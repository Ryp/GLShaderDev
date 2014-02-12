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

#include <QStringList>

#include "ExtensionValidator.h"

ExtensionValidator::ExtensionValidator() :
  _validChars("abcdefghijklmnopqrstuvwxyz;")
{
}

ExtensionValidator::~ExtensionValidator()
{

}

QValidator::State ExtensionValidator::validate(QString& input, int&) const
{
  if (input.isEmpty())
    return QValidator::Invalid;
  
  input = input.toLower();
  for (int i = 0; i < input.size(); ++i)
  {
    if (!_validChars.contains(input.at(i)))
      return QValidator::Invalid;
  }
  
  QStringList		splited = input.split(";");
  splited.removeDuplicates();
  QString 		newStr;
  for (int i = 0; i < splited.size(); ++i)
  {
    newStr += splited.at(i);
    if (i + 1 < splited.size())
      newStr += ";";
  }
  input = newStr;
  return QValidator::Acceptable;
}
