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

#include <vector>
#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <string.h>

#include "ModelLoader.h"
#include "Exceptions/ModelLoaderException.hpp"

ModelLoader::ModelLoader()
{
  _parsers["obj"] = &ModelLoader::loadOBJ;
}

ModelLoader::~ModelLoader() {}

Model* ModelLoader::load(std::string filename)
{
  Model*	model = nullptr;
  std::ifstream	file;
  std::size_t	extensionLength;
  std::string	extension;

  if ((extensionLength = filename.find_last_of(".")) == std::string::npos)
    throw (ModelLoaderException("Invalid file name \'" + filename + "\'"));
  extension = filename.substr(extensionLength + 1);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
  if (_parsers[extension] == nullptr)
    throw (ModelLoaderException("Unknown file extension \'" + extension + "\'"));
  file.open(filename);
  if (!file.good())
    throw (ModelLoaderException("Could not open file \'" + filename + "\'"));
  model = ((*this).*(_parsers[extension]))(file);
  file.close();
  return (model);
}

Model* ModelLoader::loadOBJ(std::ifstream& src)
{
  Model*		model = new Model;
  std::string		line;
  std::stringstream	ss;

  glm::vec3		tmpVec3;
  glm::vec2		tmpVec2;
  glm::uvec3		vIdx;

  std::vector<glm::vec3>	vertices;
  std::vector<glm::vec3>	normals;
  std::vector<glm::vec2>	uvs;
  std::vector<glm::uvec3>	indexes;

  while (std::getline(src, line))
  {
    ss.clear();
    ss.str(line);
    ss >> line;
    if (line == "v")
    {
      ss >> tmpVec3[0] >> tmpVec3[1] >> tmpVec3[2];
      vertices.push_back(tmpVec3);
    }
    else if (line == "vn")
    {
      ss >> tmpVec3[0] >> tmpVec3[1] >> tmpVec3[2];
      normals.push_back(tmpVec3);
    }
    else if (line == "vt")
    {
      ss >> tmpVec2[0] >> tmpVec2[1];
      uvs.push_back(tmpVec2);
    }
    else if (line == "f")
    {
      std::string val;
      std::size_t pos;
      /*std::cout << "Parsing line: " << ss.str() << std::endl;
      */for (int i = 0; i < 3; ++i)
      {
	ss >> line;
// 	std::cout << "Parsing token: " << line << std::endl;
	for (int j = 0; j < 3; ++j)
	{
	  val = line.substr(0, line.find_first_of('/'));
	  /*std::cout << "val=" << line << std::endl;
	  */if (!val.empty())
	    vIdx[j] = abs(std::stoul(val)) - 1;
	  else
	    vIdx[j] = 0;
	  if ((pos = line.find_first_of('/')) != std::string::npos)
	    line = line.substr(pos + 1);
	  else
	    line = "";
	}/*
	std::cout << "Parsed IDX: " << vIdx[0] << " " << vIdx[1] << " " << vIdx[2] << std::endl;*/
	indexes.push_back(vIdx);
      }
      /*
      if (ss.str() != "")
      {
	vIdx[1] = vIdx[2];
	ss >> line;
	line = line.substr(0, line.find_first_of('/'));
	vIdx[2] = abs(std::stoul(line)) - 1;
	_indexes.push_back(vIdx);
      }
      */
    }
  }

  model->_hasUVs = !(uvs.empty());
  model->_hasNormals = !(normals.empty());

  if (vertices.empty() || indexes.empty())
    throw (ModelLoaderException("Empty model"));

  // CW Winding test
  if (model->_hasNormals)
  {
    glm::vec3 a = vertices[indexes[1][0]] - vertices[indexes[0][0]];
    glm::vec3 b = vertices[indexes[2][0]] - vertices[indexes[0][0]];
    glm::vec3 n = normals[indexes[0][2]] + normals[indexes[1][2]] + normals[indexes[2][2]];
    if (glm::dot(glm::cross(a, b), n) < 0.0f)
    {
      glm::vec3 t;
      for (unsigned i = 0; (i + 2) < indexes.size(); i += 3)
      {
	t = indexes[i + 1];
	indexes[i + 1] = indexes[i + 2];
	indexes[i + 2] = t;
      }
      std::clog << "Model has been reverted" << std::endl;
    }
  }

  for (unsigned i = 0; i < indexes.size(); ++i)
  {
    model->_vertices.push_back(vertices[indexes[i][0]]);
    if (model->_hasUVs)
      model->_uvs.push_back(uvs[indexes[i][1]]);
    if (model->_hasNormals)
      model->_normals.push_back(normals[indexes[i][2]]);
  }

  return (model);
}
