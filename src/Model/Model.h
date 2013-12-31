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

#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <glm/glm.hpp>

#include "GLHeaders.hpp"

class Model
{
  friend class ModelLoader;
public:
  Model();
  ~Model();

public:
  void		debugDump();
  unsigned	getTriangleCount();
  void		computeTangents();

public:
  const void*	getVertexBuffer() const;
  unsigned	getVertexBufferSize() const;

  const void*	getUVBuffer() const;
  unsigned	getUVBufferSize() const;

  const void*	getNormalBuffer() const;
  unsigned	getNormalBufferSize() const;

  const void*	getIndexBuffer() const;
  unsigned	getIndexBufferSize() const;

  const void*	getTangentBuffer() const;
  unsigned	getTangentBufferSize() const;

  const void*	getBitangentBuffer() const;
  unsigned	getBitangentBufferSize() const;

private:
  bool				_isIndexed;
  bool				_hasUVs;
  bool				_hasNormals;

private:
  std::vector<glm::vec3>	_vertices;
  std::vector<glm::vec3>	_normals;
  std::vector<glm::vec2>	_uvs;
  std::vector<unsigned int>	_indexes;

  std::vector<glm::vec3>	_tangents;
  std::vector<glm::vec3>	_bitangents;
};

#endif // MODEL_H
