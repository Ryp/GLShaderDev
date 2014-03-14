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
#include <QToolBar>
#include <QTreeView>

#include "ShaderStagesView.h"
#include "StagesModel.h"
#include "GL/Shader/ShaderObject.h"

ShaderStagesView::ShaderStagesView(QWidget* parent)
: QWidget(parent),
  _view(new QTreeView),
  _stageModel(0)
{
  QVBoxLayout*	vLayout = new QVBoxLayout;
  QToolBar*	toolbar = new QToolBar;

  toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
  toolbar->setIconSize(QSize(16, 16));
  toolbar->addAction(QIcon(":/list-add.png"), tr("&Add"), this, SLOT(addStage()));
  toolbar->addAction(QIcon(":/list-remove.png"), tr("&Remove"), this, SLOT(delStage()));

  _view->setRootIsDecorated(false);

  vLayout->setSpacing(0);
  vLayout->setMargin(0);
  vLayout->addWidget(toolbar);
  vLayout->addWidget(_view);

  setLayout(vLayout);
}

ShaderStagesView::~ShaderStagesView() {}

void ShaderStagesView::setStagesManager(IStagesManager* stagesManager)
{
  if (!_stageModel)
  {
    _stageModel = new StagesModel(this);
    _view->setModel(_stageModel);
  }
  _stageModel->setStagesManager(stagesManager);
}

void ShaderStagesView::addStage()
{
  // FIXME Better UI

  _stageModel->addShaderObject(ShaderObject::VertexShader, "../rc/shader/light.v.glsl");
  _stageModel->addShaderObject(ShaderObject::FragmentShader, "../rc/shader/light.f.glsl");
}

void ShaderStagesView::delStage()
{
  QModelIndexList idxList = _view->selectionModel()->selectedIndexes();

  if (idxList.size() > 0)
    _stageModel->delShaderObject(idxList[0]);
}
