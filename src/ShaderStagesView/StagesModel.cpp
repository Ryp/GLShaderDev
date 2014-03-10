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

#include <QFileInfo>

#include "GL/ShaderUtils.h"
#include "StagesModel.h"

StagesModel::StagesModel(QObject* parent)
: QAbstractItemModel(parent),
  _stagesManager(0)
{}

StagesModel::~StagesModel() {}

void StagesModel::setStagesManager(IStagesManager* stagesManager)
{
  emit QAbstractItemModel::beginResetModel();
  _stagesManager = stagesManager;
  emit QAbstractItemModel::endResetModel();
}

void StagesModel::addShaderObject(ShaderObject::ShaderType type, const QString& filename)
{
  emit QAbstractItemModel::beginResetModel();
  _stagesManager->addShaderObject(type, filename);
  emit QAbstractItemModel::endResetModel();
}

void StagesModel::delShaderObject(ShaderObject::ShaderType type)
{
  emit QAbstractItemModel::beginResetModel();
  _stagesManager->delShaderObject(type);
  emit QAbstractItemModel::endResetModel();
}

void StagesModel::delShaderObject(const QModelIndex& index)
{
  if (index.isValid()
    && index.row() >= 0
    && index.row() < rowCount())
  {
    IStagesManager::Stages::const_iterator it = _stagesManager->getStages().begin();
    for (int i = 0; i < index.row(); ++i)
      ++it;
    emit QAbstractItemModel::beginResetModel();
    _stagesManager->delShaderObject(it->first);
    emit QAbstractItemModel::endResetModel();
  }
}

QVariant StagesModel::data(const QModelIndex& index, int role) const
{
  if (index.isValid()
    && index.row() >= 0
    && index.row() < rowCount()
    && index.column() >= 0
    && index.column() < columnCount())
  {
    IStagesManager::Stages::const_iterator it = _stagesManager->getStages().begin();
    for (int i = 0; i < index.row(); ++i)
      ++it;
    if (role == Qt::DisplayRole)
    {
      if (index.column() == 0)
	return (ShaderUtils::getShaderString(it->first));
      if (index.column() == 1)
      {
	QFileInfo nfo(it->second);
	return (nfo.fileName());
      }
    }
  }
  return (QVariant());
}

QVariant StagesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    if (section == 0)
      return ("Type");
    else if (section == 1)
      return ("File");
  }
  return QVariant();
}

int StagesModel::columnCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return (2);
  return (0);
}

int StagesModel::rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return (_stagesManager->getStages().size());
  return (0);
}

QModelIndex StagesModel::parent(const QModelIndex& child) const
{
  static_cast<void>(child);

  return (QModelIndex());
}

QModelIndex StagesModel::index(int row, int column, const QModelIndex& parent) const
{
  static_cast<void>(parent);

  if (column >= 0 && column <= columnCount())
    return (createIndex(row, column));
  return (QModelIndex());
}
