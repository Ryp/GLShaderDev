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

#include "OutputItem.h"

OutputItem::OutputItem(const QString& line)
:   type(HiddenItem),
    originalString(line),
    shortenedString(line),
    isDeferencable(false),
    file(QString()),
    lineNo(0),
    columnNo(0),
    errNo(QString())
{}

OutputItem::OutputItem(const QString& line, OutputItemType type)
:   type(type),
    originalString(line),
    shortenedString(line),
    isDeferencable(false),
    file(QString()),
    lineNo(0),
    columnNo(0),
    errNo(QString())
{}
