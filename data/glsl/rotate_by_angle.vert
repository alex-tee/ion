#version 130

attribute vec2 position;
attribute vec2 tex_coord;

/* angle to rotate with */
uniform float _angle;

varying vec2 tex_coord0;

mat2 rotation2d(float angle) {
  float s = sin(angle);
  float c = cos(angle);

  return mat2(
    c, -s,
    s, c
  );
}

vec2 rotate(vec2 v, float angle) {
  return rotation2d(angle) * v;
}

void main()
{
  vec4 vertex_pos =
    gl_ModelViewProjectionMatrix *
    vec4 (position, 0.0, 1.0);
  vec2 mypos = vertex_pos.xy;
  mypos = mypos - vec2(-0.5f,-0.5f);
  mypos = rotate (mypos, _angle);
  mypos = mypos + vec2(0.5f,0.5f);

  tex_coord0 = tex_coord;

  gl_Position = vec4 (mypos, 0.0, 1.0);
}
