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


#ifndef PREFERENCESWIDGET_H
#define PREFERENCESWIDGET_H

#include <QDialog>
#include <QListView>
#include <QStackedWidget>
#include <QAbstractButton>
#include <QDialogButtonBox>

#include "Preferences/Panels/APreferencePanel.h"

class OpenGLWidget;

class PreferencesWidget : public QDialog
{
  Q_OBJECT
public:
  PreferencesWidget();
  ~PreferencesWidget();
  
  void 	enableApply();
  
private:
  void 	initPreferences();
  
  void 	modifyPreferences(bool);

public slots: 
  void 	onSelectionChanged(QItemSelection);
  
  void 	accept();
  void 	cancel();
  void 	apply(QAbstractButton*);
  
public:
  enum		PanelList
  {
    General = 0,
    ShaderExtensions
  };
  
private:
  QListView*				_listView;
  QStackedWidget*			_panel;
  std::vector<APreferencePanel*>	_panels;	
  QDialogButtonBox*			_buttons;
};

#endif // PREFERENCESWIDGET_H
