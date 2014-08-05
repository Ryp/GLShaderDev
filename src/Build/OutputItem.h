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

#ifndef OUTPUTITEM_H
#define OUTPUTITEM_H

#include <QString>

struct OutputItem
{
    enum OutputItemType
    {
        HiddenItem = 0,
        ErrorItem,
        StandardItem,
        InformationItem
    };
    
    explicit OutputItem(const QString& line = QString());
    OutputItem(const QString& line, OutputItemType type);
    
    OutputItemType  type;
    QString         originalString;
    QString         shortenedString;
    bool            isDeferencable;
    QString         file;
    int             lineNo;
    int             columnNo;
    int             errNo;
};

#endif // OUTPUTITEM_H
