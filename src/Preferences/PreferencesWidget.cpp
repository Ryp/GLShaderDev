/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without een the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */


#include <QMessageBox>
#include <QSplitter>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "PreferencesWidget.h"
#include "Dialog/GLInfoDialog.h"
#include "Preferences/PreferenceListItemDelegate.h"
#include "Preferences/Panels/GeneralPanel.h"


PreferencesWidget::PreferencesWidget()
{
  setWindowIcon(QIcon(":/preferences-other.png"));
  setWindowTitle("Preferences");
  setModal(true);

  _buttons = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Ok | QDialogButtonBox::Apply);
  connect(_buttons, SIGNAL(accepted()), this, SLOT(accept()));
  connect(_buttons, SIGNAL(rejected()), this, SLOT(cancel()));
  connect(_buttons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(apply(QAbstractButton*)));

  _listView = new QListView;
  _listView->setFixedWidth(205);
  _listView->setMinimumHeight(3 * 100);
  _listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  _panel = new QStackedWidget;
  _panels.push_back(new GeneralPanel);

  QStandardItemModel*	itemModel = new QStandardItemModel(_listView);
  
  itemModel->appendRow(_panels.at(General)->getItem());

  _listView->setModel(itemModel);
  _listView->setItemDelegate(new PreferenceListItemDelegate(_listView));
  _listView->setAutoScroll(false);

  QWidget*	menuList = new QWidget;
  QVBoxLayout*	menuLayout = new QVBoxLayout;
  menuLayout->addWidget(_listView);
  menuLayout->setContentsMargins(5, 5, 5, 5);
  menuList->setLayout(menuLayout);

  _panel->addWidget(_panels.at(General)->getWidget());
  _panel->setCurrentIndex(0);
  QPalette pal(palette());
  _panel->setAutoFillBackground(true);
  pal.setColor(QPalette::Background, Qt::white);
  _panel->setPalette(pal);

  QGridLayout*		settingLayout = new QGridLayout;
  
  settingLayout->addWidget(menuList, 0, 0);
  settingLayout->addWidget(_panel, 0, 1);
  settingLayout->addWidget(_buttons, 1, 1);
  settingLayout->setColumnStretch(1, 1);

  setLayout(settingLayout);

  connect(_listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onSelectionChanged(QItemSelection)));
}

PreferencesWidget::~PreferencesWidget() {}

void PreferencesWidget::onSelectionChanged(QItemSelection item)
{
  if (item.indexes().count() < 2)
    _panel->setCurrentIndex(item.indexes().first().row());
}

void PreferencesWidget::accept()
{
  QDialog::accept();
}

void PreferencesWidget::cancel()
{
  QDialog::reject();
}

void PreferencesWidget::apply(QAbstractButton* button)
{
  if (_buttons->standardButton(button) == QDialogButtonBox::Apply)
  {
      QMessageBox::about(this, tr("Preferences"), tr("Are you sure ?"));
  }
}

