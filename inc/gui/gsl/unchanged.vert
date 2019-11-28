#version 130

void main()
{
  gl_Position = ftransform();
  gl_FrontColor = gl_Color;
  //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
