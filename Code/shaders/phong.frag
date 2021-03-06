uniform sampler2D in_Texture;
uniform vec3 in_Emissive;
uniform vec3 in_Ambient;
//uniform vec3 in_LightPos;
uniform vec3 in_LightDir;

uniform mat4 in_View;

varying vec4 ex_Color;
varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;

void main()
{
	gl_FragColor = ex_Color;
	vec4 tex = texture2D(in_Texture, ex_TexCoord);

	vec3 norm = normalize(ex_Normal);
	vec3 lightDir = in_LightDir;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(0.5, 0.5, 0.5);

	vec4 viewPos = inverse(in_View) * vec4(0, 0, 0, 1);
	vec3 viewDir = normalize(vec3(viewPos) - ex_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);

	vec3 specular = spec * vec3(0.5, 0.5, 0.5);

	vec3 light = in_Emissive + in_Ambient + diffuse + specular;
	gl_FragColor = tex * vec4(light, 1);
}