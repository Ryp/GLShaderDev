#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <list>
#include "Shader/ShaderProgram.h"

class ShaderManager
{
  static const int DefautSize = 10;
public:
  ShaderManager(unsigned sizeLimit = DefautSize);
  ~ShaderManager();

public:
  void	pushShader(const ShaderProgram& program);

private:
  ShaderManager(const ShaderManager& other);
  ShaderManager& operator=(const ShaderManager& other);

private:
  unsigned			_sizeLimit;
  std::list<ShaderProgram>	_shaders;
};

#endif // SHADERMANAGER_H
