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

#include "TestWidget.h"

#include <QBoxLayout>
#include <QLineEdit>
#include <QSpinBox>

#include "ShaderInputView/InputItem/FloatInputItem.h"

TestWidget::TestWidget(QWidget* parent)
: AInputItemEditorWidget(parent)
{
  QBoxLayout*	layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
  
  _lineEdit = new QLineEdit;
  _spinBox = new QSpinBox;

  layout->addWidget(_lineEdit);
  layout->addWidget(_spinBox);

  setLayout(layout);

  connect(_spinBox, SIGNAL(editingFinished()), this, SIGNAL(editingFinished()));
}

TestWidget::~TestWidget() {}

void TestWidget::setCurrentItem(IShaderInputItem* item)
{
  _item = static_cast<FloatInputItem*>(item);
}

void TestWidget::pullChangesFromItem()
{
  _lineEdit->setText(_item->getInputName().c_str());
  _spinBox->setValue(_item->getValue());
}

void TestWidget::pushChangesToItem()
{
  _item->setInputName(_lineEdit->text().toStdString());
  _item->setValue(_spinBox->value());
}
