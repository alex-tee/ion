#version 430

/* this is the currently bound texture */
uniform sampler2D sampler;

/* tex coordinate passed from vertex shader */
varying vec2 tex_coord0;

/* equivalent to gl_FragColor */
out vec4 out_color;

void main()
{
  out_color =
    texture2D (sampler, tex_coord0);
}
