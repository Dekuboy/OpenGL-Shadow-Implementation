uniform sampler2D in_Texture;
uniform sampler2D in_DepthMap;
uniform vec3 in_Ambient;
uniform vec3 in_LightPos;

uniform mat4 in_View;

varying vec4 ex_Color;
varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec4 ex_LightSpaceFragPos;
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
	vec3 projCoords = ex_LightSpaceFragPos.xyz / ex_LightSpaceFragPos.w;
	projCoords = projCoords * 0.5 + 0.5;
	float objectDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005); 
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(in_DepthMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(in_DepthMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += objectDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;

	vec3 light = in_Ambient + (1.0 - shadow) * (diffuse + specular);
	gl_FragColor = tex * vec4(light, 1);
}