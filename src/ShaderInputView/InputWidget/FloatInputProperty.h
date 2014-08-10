#ifndef FLOATINPUTPROPERTY_H
#define FLOATINPUTPROPERTY_H

#include "ShaderInputView/InputWidget/AShaderInputProperty.h"

class QtProperty;
class QtAbstractPropertyBrowser;

class FloatInputItem;

class FloatInputProperty : public AShaderInputProperty
{
    Q_OBJECT
public:
    FloatInputProperty(FloatInputItem* inputItem, QtAbstractPropertyBrowser* editor, QtProperty* parent);
    ~FloatInputProperty() = default;

private:
    QtProperty* _floatProperty;
};

#endif // FLOATINPUTPROPERTY_H
