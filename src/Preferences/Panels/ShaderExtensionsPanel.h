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

#ifndef SHADEREXTENSIONSPANEL_H
#define SHADEREXTENSIONSPANEL_H

#include <Preferences/Panels/APreferencePanel.h>

class ShaderExtensionsPanel : public APreferencePanel
{
Q_OBJECT

public:
  ShaderExtensionsPanel(PreferencesWidget*);
  virtual ~ShaderExtensionsPanel();

  virtual void init();
  
public slots:  
  void 		vertexShaderHasChanged(QString);
  void 		tesselationControlShaderHasChanged(QString);
  void 		tesselationEvaluationShaderHasChanged(QString);
  void 		geometryShaderHasChanged(QString);
  void 		fragmentShaderHasChanged(QString);
  void 		computeShaderHasChanged(QString);
};

#endif // SHADEREXTENSIONSPANEL_H
