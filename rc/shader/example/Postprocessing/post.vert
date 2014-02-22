#version 430 core

in vec3 vertex;
in vec2 uv;

out vec2 coord;

void main()
{
    gl_Position = vec4(vertex, 1.0);
    coord = uv;
}
