#version 330

layout(location = 0, index = 0) out vec4 fragColor;

in vec3 face_normal;
in vec4 d;

void main( void )
{
    fragColor = d;
}
