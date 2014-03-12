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

#ifndef AINPUTITEMEDITORWIDGET_H
#define AINPUTITEMEDITORWIDGET_H

#include <QWidget>

class IShaderInputItem;

class AInputItemEditorWidget : public QWidget
{
  Q_OBJECT
public:
  AInputItemEditorWidget(QWidget* parent = 0);
  virtual ~AInputItemEditorWidget();

public:
  virtual void	setCurrentItem(IShaderInputItem* item) = 0;
  virtual void	pullChangesFromItem() = 0;
  virtual void	pushChangesToItem() = 0;
};

#endif // AINPUTITEMEDITORWIDGET_H
