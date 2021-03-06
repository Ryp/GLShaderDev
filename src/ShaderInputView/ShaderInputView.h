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

#ifndef SHADERINPUTVIEW_H
#define SHADERINPUTVIEW_H

#include <QWidget>

#include "InputItem/ShaderInputFactory.h"
#include "Project/IInputItemManager.h"

class QtAbstractPropertyBrowser;
class QtGroupPropertyManager;
class QtProperty;

class ShaderProject;
class ShaderInputModel;

QT_BEGIN_NAMESPACE
class QListView;
QT_END_NAMESPACE

class ShaderInputView : public QWidget
{
    Q_OBJECT
public:
    ShaderInputView(QWidget* parent = 0);
    ~ShaderInputView();

public:
    void    setInputItemManager(IInputItemManager* itemManager);

private slots:
    void    createTexture();
    void    createFloat();

private:
    QListView*          _view;
    ShaderInputModel*   _model;
    ShaderInputFactory  _inputFactory;
    IInputItemManager*  _inputManager;
    QtAbstractPropertyBrowser*  _editor;
    QtProperty*         _rootProperty;
    QtGroupPropertyManager* _groupMgr;
};

#endif // SHADERINPUTVIEW_H
