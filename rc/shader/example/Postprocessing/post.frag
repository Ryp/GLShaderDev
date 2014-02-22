#version 430 core

in vec2 coord;

out vec4 color;

uniform sampler2D tex;
uniform float time;

void main()
{
  vec2 texcoord = coord;

  texcoord.x += sin(texcoord.y * 4 * 3 * 3.14159 + time * 10) / 100;
  color = texture(tex, texcoord);
}
