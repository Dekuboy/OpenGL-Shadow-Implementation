uniform sampler2D in_Texture;
uniform samplerCube in_DepthMap;
uniform vec3 in_Ambient;
uniform vec3 in_LightPos;
uniform float in_FarPlane;

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
	vec3 lightDir = normalize(in_LightPos - ex_FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(0.5);

	vec4 viewPos = inverse(in_View) * vec4(0, 0, 0, 1);
	vec3 viewDir = normalize(vec3(viewPos) - ex_FragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(viewDir, halfDir), 0.0), 1);

	vec3 specular = spec * vec3(0.5);

	// check if position is in shadow
	vec3 fragToLight = ex_FragPos - in_LightPos;
	float closestDepth = texture(in_DepthMap, fragToLight).r;
	closestDepth *= in_FarPlane;
	float currentDepth = length(fragToLight);

	float bias = 0.05;
	float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

	vec3 light = in_Ambient + (1.0 - shadow) * (diffuse + specular);
	gl_FragColor = tex * vec4(light, 1);
	//gl_FragColor = vec4(vec3(closestDepth / in_FarPlane), 1.0);
}