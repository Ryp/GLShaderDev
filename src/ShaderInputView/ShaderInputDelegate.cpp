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

#include <QDebug> // FIXME
#include <QPainter>
#include <QLineEdit>

#include "ShaderInputDelegate.h"

ShaderInputDelegate::ShaderInputDelegate(QObject* parent)
: QStyledItemDelegate(parent)
{}

ShaderInputDelegate::~ShaderInputDelegate() {}

QWidget* ShaderInputDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  QLineEdit* lineEdit = new QLineEdit(parent);

  static_cast<void>(option);
  static_cast<void>(index);

  qDebug() << "Editor created";

  return (lineEdit);
}

void ShaderInputDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

  lineEdit->setText((index.model()->data(index, Qt::EditRole)).toString());
}

void ShaderInputDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

  model->setData(index, lineEdit->text(), Qt::EditRole);
}

void ShaderInputDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  static_cast<void>(index);

  editor->setGeometry(option.rect);
}
