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

#include <QtGui/QHBoxLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QHeaderView>

#include "BuildOutput.h"

BuildOutput::BuildOutput(QWidget* parent)
: QWidget(parent)
{
  _layout = new QHBoxLayout(this);
  _layout->setSpacing(0); // FIXME
  _layout->setMargin(0);

  QTreeWidget* list = new QTreeWidget(this);
  list->header()->hide();
  list->setRootIsDecorated(false);
  QFont ft = this->font();
  ft.setFamily("Monospace");
  list->setFont(ft);

  QStringList l;
  l.append("Pute");
  l.append("Negre");
//   QTreeWidgetItem* a = new QTreeWidgetItem(list, l);
//   QTreeWidgetItem* b = new QTreeWidgetItem(list, l);
  _layout->addWidget(list);

  //   connect(list, itemDoubleClicked(QTreeWidgetItem*, int), this, onLineSensitiveItem(int, int));
}

BuildOutput::~BuildOutput() {}
