 
in vec3 vertex;
in vec2 uv;

varying vec2 coord;

void main()
{
    gl_Position = vec4(vertex, 1.0);
    coord = uv;
}
