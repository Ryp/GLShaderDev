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

#include "ShaderInputModel.h"

ShaderInputModel::ShaderInputModel(IInputItemManager* itemManager, QObject* parent)
: QAbstractListModel(parent),
  _items(itemManager->getInputItems())
{}

ShaderInputModel::~ShaderInputModel() {}

void ShaderInputModel::addItem(IShaderInputItem* item)
{
  beginInsertRows(QModelIndex(), _items.size(), _items.size());
  _items.push_back(item);
  emit QAbstractItemModel::endInsertRows();
}

void ShaderInputModel::notifyDataChange(const QModelIndex& index)
{
  emit dataChanged(index, index);
}

Qt::ItemFlags ShaderInputModel::flags(const QModelIndex& index) const
{
  static_cast<void>(index);

  return (Qt::ItemFlag::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

QVariant ShaderInputModel::data(const QModelIndex& index, int role) const
{
  int	row = index.row();

  if (index.isValid()
    && row >= 0
    && row < rowCount())
  {
    if (role == Qt::DisplayRole)
      return (QString(_items[row]->getInputName().c_str()));
    else if (role == Qt::ToolTipRole)
      return (QString(_items[row]->getInputName().c_str()));
  }
  return (QVariant());
}

int ShaderInputModel::rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return (_items.size());
  return (0);
}

QModelIndex ShaderInputModel::index(int row, int column, const QModelIndex& parent) const
{
  static_cast<void>(parent);

  if (row >= 0 && row < rowCount())
    return (createIndex(row, column, _items[row]));
  else
    return (createIndex(row, column));
}

IShaderInputItem* ShaderInputModel::getItem(const QModelIndex& index)
{
  IShaderInputItem *item = 0;

  if (index.isValid())
    item = static_cast<IShaderInputItem*>(index.internalPointer());
  return (item);
}
