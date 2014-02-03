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

#include <QBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>

#include "NewFileDialog.h"
#include "GL/Shader/ShaderObject.h"

NewFileDialog::NewFileDialog(QWidget *parent)
: QDialog(parent),
  _shaderCombo(new QComboBox),
  _folderLineEdit(new QLineEdit),
  _fileNameLineEdit(new QLineEdit),
  _newButton(new QPushButton(QIcon(":/document-new.png"), tr("&New"))),
  _cancelButton(new QPushButton(QIcon(":/dialog-cancel.png"), tr("&Cancel"))),
  _browseButton(new QPushButton(QIcon(":/document-open-folder.png"), tr("&Browse...")))
{
  QGroupBox* typeGroupBox = new QGroupBox(tr("Properties"));
  QGroupBox* locationGroupBox = new QGroupBox(tr("File Location"));

  QFormLayout* propertiesLayout = new QFormLayout;
  propertiesLayout->setAlignment(Qt::AlignLeft);
  _fileNameLineEdit->setPlaceholderText(tr("Shader Identifier..."));
  propertiesLayout->addRow(tr("Identifier:"), _fileNameLineEdit);
  _shaderCombo->insertItem(0, tr("Vertex Shader"), ShaderObject::VertexShader);
  _shaderCombo->insertItem(1, tr("Tesselation Evaluation Shader"), ShaderObject::TesselationControlShader);
  _shaderCombo->insertItem(2, tr("Tesselation Evaluation Shader"), ShaderObject::TesselationEvaluationShader);
  _shaderCombo->insertItem(3, tr("Geometry Shader"), ShaderObject::GeometryShader);
  _shaderCombo->insertItem(4, tr("Fragment Shader"), ShaderObject::FragmentShader);
  propertiesLayout->addRow(tr("Type:"), _shaderCombo);

  QHBoxLayout* locationLayout = new QHBoxLayout;
  locationLayout->addWidget(new QLabel(tr("Location:")));
  _folderLineEdit->setPlaceholderText(tr("Folder..."));
  _folderLineEdit->setMinimumWidth(300);
  locationLayout->addWidget(_folderLineEdit);
  locationLayout->addWidget(_browseButton);

  QBoxLayout* buttonsLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  buttonsLayout->setAlignment(Qt::AlignRight);
  buttonsLayout->addWidget(_newButton);
  buttonsLayout->addWidget(_cancelButton);

  locationGroupBox->setLayout(locationLayout);
  typeGroupBox->setLayout(propertiesLayout);

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(typeGroupBox);
  mainLayout->addWidget(locationGroupBox);
  mainLayout->addLayout(buttonsLayout);

  connect(_browseButton, SIGNAL(clicked()), this, SLOT(browseFolder()));
  connect(_newButton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

  _newButton->setDefault(true);
  setWindowTitle(tr("New Shader File"));
}

NewFileDialog::~NewFileDialog() {}

const QString& NewFileDialog::getNewFileName() const
{
  return (_file);
}

ShaderObject::ShaderType NewFileDialog::getNewFileType() const
{
  return (_type);
}

void NewFileDialog::accept()
{
  QString	file;
  QString	folder;

  file = _fileNameLineEdit->text();
  folder = _folderLineEdit->text();

  if (file.isEmpty())
    QMessageBox::warning(this, tr("Error"), tr("Empty Identifier"));
  else if (file.contains(QDir::separator()))
    QMessageBox::warning(this, tr("Error"), tr("Identifier cannot contain '/' caracters"));
  else if (folder.isEmpty())
    QMessageBox::warning(this, tr("Error"), tr("Empty Folder Path"));
  else
  {
    if (!folder.endsWith('/'))
      folder.append('/');
    _type = static_cast<ShaderObject::ShaderType>(_shaderCombo->itemData(_shaderCombo->currentIndex()).toInt());
    _file = folder + file;
    QDialog::accept();
  }
}

void NewFileDialog::browseFolder()
{
  QString folder = QFileDialog::getExistingDirectory(this);
  if (folder.isEmpty())
    return ;
  _folderLineEdit->setText(folder);
}
