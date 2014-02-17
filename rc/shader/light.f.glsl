#version 430 core

layout(location = 0, index = 0) out vec4 fragColor;

uniform sampler2D texture;
uniform float time;

in vec3 n;
in vec4 d;
in vec2 UV_out;

void main(void)
{
    fragColor = d * dot(vec3(1.0, 1.0, 1.0), n) * 0 + texture2D(texture, UV_out).rgba * dot(vec3(1.0, 1.0, 1.0), n) * ((cos(time * 9) / 2) + 1);
}
