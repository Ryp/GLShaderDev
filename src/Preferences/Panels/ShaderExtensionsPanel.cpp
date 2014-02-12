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

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSettings>

#include "ShaderExtensionsPanel.h"
#include "ExtensionValidator.h"
#include "../PreferencesWidget.h"

ShaderExtensionsPanel::ShaderExtensionsPanel(PreferencesWidget* parent) : APreferencePanel(parent, QIcon(":/preferences-other.png"), "Shader Extansions")
{

}

ShaderExtensionsPanel::~ShaderExtensionsPanel()
{

}

void ShaderExtensionsPanel::init()
{
  ExtensionValidator*		validator = new ExtensionValidator;
  
  //->VertexShader
  QHBoxLayout*	vertexShaderLayout = new QHBoxLayout;
  QLabel*	vertexShaderLabel = new QLabel();
  vertexShaderLabel->setText("VertexShader extension :   *.");
  vertexShaderLayout->addWidget(vertexShaderLabel);
  
  QLineEdit*	vertexShaderEditBox = new QLineEdit;
  vertexShaderEditBox->setText(_settings.getSetting("vertexShaderExt")->toString());
  vertexShaderEditBox->setValidator(validator);
  vertexShaderLayout->addWidget(vertexShaderEditBox);
  connect(vertexShaderEditBox, SIGNAL(textEdited(QString)), this, SLOT(vertexShaderHasChanged(QString)));
  _layout->addLayout(vertexShaderLayout);
  
  //->TesselationControlShader
  QHBoxLayout*	tesselationControlShaderLayout = new QHBoxLayout;
  QLabel*	tesselationControlShaderLabel = new QLabel();
  tesselationControlShaderLabel->setText("TesselationControlShader extension :   *.");
  tesselationControlShaderLayout->addWidget(tesselationControlShaderLabel);
  
  QLineEdit*	tesselationControlShaderEditBox = new QLineEdit;
  tesselationControlShaderEditBox->setText(_settings.getSetting("tesselationControlShaderExt")->toString());
  tesselationControlShaderLayout->addWidget(tesselationControlShaderEditBox);
  connect(tesselationControlShaderEditBox, SIGNAL(textEdited(QString)), this, SLOT(tesselationControlShaderHasChanged(QString)));
  _layout->addLayout(tesselationControlShaderLayout);
  
  //->TesselationEvaluationShader
  QHBoxLayout*	tesselationEvaluationShaderLayout = new QHBoxLayout;
  QLabel*	tesselationEvaluationShaderLabel = new QLabel();
  tesselationEvaluationShaderLabel->setText("TesselationEvaluationShader extension :   *.");
  tesselationEvaluationShaderLayout->addWidget(tesselationEvaluationShaderLabel);
  
  QLineEdit*	tesselationEvaluationShaderEditBox = new QLineEdit;
  tesselationEvaluationShaderEditBox->setText(_settings.getSetting("tesselationEvaluationShaderExt")->toString());
  tesselationEvaluationShaderLayout->addWidget(tesselationEvaluationShaderEditBox);
  connect(tesselationEvaluationShaderEditBox, SIGNAL(textEdited(QString)), this, SLOT(tesselationEvaluationShaderHasChanged(QString)));
  _layout->addLayout(tesselationEvaluationShaderLayout);
  
  //->GeometryShader
  QHBoxLayout*	geometryShaderLayout = new QHBoxLayout;
  QLabel*	geometryShaderLabel = new QLabel();
  geometryShaderLabel->setText("GeometryShader extension :   *.");
  geometryShaderLayout->addWidget(geometryShaderLabel);
  
  QLineEdit*	geometryShaderEditBox = new QLineEdit;
  geometryShaderEditBox->setText(_settings.getSetting("geometryShaderExt")->toString());
  geometryShaderLayout->addWidget(geometryShaderEditBox);
  connect(geometryShaderEditBox, SIGNAL(textEdited(QString)), this, SLOT(geometryShaderHasChanged(QString)));
  _layout->addLayout(geometryShaderLayout);
  
  //->FragmentShader
  QHBoxLayout*	fragmentShaderLayout = new QHBoxLayout;
  QLabel*	fragmentShaderPathLabel = new QLabel();
  fragmentShaderPathLabel->setText("FragmentShader extension :   *.");
  fragmentShaderLayout->addWidget(fragmentShaderPathLabel);
  
  QLineEdit*	fragmentShaderPathEditBox = new QLineEdit;
  fragmentShaderPathEditBox->setText(_settings.getSetting("fragmentShaderExt")->toString());
  fragmentShaderLayout->addWidget(fragmentShaderPathEditBox);
  connect(fragmentShaderPathEditBox, SIGNAL(textEdited(QString)), this, SLOT(fragmentShaderHasChanged(QString)));
  _layout->addLayout(fragmentShaderLayout);
  
  //->ComputeShader
  QHBoxLayout*	computeShaderLayout = new QHBoxLayout;
  QLabel*	computeShaderLabel = new QLabel();
  computeShaderLabel->setText("ComputeShader extension :   *.");
  computeShaderLayout->addWidget(computeShaderLabel);
  
  QLineEdit*	computeShaderEditBox = new QLineEdit;
  computeShaderEditBox->setText(_settings.getSetting("computeShaderExt")->toString());
  computeShaderLayout->addWidget(computeShaderEditBox);
  connect(computeShaderEditBox, SIGNAL(textEdited(QString)), this, SLOT(computeShaderHasChanged(QString)));
  _layout->addLayout(computeShaderLayout);
}

void ShaderExtensionsPanel::vertexShaderHasChanged(QString value)
{
  _settings.setSetting("vertexShaderExt", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtensionsPanel::tesselationControlShaderHasChanged(QString value)
{
  _settings.setSetting("tesselationControlShaderExt", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtensionsPanel::tesselationEvaluationShaderHasChanged(QString value)
{
  _settings.setSetting("tesselationEvaluationShaderExt", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtensionsPanel::geometryShaderHasChanged(QString value)
{
  _settings.setSetting("geometryShaderExt", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtensionsPanel::fragmentShaderHasChanged(QString value)
{
  _settings.setSetting("fragmentShaderExt", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtensionsPanel::computeShaderHasChanged(QString value)
{
  _settings.setSetting("computeShaderExt", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

