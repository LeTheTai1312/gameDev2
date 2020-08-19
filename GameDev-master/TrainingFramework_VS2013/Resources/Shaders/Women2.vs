attribute vec3 a_posL;
attribute vec3 a_colr;
attribute vec4 a_position;
attribute vec2 a_uv;
varying vec4 v_color;
uniform mat4 u_mvpMatrix;


varying vec2 v_uv;

void main()
{
gl_Position = u_mvpMatrix * vec4(a_posL, 1.0);
v_uv = a_uv;
}
   