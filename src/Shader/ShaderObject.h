#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <string>
#include <GL/gl.h>

class ShaderObject
{
public:
  enum ShaderType {
    None = 0,
    VertexShader = GL_VERTEX_SHADER,
    TesselationControlShader = GL_TESS_CONTROL_SHADER,
    TesselationEvaluationShader = GL_TESS_EVALUATION_SHADER,
    GeometryShader = GL_GEOMETRY_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
    ComputeShader = GL_COMPUTE_SHADER
  };

public:
  ShaderObject();
  ~ShaderObject();

public:
  bool			compile(const std::string& code, ShaderType type);
  void			destroy();
  GLuint		getHandle() const;
  ShaderType		getType() const;
  const std::string&	getErrorLog() const;
  bool			isCompiled() const;

private:
  GLuint		_handle;
  ShaderType		_type;
  std::string		_log;
  bool			_isCompiled;
};

#endif // SHADEROBJECT_H
