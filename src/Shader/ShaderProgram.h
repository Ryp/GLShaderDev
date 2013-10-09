#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <map>
#include <GL/gl.h>

#include "ShaderObject.h"

class ShaderProgram
{
public:
  ShaderProgram();
  ~ShaderProgram();

public:
  void			attach(const ShaderObject& object);
  void			detach(const ShaderObject& object);
  bool			link();
  void			bind();
  void			destroy();
  GLuint		getHandle() const;
  const std::string&	getLog() const;
  GLuint		getAttribLocation(const std::string& name) const;
  GLuint		getUniformLocation(const std::string& name) const;

private:
  void			retrieveLocations();

private:
  std::string			_log;
  std::map<std::string, GLuint>	_attribs;
  std::map<std::string, GLuint>	_uniforms;
  GLuint			_handle;
};

#endif // SHADERPROGRAM_H
