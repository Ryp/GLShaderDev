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

#ifndef SHADERVISUALIZATIONOPTIONS_H
#define SHADERVISUALIZATIONOPTIONS_H

#include <QWidget>

class QPushButton;

class ShaderVisualizationOptions : public QWidget
{
  Q_OBJECT
public:
  ShaderVisualizationOptions(QWidget *parent = 0);
  ~ShaderVisualizationOptions();

signals:
  void	backgroundColorChanged(QColor color);

private slots:
  void	backgroundColorButtonClicked();

private:
  QPushButton*	_bgrPicker;
};

#endif // SHADERVISUALIZATIONOPTIONS_H
