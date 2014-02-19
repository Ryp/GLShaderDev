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

#ifndef SHADERSTAGESVIEW_H
#define SHADERSTAGESVIEW_H

#include <list>
#include <map>

#include <QWidget>

class StagesModel;

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
QT_END_NAMESPACE

class ShaderStagesView : public QWidget
{
  Q_OBJECT
public:
  ShaderStagesView(QWidget* parent = 0);
  ~ShaderStagesView();

public:
  std::list<std::pair<int, QString> >	getShaderConfig() const;

private:
  StagesModel*				_stageModel;
  std::map<int, QTreeWidgetItem*>	_stages;
};

#endif // SHADERSTAGESVIEW_H
