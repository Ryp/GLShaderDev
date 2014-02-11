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

#include <QLabel>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSettings>

#include "GeneralPanel.h"
#include "../PreferencesWidget.h"

GeneralPanel::GeneralPanel(PreferencesWidget* parent): APreferencePanel(parent, QIcon(":/preferences-other.png"), "General")
{  
}

GeneralPanel::~GeneralPanel()
{
}

void GeneralPanel::init()
{
  QHBoxLayout*	recentFileLayout = new QHBoxLayout;
  
  QLabel*	recentFileLabel = new QLabel();
  recentFileLabel->setText("Number Of Recent Files kept in memory :");
  recentFileLayout->addWidget(recentFileLabel);
  QSpinBox*	recentFileEditBox = new QSpinBox;
  recentFileEditBox->setRange(1, 50);
  recentFileEditBox->setValue(_settings.getSetting("maxRecentFiles")->toInt());
  recentFileEditBox->setKeyboardTracking(false);
  recentFileLayout->addWidget(recentFileEditBox);
  
  connect(recentFileEditBox, SIGNAL(valueChanged(int)), this, SLOT(hasChanged(int)));
  
  _layout->addLayout(recentFileLayout);
}

void GeneralPanel::hasChanged(int value)
{
  _settings.setSetting("maxRecentFiles", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}
