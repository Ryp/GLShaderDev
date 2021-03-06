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

#include "Model.h"

/* FIXME */
#include <iostream>

Model::Model()
  : _isIndexed(false),
    _hasUVs(false),
    _hasNormals(false)
{}

Model::~Model() {}

/* FIXME Rm me */
void Model::debugDump()
{
  std::cout << "Total vertices: " << _vertices.size() << std::endl;
  std::cout << "Total normals: " << _normals.size() << std::endl;
  std::cout << "Total uvs: " << _uvs.size() << std::endl;
  std::cout << "Total indexes: " << _indexes.size() << std::endl;
//   for (unsigned i = 0; i < _vertices.size(); ++i)
//     std::cout << "Vertex: " << _vertices[i][0] << " " << _vertices[i][1] << " " << _vertices[i][2] << std::endl;
//   for (unsigned i = 0; i < _normals.size(); ++i)
//     std::cout << "Normal: " << _normals[i][0] << " " << _normals[i][1] << " " << _normals[i][2] << std::endl;
//   for (unsigned i = 0; i < _uvs.size(); ++i)
//     std::cout << "UV: " << _uvs[i][0] << " " << _uvs[i][1] << std::endl;
//   for (unsigned i = 0; i < _indexes.size(); ++i)
//     std::cout << "Index: " << _indexes[i] << std::endl;
}

unsigned int Model::getTriangleCount()
{
  if (_isIndexed)
    return (_indexes.size());
  else
    return (_vertices.size() / 3);
}

void Model::computeTangents()
{
  if (_hasNormals && _hasUVs)
  {
    /* TODO Compute tangents */
  }
}

const void* Model::getVertexBuffer() const
{
  return (&_vertices[0]);
}

unsigned int Model::getVertexBufferSize() const
{
  return (_vertices.size() * sizeof(_vertices[0][0]) * 3);
}

const void* Model::getUVBuffer() const
{
  return (&_uvs[0]);
}

unsigned int Model::getUVBufferSize() const
{
  return (_uvs.size() * sizeof(_uvs[0][0]) * 2);
}

const void* Model::getNormalBuffer() const
{
  return (&_normals[0]);
}

unsigned int Model::getNormalBufferSize() const
{
  return (_normals.size() * sizeof(_normals[0][0]) * 3);
}

const void* Model::getIndexBuffer() const
{
  return (&_indexes[0]);
}

unsigned int Model::getIndexBufferSize() const
{
  return (_indexes.size() * sizeof(_indexes[0]));
}

const void* Model::getTangentBuffer() const
{
  return (&_tangents[0]);
}

unsigned int Model::getTangentBufferSize() const
{
  return (_tangents.size() * sizeof(_tangents[0][0]) * 3);
}

const void* Model::getBitangentBuffer() const
{
  return (&_bitangents[0]);
}

unsigned int Model::getBitangentBufferSize() const
{
  return (_bitangents.size() * sizeof(_bitangents[0][0]) * 3);
}
