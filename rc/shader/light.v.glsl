#version 420 core

in vec3 vertex;
in vec3 normal;

out vec3 n;
out vec4 d;

uniform mat4 MVP;

void main(void)
{
  gl_Position = MVP * vec4(vertex, 1.0);
	
	d = abs(gl_Position);
  d = d / 8;
  d[3] = 1.0;

  n = vec4(MVP * vec4(normal, 1.0)).xyz;
}
