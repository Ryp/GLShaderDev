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
#include <QToolButton>

#include "ShaderInputModel.h"
#include "ShaderInputView.h"
#include "InputWidget/AShaderInputProperty.h"
#include "InputWidget/FloatInputProperty.h"
#include "InputItem/FloatInputItem.h"
#include "InputItem/TextureInputItem.h"

#include <qtpropertymanager.h>
#include <qteditorfactory.h>
#include <qttreepropertybrowser.h>
#include <qtbuttonpropertybrowser.h>
#include <qtgroupboxpropertybrowser.h>
#include <qtvariantproperty.h>

ShaderInputView::ShaderInputView(QWidget* parent)
:   QWidget(parent),
    _view(new QListView),
    _model(0)
{
    QVBoxLayout*    vLayout = new QVBoxLayout;
    QMenu*          inputTypeMenu = new QMenu;

    //   toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //   toolbar->setIconSize(QSize(16, 16));

    QToolButton* tb = new QToolButton;
    tb->setText("Add &Item");
    //   tb->setIcon(QIcon(":/list-add.png"));
    tb->setPopupMode(QToolButton::ToolButtonPopupMode::InstantPopup);
    //   toolbar->addAction(tb);
    inputTypeMenu->setTitle("MEC");
    inputTypeMenu->addAction(tr("&Texture..."), this, SLOT(createTexture()));
    inputTypeMenu->addAction(tr("&Float..."), this, SLOT(createFloat()));
    tb->setMenu(inputTypeMenu);
    vLayout->addWidget(tb);

    vLayout->setSpacing(0);
    vLayout->setMargin(0);

    QtBoolPropertyManager *boolManager = new QtBoolPropertyManager(this);
    QtIntPropertyManager *intManager = new QtIntPropertyManager(this);
    QtDoublePropertyManager* doubleManager = new QtDoublePropertyManager(this);
    QtStringPropertyManager *stringManager = new QtStringPropertyManager(this);
    QtSizePropertyManager *sizeManager = new QtSizePropertyManager(this);
    QtRectPropertyManager *rectManager = new QtRectPropertyManager(this);
    QtSizePolicyPropertyManager *sizePolicyManager = new QtSizePolicyPropertyManager(this);
    QtEnumPropertyManager *enumManager = new QtEnumPropertyManager(this);
    _groupMgr = new QtGroupPropertyManager(this);

    QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(this);
    QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(this);
    QtDoubleSpinBoxFactory* doubleSpinBox = new QtDoubleSpinBoxFactory(this);
    QtSliderFactory *sliderFactory = new QtSliderFactory(this);
    QtScrollBarFactory *scrollBarFactory = new QtScrollBarFactory(this);
    QtLineEditFactory *lineEditFactory = new QtLineEditFactory(this);
    QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(this);

    _editor = new QtTreePropertyBrowser();
    _editor->setFactoryForManager(boolManager, checkBoxFactory);
    _editor->setFactoryForManager(intManager, spinBoxFactory);
    _editor->setFactoryForManager(stringManager, lineEditFactory);
    _editor->setFactoryForManager(doubleManager, doubleSpinBox);
    _editor->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    _editor->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    _editor->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    _editor->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    _editor->setFactoryForManager(enumManager, comboBoxFactory);

    _rootProperty = _groupMgr->addProperty("ProjectName");
    _editor->addProperty(_rootProperty);
    vLayout->addWidget(_editor);

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
    QtProperty* prop = _groupMgr->addProperty("Texture");
    TextureInputItem* textureItem = _inputFactory.createTexture();

    _rootProperty->addSubProperty(prop);
    AShaderInputProperty* inputprop = new AShaderInputProperty(textureItem, _editor, prop);
    _model->addItem(textureItem);
}

void ShaderInputView::createFloat()
{
    QtProperty* prop = _groupMgr->addProperty("Float");
    FloatInputItem* floatItem = _inputFactory.createFloat();

    _rootProperty->addSubProperty(prop);
    AShaderInputProperty* inputprop = new FloatInputProperty(floatItem, _editor, prop);
    _model->addItem(floatItem);
}
