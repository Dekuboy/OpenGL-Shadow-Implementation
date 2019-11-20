varying vec4 ex_Color;
uniform sampler2D in_Texture;
varying vec2 ex_TexCoord;
void main()
{
	vec4 tex = texture2D(in_Texture, ex_TexCoord);
	if (tex.a <= 0)	discard;	
	gl_FragColor = tex;
}