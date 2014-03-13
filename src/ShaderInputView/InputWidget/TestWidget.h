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

#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

#include "AInputItemEditorWidget.h"

class FloatInputItem;

QT_BEGIN_NAMESPACE
class QDoubleSpinBox;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class TestWidget : public AInputItemEditorWidget
{
  Q_OBJECT
public:
  TestWidget(QWidget* parent = 0);
  ~TestWidget();

public:
  void	setCurrentItem(IShaderInputItem* item);
  void	pullChangesFromItem();
  void	pushChangesToItem();

public slots:
  void	reload();

signals:
  void	editingFinished();

private:
  FloatInputItem*	_item;
  QDoubleSpinBox*	_spinBox;
  QLineEdit*		_lineEdit;
  QPushButton*		_reloadButton;
};

#endif // TESTWIDGET_H
