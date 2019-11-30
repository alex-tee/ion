#version 430

/* screen size we can use to convert the coordinates
 * from screen space to [-1...1] */
uniform vec2 screen;

/* angle to rotate by, or 0 to not rotate */
uniform float angle;

/* vertex position in screen coordinates */
attribute vec2 position;

/* texture coordinate in ([0...1],[0...1]) */
attribute vec2 tex_coord;

/* tex coordinate to pass to fragment shader */
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
  tex_coord0 = tex_coord;

  /* rotate if necessary */
  vec2 mypos = position.xy;
  if (angle > 0.1 || angle < -0.1)
    {
      mypos = rotate (vec2 (0, 0), angle);
      mypos = mypos + position.xy;
    }

  /* convert to shader coordinates [-1...1] on each
   * axis */
  gl_Position =
    vec4 (
      (mypos.x / screen.x) * 2 - 1.0,
      (mypos.y / screen.y) * 2 - 1.0,
      0.0, 1.0);;
}
