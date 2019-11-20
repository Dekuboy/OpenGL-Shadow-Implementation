uniform float in_Time;
uniform sampler2D in_Texture;
uniform vec3 in_Centre;
uniform vec3 in_Shock;

varying vec2 ex_TexCoord;
varying vec2 ex_Position;

void main()
{
	vec2 texCoord = ex_TexCoord;
	float distance = distance(ex_TexCoord, in_Centre);
	if ((distance >= (in_Time - in_Shock.z)) && 
		(distance <= (in_Time + in_Shock.z)))
	{
		float diff = (distance - in_Time);
		float powDiff = 1.0 - pow(abs(diff * in_Shock.x), in_Shock.y);
		diff *= powDiff;
		vec2 diffTC = normalize(texCoord - in_Centre);
		texCoord += (diffTC * diff);
	}
	gl_FragColor = texture2D(in_Texture, texCoord);
}