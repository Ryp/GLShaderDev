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

#ifndef SHADERINPUTDELEGATE_H
#define SHADERINPUTDELEGATE_H

#include <QStyledItemDelegate>

class AInputItemEditorWidget;

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

class ShaderInputDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  ShaderInputDelegate(QObject* parent = 0);
  ~ShaderInputDelegate();

public:
  QWidget*	createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
  void		setEditorData(QWidget* editor, const QModelIndex& index) const;
  void		setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
  void		updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
  void		paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
  QSize		sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

public:
  AInputItemEditorWidget*	_testWidget;
};

#endif // SHADERINPUTDELEGATE_H
