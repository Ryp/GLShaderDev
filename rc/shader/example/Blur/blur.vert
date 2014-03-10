#version 330 compatibility

in vec3 vertex;
in vec2 uv;

void main()
{
    gl_Position = vec4(vertex, 1.0);
		gl_TexCoord[0] = vec4(vec2(uv.x, 1.0 - uv.y), 0.0, 0.0);
}
