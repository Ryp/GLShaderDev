#version 430 core

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec3 n;
out vec4 d;
out vec2 UV_out;

uniform mat4 MVP;

void main(void)
{
	mat4	mat;
	mat[0] = vec4(1.0, 0.0, 0.0, 0.0);
	mat[1] = vec4(0.0, 1.0, 0.0, 0.0);
	mat[2] = vec4(0.0, 0.0, 1.0, 0.0);
	mat[3] = vec4(0.0, 0.0, 0.0, 1.0);
  gl_Position = MVP * mat * vec4(vertex, 1.0);
	
	d = abs(gl_Position);
  d = d / 20;
  d[3] = 1.0;


	UV_out = uv;
  n = vec4(MVP * vec4(normal, 1.0)).xyz;
}
