#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec4 d;

void main( void )
{
	d = abs(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position);
	d = d / 6;
	d[3] = 1.0;
	
  gl_Position = gl_in[0].gl_Position / 4;
	gl_Position[3] = 1.0;
	EmitVertex();

  gl_Position = gl_in[1].gl_Position / 4;
	gl_Position[3] = 1.0;
	EmitVertex();

  gl_Position = gl_in[2].gl_Position / 4;
	gl_Position[3] = 1.0;
	EmitVertex();

	EndPrimitive();
}
