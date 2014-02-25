#version 420 core

in vec3 vertex;

out vec3 vPosition;

void main()
{
  vPosition = vertex;
}
