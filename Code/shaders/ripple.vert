attribute vec3 in_Position;
attribute vec4 in_Color;
attribute vec2 in_TexCoord;
attribute vec3 in_Normal;

varying vec2 ex_Position;
varying vec4 ex_Color;
varying vec2 ex_TexCoord;

void main()
{
	gl_Position = vec4(in_Position, 1.0);
	ex_Position = in_Position.xy;
	ex_TexCoord = in_TexCoord;
}