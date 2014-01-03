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
#include <QToolButton>
#include <QToolBar>
#include <QTreeWidget>
#include <QHeaderView>

#include "ShaderStagesView.h"
#include "Editor/CodeWidget.h"
#include "Shader/ShaderObject.h"

ShaderStagesView::ShaderStagesView(QWidget *parent)
: QWidget(parent)
{
  QVBoxLayout*	vLayout = new QVBoxLayout;
  QToolBar*	toolbar = new QToolBar;
  QTreeWidget*	tree = new QTreeWidget;

  toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
  toolbar->setIconSize(QSize(16, 16));
  toolbar->addAction(QIcon(":/list-add.png"), tr("&Add"));
  toolbar->addAction(QIcon(":/list-remove.png"), tr("&Remove"));
//   toolbar->addAction(QIcon(":/dialog-close.png"), tr("&Close"), this, SLOT(languageChange()));

  QStringList headerLabels;
  headerLabels.append("Stage");
  headerLabels.append("File");
  //   tree->header()->hide();
//   tree->setRootIsDecorated(false);
  tree->setColumnCount(2);
  tree->setHeaderLabels(headerLabels);

  QStringList rootStrings;
  rootStrings.append("MyShader");

  QTreeWidgetItem* shaderRoot = new QTreeWidgetItem(tree, rootStrings);
  shaderRoot->setExpanded(true);

  QStringList vstrings;
  vstrings.append("Vertex");
  vstrings.append("/home/ryp/Dev/C++/GLShaderDev/rc/shader/geopassthrough.vert");
  QTreeWidgetItem* vertex = new QTreeWidgetItem(shaderRoot, vstrings);
  _stages[ShaderObject::VertexShader] = vertex;

  QStringList gstrings;
  gstrings.append("Geometry");
  gstrings.append("/home/ryp/Dev/C++/GLShaderDev/rc/shader/geopassthrough.geom");
  QTreeWidgetItem* geometry = new QTreeWidgetItem(shaderRoot, gstrings);
  _stages[ShaderObject::GeometryShader] = geometry;

  QStringList fstrings;
  fstrings.append("Fragment");
  fstrings.append("/home/ryp/Dev/C++/GLShaderDev/rc/shader/geopassthrough.frag");
  QTreeWidgetItem* fragment = new QTreeWidgetItem(shaderRoot, fstrings);
  _stages[ShaderObject::FragmentShader] = fragment;


  vLayout->setSpacing(0);
  vLayout->setMargin(0);
  vLayout->addWidget(toolbar);
  vLayout->addWidget(tree);

  setLayout(vLayout);
}

ShaderStagesView::~ShaderStagesView() {}

std::list< std::pair< int, QString > >  ShaderStagesView::getShaderConfig() const
{
  std::list< std::pair< int, QString > >	list;

  for (std::map<int, QTreeWidgetItem*>::const_iterator it = _stages.begin(); it != _stages.end(); ++it)
    list.push_back(std::make_pair(it->first, it->second->text(1)));
  return (list);
}
