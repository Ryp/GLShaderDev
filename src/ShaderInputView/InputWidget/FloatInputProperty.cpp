#include "FloatInputProperty.h"

#include <ShaderInputView/InputItem/FloatInputItem.h>

#include <QtDoublePropertyManager>
#include <qteditorfactory.h>

FloatInputProperty::FloatInputProperty(FloatInputItem* inputItem, QtAbstractPropertyBrowser* editor, QtProperty* parent)
:   AShaderInputProperty(inputItem, editor, parent)
{
    QtDoublePropertyManager* doubleManager = new QtDoublePropertyManager(this);
    QtDoubleSpinBoxFactory* doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);

    editor->setFactoryForManager(doubleManager, doubleSpinBoxFactory);

    _floatProperty = doubleManager->addProperty("value");

    parent->addSubProperty(_floatProperty);

    doubleManager->setValue(_floatProperty, inputItem->getValue());
}

