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

#include "StagesModel.h"

StagesModel::StagesModel(QObject* parent)
: QAbstractItemModel(parent)
{}

StagesModel::~StagesModel() {}

QVariant StagesModel::data(const QModelIndex& index, int role) const
{
  if (index.isValid()
    && index.row() >= 0
    && index.row() < rowCount()
    && index.column() >= 0
    && index.column() < columnCount())
  {
    if (role == Qt::DisplayRole)
      return ("Text");// FIXME
  }
  return QVariant();
}

int StagesModel::columnCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return (2);// FIXME
  return (0);
}

int StagesModel::rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return (2);// FIXME
  return (0);
}

QModelIndex StagesModel::parent(const QModelIndex& child) const
{
  static_cast<void>(child);

  return (QModelIndex()); // FIXME
}

QModelIndex StagesModel::index(int row, int column, const QModelIndex& parent) const
{
  static_cast<void>(row);
  static_cast<void>(column);
  static_cast<void>(parent);

  return (QModelIndex()); // FIXME
}
