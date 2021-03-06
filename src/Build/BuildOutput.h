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

#ifndef BUILDOUTPUT_H
#define BUILDOUTPUT_H

#include <QWidget>
#include <QAbstractListModel>

#include "Build/OutputParser.h"

class OutputDelegate;
class OutputModel;

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

class BuildOutput : public QWidget
{
  Q_OBJECT
public:
  BuildOutput(QWidget* parent = 0);
  ~BuildOutput();

public:
  OutputModel*	getModel();

private slots:
  void	activate(const QModelIndex& index);

signals:
  void	dereferencableItemActivated(const QString& file, int line, int column);

private:
  QTreeView*		_outputView;
  OutputModel*		_outputModel;
  OutputDelegate*	_outputDelegate;
};

#endif // BUILDOUTPUT_H
