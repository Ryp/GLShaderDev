#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 n;
out vec3 face_normal;

out vec4 d;

void main(void)
{
	face_normal = n;

  d = abs(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position);
  d = d / 6;
  d[3] = 1.0;

  for(int i = 0; i < gl_in.length(); i++)
  {
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
}
