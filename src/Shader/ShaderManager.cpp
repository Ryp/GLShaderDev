#include "ShaderManager.h"

ShaderManager::ShaderManager(unsigned sizeLimit)
  : _sizeLimit(sizeLimit)
{}

ShaderManager::~ShaderManager() {}

void ShaderManager::pushShader(const ShaderProgram& program)
{
  _shaders.push_front(program);
  if (_shaders.size() > _sizeLimit)
    _shaders.pop_back();
}

ShaderManager::ShaderManager(const ShaderManager& other)
{
  static_cast<void>(other);
}

ShaderManager& ShaderManager::operator=(const ShaderManager& other)
{
  static_cast<void>(other);
  return (*this);
}
