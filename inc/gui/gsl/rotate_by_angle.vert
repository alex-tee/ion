#version 130

/* angle to rotate with */
uniform float _angle;
varying vec2 mypos;

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
  mypos = gl_Vertex.xy - vec2(-0.5f,-0.5f);
  mypos = rotate (mypos, _angle);
  mypos = mypos + vec2(0.5f,0.5f);
  gl_Position = vec4 (mypos, gl_Vertex.z, 1.0);
}
