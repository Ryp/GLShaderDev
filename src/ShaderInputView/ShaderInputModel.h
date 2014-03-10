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

#ifndef SHADERINPUTMODEL_H
#define SHADERINPUTMODEL_H

#include <QAbstractItemModel>

#include "InputItem/IShaderInputItem.h"
#include "Project/IInputItemManager.h"

class ShaderInputModel : public QAbstractListModel
{
  Q_OBJECT
public:
  ShaderInputModel(IInputItemManager* itemManager, QObject* parent = 0);
  ~ShaderInputModel();

public:
  void	addItem(IShaderInputItem* item);

public:
  Qt::ItemFlags	flags(const QModelIndex& index) const;
  QVariant	data(const QModelIndex& index, int role) const;
  int		rowCount(const QModelIndex& parent = QModelIndex()) const;

private:
  IInputItemManager::InputItems&	_items;
};

#endif // SHADERINPUTMODEL_H
