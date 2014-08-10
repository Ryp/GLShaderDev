#ifndef ASHADERINPUTPROPERTY_H
#define ASHADERINPUTPROPERTY_H

#include <QObject>

class QtAbstractPropertyBrowser;
class QtProperty;
class IShaderInputItem;

class AShaderInputProperty : public QObject
{
    Q_OBJECT
public:
    AShaderInputProperty(IShaderInputItem* inputItem, QtAbstractPropertyBrowser* editor, QtProperty* parent);

public slots:
    void    changed(QtProperty* property);
//     virtual void    createProperties() = 0;

protected:
    IShaderInputItem*   _inputItem;
    QtProperty*         _parentProperty;

private:
    QtProperty*         _nameProperty;
    QtProperty*         _enabledProperty;
};

#endif // ASHADERINPUTPROPERTY_H
