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

#include "ShaderInputDelegate.h"
#include "ShaderInputModel.h"

#include "InputWidget/TestWidget.h" // FIXME test
#include "InputItem/FloatInputItem.h" // FIXME test

ShaderInputDelegate::ShaderInputDelegate(QObject* parent)
: QStyledItemDelegate(parent),
  _testWidget(new TestWidget)
{}

ShaderInputDelegate::~ShaderInputDelegate()
{
  _testWidget->deleteLater();
}

QWidget* ShaderInputDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  static_cast<void>(option);

  if (dynamic_cast<FloatInputItem*>(static_cast<IShaderInputItem*>(index.internalPointer())))
  {
    qDebug() << "Editor created";
    return (new TestWidget(parent));
  }
  else
    return (0);
}

void ShaderInputDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  AInputItemEditorWidget*	editorWidget = static_cast<AInputItemEditorWidget*>(editor);

  if (editor)
  {
    editorWidget->setCurrentItem(static_cast<IShaderInputItem*>(index.internalPointer()));
    editorWidget->pullChangesFromItem();
  }
  else
    QStyledItemDelegate::setEditorData(editor, index);
}

void ShaderInputDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  AInputItemEditorWidget*	editorWidget = static_cast<AInputItemEditorWidget*>(editor);
  ShaderInputModel*		inputModel = static_cast<ShaderInputModel*>(model);

  if (editor)
  {
    editorWidget->pushChangesToItem();
    inputModel->notifyDataChange(index);
  }
  else
    QStyledItemDelegate::setModelData(editor, model, index);
}

void ShaderInputDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  static_cast<void>(index);

  if (editor)
    editor->setGeometry(option.rect);
}

void ShaderInputDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  QStyledItemDelegate::paint(painter, option, index);
}

QSize ShaderInputDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  return QStyledItemDelegate::sizeHint(option, index) + QSize(0, 10);
}
