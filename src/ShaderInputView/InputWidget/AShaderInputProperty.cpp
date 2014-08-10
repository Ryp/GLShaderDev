#include "AShaderInputProperty.h"

#include <QtProperty>
#include <QtBoolPropertyManager>

#include <qteditorfactory.h>

#include <iostream> // FIXME

#include <ShaderInputView/InputItem/IShaderInputItem.h>

AShaderInputProperty::AShaderInputProperty(IShaderInputItem* inputItem, QtAbstractPropertyBrowser* editor, QtProperty* parent)
:   _inputItem(inputItem),
    _parentProperty(parent)
{
    QtBoolPropertyManager *boolManager = new QtBoolPropertyManager(this);
    QtStringPropertyManager *stringManager = new QtStringPropertyManager(this);

    QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(this);
    QtLineEditFactory *lineEditFactory = new QtLineEditFactory(this);

    editor->setFactoryForManager(boolManager, checkBoxFactory);
    editor->setFactoryForManager(stringManager, lineEditFactory);

    _nameProperty = stringManager->addProperty("name");
    _enabledProperty = boolManager->addProperty("enabled");

    parent->addSubProperty(_nameProperty);
    parent->addSubProperty(_enabledProperty);

    stringManager->setValue(_nameProperty, QString::fromStdString(inputItem->getInputName()));
    boolManager->setValue(_enabledProperty, inputItem->isEnabled());
}

void AShaderInputProperty::changed(QtProperty* property)
{
    std::cout << "Changed !" << std::endl;
}
