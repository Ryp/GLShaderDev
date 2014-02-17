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
  _labels["vertexShaderExt"] = "VertexShader";
  _labels["tesselationControlShaderExt"] = "TesselationControlShader";
  _labels["tesselationEvaluationShaderExt"] = "TesselationEvaluationShader";
  _labels["geometryShaderExt"] = "GeometryShader";
  _labels["fragmentShaderExt"] = "FragmentShader";
  _labels["computeShaderExt"] = "ComputeShader";
}

ShaderExtensionsPanel::~ShaderExtensionsPanel()
{

}

void ShaderExtensionsPanel::init()
{
  ExtensionValidator*		validator = new ExtensionValidator;
  
  for (QHash<QString, QString>::iterator it = _labels.begin(); it != _labels.end(); ++it)
  {
    QHBoxLayout*	layout = new QHBoxLayout;
    QLabel*		label = new QLabel();
    label->setText(it.value() + " extension :   *.");
    layout->addWidget(label);
    
    QLineEdit*		editBox = new QLineEdit;
    editBox->setText(_settings.getSetting(it.key())->toString());
    editBox->setValidator(validator);
    layout->addWidget(editBox);
    if (it.key() == "vertexShaderExt")
      connect(editBox, SIGNAL(textEdited(QString)), this, SLOT(vertexShaderHasChanged(QString)));
    else if (it.key() == "tesselationControlShaderExt")
      connect(editBox, SIGNAL(textEdited(QString)), this, SLOT(tesselationControlShaderHasChanged(QString)));
    else if (it.key() == "tesselationEvaluationShaderExt")
      connect(editBox, SIGNAL(textEdited(QString)), this, SLOT(tesselationEvaluationShaderHasChanged(QString)));
    else if (it.key() == "geometryShaderExt")
      connect(editBox, SIGNAL(textEdited(QString)), this, SLOT(geometryShaderHasChanged(QString)));
    else if (it.key() == "fragmentShaderExt")
      connect(editBox, SIGNAL(textEdited(QString)), this, SLOT(fragmentShaderHasChanged(QString)));
    else if (it.key() == "computeShaderExt")
      connect(editBox, SIGNAL(textEdited(QString)), this, SLOT(computeShaderHasChanged(QString)));
    connect(editBox, SIGNAL(editingFinished()), this, SLOT(duplicatorz()));
    _layout->addLayout(layout);
  }
}

QVariant* ShaderExtensionsPanel::delDuplicate(QVariant* varToChange)
{
  QStringList		splited = varToChange->toString().split(";");
  splited.removeDuplicates();
  return new QVariant(splited.join(";"));
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

void ShaderExtensionsPanel::duplicatorz()
{
  QStringList		boxes = {	"vertexShaderExt",
					"tesselationControlShaderExt",
					"tesselationEvaluationShaderExt",
					"geometryShaderExt",
					"fragmentShaderExt",
					"computeShaderExt"
				};
				
  // Remove duplicates from same editBox.
  for (int i = 0; i < boxes.size(); ++i)
    _settings.setSetting(boxes[i], delDuplicate(_settings.getSetting(boxes[i])));
			
  // Pop errorBox if there is duplicates in different editBoxes.
  for (int i = 0; i < boxes.size(); ++i)
  {
    QString 		current = _settings.getSetting(boxes[i])->toString();
    QStringList		currentTab = current.split(";");
    
    for (int j = 0; j < boxes.size(); ++j)
    {
      if (i != j)
      {
	QString		inTest = _settings.getSetting(boxes[j])->toString();
	QStringList	inTab = inTest.split(";");
	
	for (int k = 0; k < currentTab.size(); ++k)
	{
	  if (inTab.contains(currentTab.at(k)))
	  {
	    _valid = false;
	    _errorMsg = "There is some duplicates. Check your synthax in " + _labels[boxes[i]] + " and " +_labels[boxes[j]] + ".";
	  }
	}
      }
    }
  }
}