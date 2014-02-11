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

#ifndef APREFERENCEPANEL_H
#define APREFERENCEPANEL_H

#include <QVBoxLayout>
#include <QWidget>
#include <QStandardItem>

#include "../SettingsList.h"

class PreferencesWidget;

class APreferencePanel : public QWidget
{
  Q_OBJECT
  
public:
  APreferencePanel(PreferencesWidget*, const QIcon&, const QString&);
  virtual ~APreferencePanel();
  
  QVBoxLayout*		getLayout() const;
  QStandardItem*	getItem() const;
  SettingsList&		getSettings();
  bool 			isChanged() const;
  
  void 			refresh();
  
  virtual void 		init() = 0;
  
protected:
  PreferencesWidget*	_parent;
  QVBoxLayout*		_layout;
  QStandardItem*	_item;
  bool 			_changed;
  SettingsList		_settings;
};

#endif // APREFERENCEPANEL_H
