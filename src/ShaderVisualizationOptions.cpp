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

#include <iostream> // FIXME
#include "ShaderVisualizationOptions.h"
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QColorDialog>
#include <QMessageBox>
#include <QPalette>

ShaderVisualizationOptions::ShaderVisualizationOptions(QWidget *parent)
: QWidget(parent),
  _bgrPicker(new QPushButton("Caca"))
{
  QFormLayout*	layout = new QFormLayout;

//   _bgrPicker->setFlat(true);
  layout->addRow(new QLabel("Background Color:"), _bgrPicker);

  connect(_bgrPicker, SIGNAL(clicked(bool)), this, SLOT(backgroundColorButtonClicked()));
  setLayout(layout);
}

ShaderVisualizationOptions::~ShaderVisualizationOptions() {}

void ShaderVisualizationOptions::backgroundColorButtonClicked()
{
  QString	textColorName;
  QPalette	palette = _bgrPicker->palette();
  QColor	color = QColorDialog::getColor(palette.color(QPalette::Background), this, "Text Color", QColorDialog::DontUseNativeDialog);

  if (color.isValid())
  {
    textColorName = color.name();
    palette.setColor(QPalette::Background, color);
    _bgrPicker->setStyleSheet("QPushButton { background-color: " + textColorName + "; outline: none; }");
    _bgrPicker->setText(textColorName);

    emit backgroundColorChanged(color);
  }
}
