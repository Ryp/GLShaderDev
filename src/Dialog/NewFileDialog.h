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

#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>

#include "GL/Shader/ShaderObject.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class NewFileDialog : public QDialog
{
  Q_OBJECT
public:
  NewFileDialog(QWidget *parent = 0);
  ~NewFileDialog();

public:
  const QString&		getNewFileName() const;
  ShaderObject::ShaderType	getNewFileType() const;

public slots:
  void	accept();
  void	browseFolder();

private:
  QString			_file;
  ShaderObject::ShaderType	_type;
  QComboBox*			_shaderCombo;
  QLineEdit*			_folderLineEdit;
  QLineEdit*			_fileNameLineEdit;
  QPushButton*			_newButton;
  QPushButton*			_cancelButton;
  QPushButton*			_browseButton;
};

#endif // NEWFILEDIALOG_H
