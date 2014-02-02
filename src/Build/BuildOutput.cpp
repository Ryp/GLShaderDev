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
#include <QtGui/QTreeView>
#include <QtGui/QHeaderView>

#include "BuildOutput.h"
#include "OutputModel.h"
#include "OutputDelegate.h"

BuildOutput::BuildOutput(QWidget* parent)
: QWidget(parent),
  _outputModel(new OutputModel(this)),
  _outputDelegate(new OutputDelegate(this))
{
  QHBoxLayout* layout = new QHBoxLayout(this);
  layout->setSpacing(0);
  layout->setMargin(0);

  _outputView = new QTreeView(this);
  _outputView->header()->hide();
  _outputView->setRootIsDecorated(false);
  QFont ft = this->font();
  ft.setFamily("Monospace");
  _outputView->setFont(ft);
  _outputView->setModel(_outputModel);
  _outputView->setItemDelegate(_outputDelegate);

  layout->addWidget(_outputView);

  connect(_outputView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(activate(const QModelIndex&)));
}

BuildOutput::~BuildOutput() {}

OutputModel* BuildOutput::getModel()
{
  return (_outputModel);
}

void BuildOutput::activate(const QModelIndex& index)
{
  if (index.isValid() && index.row() < _outputModel->rowCount())
  {
    OutputItem item = _outputModel->getItem(index.row());
    if (!item.isDeferencable)
      return;
    emit dereferencableItemActivated(item.file, item.lineNo, item.columnNo);
  }
}
