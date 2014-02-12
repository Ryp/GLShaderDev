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

#ifndef EXTENSIONVALIDATOR_H
#define EXTENSIONVALIDATOR_H

#include <QValidator>
#include <QString>

class ExtensionValidator : public QValidator
{
Q_OBJECT

public:
  ExtensionValidator();
  virtual ~ExtensionValidator();

  virtual QValidator::State validate(QString& , int& ) const;
  
private:
  QString 		_validChars;
};

#endif // EXTENSIONVALIDATOR_H
