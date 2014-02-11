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

#include "ShaderExtansionsPanel.h"
#include "../PreferencesWidget.h"

ShaderExtansionsPanel::ShaderExtansionsPanel(PreferencesWidget* parent) : APreferencePanel(parent, QIcon(":/preferences-other.png"), "Shader Extansions")
{

}

ShaderExtansionsPanel::~ShaderExtansionsPanel()
{

}

void ShaderExtansionsPanel::init()
{
  //->VertexShader
  QHBoxLayout*	vertexShaderLayout = new QHBoxLayout;
  QLabel*	vertexShaderLabel = new QLabel();
  vertexShaderLabel->setText("VertexShader path :");
  vertexShaderLayout->addWidget(vertexShaderLabel);
  
  QLineEdit*	vertexShaderEditBox = new QLineEdit;
  vertexShaderEditBox->setText(_settings.getSetting("vertexShaderPath")->toString());
  vertexShaderLayout->addWidget(vertexShaderEditBox);
  connect(vertexShaderEditBox, SIGNAL(textEdited(QString)), this, SLOT(vertexShaderHasChanged(QString)));
  _layout->addLayout(vertexShaderLayout);
  
  //->TesselationControlShader
  QHBoxLayout*	tesselationControlShaderLayout = new QHBoxLayout;
  QLabel*	tesselationControlShaderPathLabel = new QLabel();
  tesselationControlShaderPathLabel->setText("TesselationControlShader path :");
  tesselationControlShaderLayout->addWidget(tesselationControlShaderPathLabel);
  
  QLineEdit*	tesselationControlShaderPathEditBox = new QLineEdit;
  tesselationControlShaderPathEditBox->setText(_settings.getSetting("tesselationControlShaderPath")->toString());
  tesselationControlShaderLayout->addWidget(tesselationControlShaderPathEditBox);
  connect(tesselationControlShaderPathEditBox, SIGNAL(textEdited(QString)), this, SLOT(tesselationControlShaderHasChanged(QString)));
  _layout->addLayout(tesselationControlShaderLayout);
  
  //->TesselationEvaluationShader
  QHBoxLayout*	tesselationEvaluationShaderLayout = new QHBoxLayout;
  QLabel*	tesselationEvaluationShaderPathLabel = new QLabel();
  tesselationEvaluationShaderPathLabel->setText("TesselationEvaluationShader path :");
  tesselationEvaluationShaderLayout->addWidget(tesselationEvaluationShaderPathLabel);
  
  QLineEdit*	tesselationEvaluationShaderPathEditBox = new QLineEdit;
  tesselationEvaluationShaderPathEditBox->setText(_settings.getSetting("tesselationEvaluationShaderPath")->toString());
  tesselationEvaluationShaderLayout->addWidget(tesselationEvaluationShaderPathEditBox);
  connect(tesselationEvaluationShaderPathEditBox, SIGNAL(textEdited(QString)), this, SLOT(tesselationEvaluationShaderHasChanged(QString)));
  _layout->addLayout(tesselationEvaluationShaderLayout);
  
  //->GeometryShader
  QHBoxLayout*	geometryShaderLayout = new QHBoxLayout;
  QLabel*	geometryShaderPathLabel = new QLabel();
  geometryShaderPathLabel->setText("GeometryShader path :");
  geometryShaderLayout->addWidget(geometryShaderPathLabel);
  
  QLineEdit*	geometryShaderPathEditBox = new QLineEdit;
  geometryShaderPathEditBox->setText(_settings.getSetting("geometryShaderPath")->toString());
  geometryShaderLayout->addWidget(geometryShaderPathEditBox);
  connect(geometryShaderPathEditBox, SIGNAL(textEdited(QString)), this, SLOT(geometryShaderHasChanged(QString)));
  _layout->addLayout(geometryShaderLayout);
  
  //->FragmentShader
  QHBoxLayout*	fragmentShaderLayout = new QHBoxLayout;
  QLabel*	fragmentShaderPathLabel = new QLabel();
  fragmentShaderPathLabel->setText("FragmentShader path :");
  fragmentShaderLayout->addWidget(fragmentShaderPathLabel);
  
  QLineEdit*	fragmentShaderPathEditBox = new QLineEdit;
  fragmentShaderPathEditBox->setText(_settings.getSetting("fragmentShaderPath")->toString());
  fragmentShaderLayout->addWidget(fragmentShaderPathEditBox);
  connect(fragmentShaderPathEditBox, SIGNAL(textEdited(QString)), this, SLOT(fragmentShaderHasChanged(QString)));
  _layout->addLayout(fragmentShaderLayout);
  
  //->ComputeShader
  QHBoxLayout*	computeShaderLayout = new QHBoxLayout;
  QLabel*	computeShaderPathLabel = new QLabel();
  computeShaderPathLabel->setText("ComputeShader path :");
  computeShaderLayout->addWidget(computeShaderPathLabel);
  
  QLineEdit*	computeShaderPathEditBox = new QLineEdit;
  computeShaderPathEditBox->setText(_settings.getSetting("computeShaderPath")->toString());
  computeShaderLayout->addWidget(computeShaderPathEditBox);
  connect(computeShaderPathEditBox, SIGNAL(textEdited(QString)), this, SLOT(computeShaderHasChanged(QString)));
  _layout->addLayout(computeShaderLayout);
}

void ShaderExtansionsPanel::vertexShaderHasChanged(QString value)
{
  _settings.setSetting("vertexShaderPath", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtansionsPanel::tesselationControlShaderHasChanged(QString value)
{
  _settings.setSetting("tesselationControlShaderPath", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtansionsPanel::tesselationEvaluationShaderHasChanged(QString value)
{
  _settings.setSetting("tesselationEvaluationShaderPath", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtansionsPanel::geometryShaderHasChanged(QString value)
{
  _settings.setSetting("geometryShaderPath", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtansionsPanel::fragmentShaderHasChanged(QString value)
{
  _settings.setSetting("fragmentShaderPath", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

void ShaderExtansionsPanel::computeShaderHasChanged(QString value)
{
  _settings.setSetting("computeShaderPath", new QVariant(value));
  _parent->enableApply();
  _changed = true;
}

