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

#include <QSettings>
#include <QMessageBox>

#include "APreferencePanel.h"
#include "../PreferencesWidget.h"

APreferencePanel::APreferencePanel(PreferencesWidget* parent, const QIcon& icon, const QString& name) : 
  _parent(parent), _layout(new QVBoxLayout), _item(new QStandardItem(icon, name)), _changed(false), _valid(true)
{
  _item->setEditable(false);
  setLayout(_layout);
}

APreferencePanel::~APreferencePanel()
{
  if (_layout)
    delete (_layout);
  if (_item)
    delete (_item);
}


QVBoxLayout* APreferencePanel::getLayout() const
{
  return _layout;
}

QStandardItem* APreferencePanel::getItem() const
{
  return _item;
}

SettingsList& APreferencePanel::getSettings()
{
  return _settings;
}

bool APreferencePanel::isChanged() const
{
  return _changed;
}

void APreferencePanel::refresh()
{
  _changed = false;
  _valid = true;
  _errorMsg = "";
  if ( _layout != NULL )
  {
      QLayoutItem* item;
      while ( ( item = _layout->takeAt( 0 ) ) != NULL )
      {
	  delete item->widget();
	  delete item;
      }
  }
  init();
}

bool APreferencePanel::apply(bool condition)
{
  QSettings		settings;

  if (!_valid && condition)
  {
    QMessageBox::warning(this, tr("Error"), tr(_errorMsg.toStdString().c_str()));
    return _valid;
  }
  
  for (std::map<QString, QVariant*>::const_iterator i_it = _settings.getList().begin();
	i_it != _settings.getList().end(); ++i_it)
	{
	  if (condition && _valid)
	    settings.setValue((*i_it).first, *(*i_it).second);
	  else
	    _settings.setSetting((*i_it).first, new QVariant(settings.value((*i_it).first)));
	}
      
  return _valid;
}