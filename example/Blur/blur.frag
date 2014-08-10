#version 130

uniform uvec2 screenSize;
uniform sampler2D texture;
uniform float time;
uniform float b;

float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

void main()
{
	float off = cos(time * b) / 2.0 + 0.5;

  vec3 tc = vec3(1.0, 0.0, 0.0);
  if (gl_TexCoord[0].x<(off-0.01))
  {
    vec2 uv = gl_TexCoord[0].xy;
    tc = texture2D(texture, uv).rgb * weight[0];
    for (int i=1; i<3; i++)
    {
      tc += texture2D(texture, uv + vec2(offset[i])/screenSize.x, 0.0).rgb * weight[i];
      tc += texture2D(texture, uv - vec2(offset[i])/screenSize.x, 0.0).rgb * weight[i];
    }
  }
  else if (gl_TexCoord[0].x>=(off+0.01))
  {
    tc = texture2D(texture, gl_TexCoord[0].xy).rgb;
  }
  gl_FragColor = vec4(tc, 1.0);
}
