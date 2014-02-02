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

#ifndef OUTPUTMODEL_H
#define OUTPUTMODEL_H

#include <list>
#include <QtCore/QAbstractListModel>

#include "OutputItem.h"

class OutputModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum CustomRoles {
    OutputItemTypeRole = Qt::UserRole + 1
  };

public:
  OutputModel(QObject* parent = 0);
  ~OutputModel();

public:
  void	addItem(const OutputItem& item);
  void	addItems(const std::list<OutputItem>& items);
  void	clear();

  const OutputItem&	getItem(int idx) const;

  // QAbstractListModel
  QVariant	data(const QModelIndex& index, int role) const;
  int		rowCount(const QModelIndex& parent = QModelIndex()) const;

private:
  std::vector<OutputItem>	_outputItems;
};

#endif // OUTPUTMODEL_H
