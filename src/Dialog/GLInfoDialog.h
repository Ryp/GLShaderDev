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

#ifndef GLINFODIALOG_H
#define GLINFODIALOG_H

#include <QDialog>

#include "GL/GLInfo.h"

class GLInfoDialog : public QDialog
{
  Q_OBJECT
public:
  GLInfoDialog(GLInfo& glInfos, QWidget *parent = 0);
  ~GLInfoDialog();

private:
  GLInfo&	_glInfo;
};

#endif // GLINFODIALOG_H
