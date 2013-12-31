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

#include <iostream>

#include <QtGui/QHBoxLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QHeaderView>

#include "BuildOutput.h"

BuildOutput::BuildOutput(QWidget* parent)
: QWidget(parent)
{
  _layout = new QHBoxLayout(this);
  _layout->setSpacing(0);
  _layout->setMargin(0);

  _list = new QTreeWidget(this);
  _list->header()->hide();
  _list->setRootIsDecorated(false);
  QFont ft = this->font();
  ft.setFamily("Monospace");
  _list->setFont(ft);

  _layout->addWidget(_list);

  connect(_list, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onDoubleClickedItem(QTreeWidgetItem*, int)));
}

BuildOutput::~BuildOutput() {}

void BuildOutput::addLine(const QString& string)
{
  QTreeWidgetItem* line = new QTreeWidgetItem(_list, QStringList(string));
  line->setTextColor(0, QColor("#006E28"));
}

void BuildOutput::addErrors(const std::list<OutputParser::Error>& errors)
{
  QTreeWidgetItem*	line;
  QStringList		strings;
  QString		error;

  for (std::list<OutputParser::Error>::const_iterator it = errors.begin(); it != errors.end(); ++it)
  {
    QString	lineString;

    if ((*it).line)
      lineString = QString(":%1:%2").arg((*it).line).arg((*it).column);
    strings.clear();
    error = QString("Error%1: %2 (#%3)").arg(lineString).arg(QString::fromStdString((*it).content)).arg((*it).errNo);
    strings.append(error);
    line = new QTreeWidgetItem(_list, strings);
    line->setTextColor(0, QColor("#BF0303"));
  }
}

void BuildOutput::clear()
{
  _list->clear();
}

void BuildOutput::onDoubleClickedItem(QTreeWidgetItem* item, int column)
{
  static_cast<void>(column);
  static_cast<void>(item);
  emit dereferencableItemActivated("/home/ryp/Dev/C++/GLShaderDev/rc/shader/simple.frag", 5, 0); // FIXME arrange data in a model
}
