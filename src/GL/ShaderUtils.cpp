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

#include "ShaderUtils.h"

typedef struct {
  ShaderObject::ShaderType	type;
  QString			name;
} ShaderType;

static const ShaderType types[ShaderUtils::ShaderTypes + 1] = {
  { ShaderObject::VertexShader, "Vertex" },
  { ShaderObject::TesselationControlShader, "TesselationControl" },
  { ShaderObject::TesselationEvaluationShader, "TesselationEvaluation" },
  { ShaderObject::GeometryShader, "Geometry" },
  { ShaderObject::FragmentShader, "Fragment" },
  { ShaderObject::ComputeShader, "Compute" },
  { ShaderObject::None, "" }
};

bool ShaderUtils::isValidType(ShaderObject::ShaderType type)
{
  if (!type)
    return (false);
  for (int i = 0; i < ShaderTypes; ++i)
  {
    if (types[i].type == type)
      return (true);
  }
  return (false);
}

const QString& ShaderUtils::getShaderString(ShaderObject::ShaderType type)
{
  for (int i = 0; i < ShaderTypes; ++i)
  {
    if (types[i].type == type)
      return (types[i].name);
  }
  return (types[ShaderTypes].name);
}

ShaderObject::ShaderType ShaderUtils::getShaderType(const QString& string)
{
  for (int i = 0; i < ShaderTypes; ++i)
  {
    if (types[i].name == string)
      return (types[i].type);
  }
  return (types[ShaderTypes].type);
}
