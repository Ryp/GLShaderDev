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

// #include <qtpropertymanager.h>
// #include <qteditorfactory.h>
// #include <qttreepropertybrowser.h>
// #include <qtbuttonpropertybrowser.h>
// #include <qtgroupboxpropertybrowser.h>

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

//   QtBoolPropertyManager *boolManager = new QtBoolPropertyManager(this);
//   QtIntPropertyManager *intManager = new QtIntPropertyManager(this);
//   QtStringPropertyManager *stringManager = new QtStringPropertyManager(this);
//   QtSizePropertyManager *sizeManager = new QtSizePropertyManager(this);
//   QtRectPropertyManager *rectManager = new QtRectPropertyManager(this);
//   QtSizePolicyPropertyManager *sizePolicyManager = new QtSizePolicyPropertyManager(this);
//   QtEnumPropertyManager *enumManager = new QtEnumPropertyManager(this);
//   QtGroupPropertyManager *groupManager = new QtGroupPropertyManager(this);
//
//   QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(this);
//   QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(this);
//   QtSliderFactory *sliderFactory = new QtSliderFactory(this);
//   QtScrollBarFactory *scrollBarFactory = new QtScrollBarFactory(this);
//   QtLineEditFactory *lineEditFactory = new QtLineEditFactory(this);
//   QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(this);
//
//   QtAbstractPropertyBrowser *editor1 = new QtTreePropertyBrowser();
//   editor1->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
//   editor1->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
//   editor1->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
//   editor1->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
//   editor1->setFactoryForManager(enumManager, comboBoxFactory);
//
//
//   QtProperty *item0 = groupManager->addProperty("QObject");
//   editor1->addProperty(item0);
//
//   vLayout->addWidget(editor1);

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
