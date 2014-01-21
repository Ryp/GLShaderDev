#version 420 core

layout(location = 0, index = 0) out vec4 fragColor;

in vec3 n;
in vec4 d;

void main(void)
{
    fragColor = d * dot(vec3(1.0, -1.0, 1.0), n);
}
