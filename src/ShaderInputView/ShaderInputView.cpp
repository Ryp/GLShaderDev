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

#include <QDebug> // FIXME

#include <QToolBar>
#include <QBoxLayout>
#include <QMenu>
#include <QListView>

#include "ShaderInputModel.h"
#include "ShaderInputDelegate.h"
#include "ShaderInputView.h"

ShaderInputView::ShaderInputView(QWidget* parent)
: QWidget(parent),
  _view(new QListView),
  _model(0)
{
  QVBoxLayout*	vLayout = new QVBoxLayout;
  QToolBar*	toolbar = new QToolBar;
  QMenu*	inputTypeMenu = new QMenu;

  toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
  toolbar->setIconSize(QSize(16, 16));

  QAction* menuAction = toolbar->addAction(QIcon(":/list-add.png"), tr("Add Input"));
  inputTypeMenu->addAction(tr("&Texture..."), this, SLOT(createTexture()));
  inputTypeMenu->addAction(tr("&Float..."), this, SLOT(createFloat()));
  menuAction->setMenuRole(QAction::TextHeuristicRole);
  menuAction->setMenu(inputTypeMenu);

  _view->setItemDelegate(new ShaderInputDelegate(this));

  vLayout->setSpacing(0);
  vLayout->setMargin(0);
  vLayout->addWidget(toolbar);
  vLayout->addWidget(_view);

  setLayout(vLayout);

}

ShaderInputView::~ShaderInputView() {}

void ShaderInputView::setInputItemManager(IInputItemManager* itemManager)
{
  if (!_model)
  {
    _model = new ShaderInputModel(itemManager, this);
    _view->setModel(_model);
  }
}

void ShaderInputView::createTexture()
{
  // TODO Show dialog
  _model->addItem(_inputFactory.createTexture());
  qDebug() << "New texture";
}

void ShaderInputView::createFloat()
{
  // TODO Show dialog
  _model->addItem(_inputFactory.createFloat());
  qDebug() << "New float";
}
