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

#ifndef STAGESMODEL_H
#define STAGESMODEL_H

#include <QAbstractItemModel>

#include "Project/ShaderProject.h"

class StagesModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  StagesModel(QObject* parent = 0);
  ~StagesModel();

public:
  void	setProject(ShaderProject* project);
  void	addShaderObject(ShaderObject::ShaderType type, const QString& filename);
  void	delShaderObject(ShaderObject::ShaderType type);
  void	delShaderObject(const QModelIndex& index);

public:
  QVariant	data(const QModelIndex& index, int role) const;
  QVariant 	headerData(int section, Qt::Orientation orientation, int role) const;
  int		columnCount(const QModelIndex& parent = QModelIndex()) const;
  int		rowCount(const QModelIndex& parent = QModelIndex()) const;
  QModelIndex	parent(const QModelIndex& child) const;
  QModelIndex	index(int row, int column, const QModelIndex& parent = QModelIndex()) const;

private:
  ShaderProject*	_project;
};

#endif // STAGESMODEL_H
