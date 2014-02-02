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

#include "Exceptions/GlsdException.hpp"
#include "OutputModel.h"

OutputModel::OutputModel(QObject* parent)
: QAbstractListModel(parent)
{}

OutputModel::~OutputModel() {}

void OutputModel::addItem(const OutputItem& item)
{
  emit QAbstractListModel::beginInsertRows(QModelIndex(), _outputItems.size(), _outputItems.size());
  _outputItems.push_back(item);
  emit QAbstractItemModel::endInsertRows();
}

void OutputModel::addItems(const std::list<OutputItem>& items)
{
  emit QAbstractListModel::beginInsertRows(QModelIndex(), _outputItems.size(), _outputItems.size());
  for (std::list<OutputItem>::const_iterator it = items.begin(); it != items.end(); ++it)
    _outputItems.push_back(*it);
  emit QAbstractItemModel::endInsertRows();
}

void OutputModel::clear()
{
  emit QAbstractItemModel::beginResetModel();
  _outputItems.clear();
  emit QAbstractItemModel::endResetModel();
}

const OutputItem& OutputModel::getItem(int idx) const
{
  if (idx < 0 || idx >= static_cast<int>(_outputItems.size()))
    throw (GlsdException("Bad item index"));
  return (_outputItems.at(idx));
}

QVariant OutputModel::data(const QModelIndex& index, int role) const
{
  if (index.isValid() && index.row() >= 0 && index.row() < rowCount() && index.column() == 0)
  {
    if (role == Qt::DisplayRole)
      return (_outputItems.at(index.row()).shortenedString);
    else if (role == OutputItemTypeRole)
      return (_outputItems.at(index.row()).type);
  }
  return QVariant();
}

int OutputModel::rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return (_outputItems.size());
  return (0);
}
