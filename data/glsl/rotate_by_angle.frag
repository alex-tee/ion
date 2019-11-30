#version 120

uniform sampler2D sampler;

varying vec2 tex_coord0;

void main()
{
  gl_FragColor =
    texture2D (sampler, tex_coord0);
  gl_FragColor = vec4 (1.0, 0.0, 0.0, 1.0);
}
