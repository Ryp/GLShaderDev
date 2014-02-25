#version 330

in vec3 vertex;
in vec3 normal;

out vec3 n;

uniform mat4 MVP;

void main(void)
{
    gl_Position = MVP * vec4(vertex, 1.0);
		n = normal;
}
