/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2014  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

PreferencesWidget::PreferencesWidget()
{
  setWindowIcon(QIcon(":/preferences-other.png"));
  setWindowTitle("Preferences");
  setMinimumSize(1000, 800);
  setModal(true);
  
  _buttons = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Ok | QDialogButtonBox::Apply);
  connect(_buttons, SIGNAL(accepted()), this, SLOT(accept()));
  connect(_buttons, SIGNAL(rejected()), this, SLOT(cancel()));
  connect(_buttons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(apply(QAbstractButton*)));
  
  _listView = new QListView;
  _listView->setFixedSize(200, 200);
  
  _panel = new QStackedWidget;
  
  QStandardItemModel*	itemModel = new QStandardItemModel(_listView);
  QStandardItem*	item1 = new QStandardItem(QIcon(":/preferences-other.png"), "test1");
  item1->setEditable(false);
  QStandardItem*	item2 = new QStandardItem(QIcon(":/preferences-other.png"), "test2");
  item2->setEditable(false);
  
  itemModel->appendRow(item1);
  itemModel->appendRow(item2);
  
  _listView->setModel(itemModel);
  
  QSplitter*	splitter = new QSplitter;
  
  QWidget*	menuList = new QWidget;
  QVBoxLayout*	menuLayout = new QVBoxLayout;
  menuLayout->addWidget(_listView);
  menuLayout->setContentsMargins(5, 5, 5, 5);
  menuList->setLayout(menuLayout);
  
  _layouts[0] = new QVBoxLayout;
  _layouts[1] = new QVBoxLayout;  
  _w[0] = new QWidget;
  _w[1] = new QWidget;
  //---->
  
  QLabel*	label1 = new QLabel(this);
  label1->setText("MENU 1");
  _layouts[0]->addWidget(label1);
  _w[0]->setLayout(_layouts[0]);
  
  QLabel*	label2 = new QLabel(this);
  label2->setText("MENU 2");
  _layouts[1]->addWidget(label2);
  _w[1]->setLayout(_layouts[1]);
  
  //<----
  
  _layouts[0]->setContentsMargins(5, 5, 5, 5);
  _layouts[1]->setContentsMargins(5, 5, 5, 5);
  
  _panel->addWidget(_w[0]);
  _panel->addWidget(_w[1]);
  _panel->setCurrentWidget(0);
  _panel->setMinimumSize(700, 700);
  QPalette pal(palette());
  _panel->setAutoFillBackground(true);
  pal.setColor(QPalette::Background, Qt::white);
  _panel->setPalette(pal);
  
  splitter->setOrientation(Qt::Horizontal);
  splitter->addWidget(menuList);
  splitter->addWidget(_panel);
  QVBoxLayout*		settingLayout = new QVBoxLayout;
  settingLayout->addWidget(splitter);
  settingLayout->addWidget(_buttons);
  
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

