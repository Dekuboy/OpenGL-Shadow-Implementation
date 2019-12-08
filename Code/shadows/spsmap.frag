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

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

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
	float shadow = 0.0;
	float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);

	// Sample the shadow map 4 times
	for (int i=0;i<4;i++)
	{
		int index = i;
		shadow += 0.2*(1.0-texture(in_DepthMap, projCoords.xy + poissonDisk[index]/700.0,  objectDepth - bias));
	}

	vec3 light = in_Ambient + (1.0 - shadow) * (diffuse + specular);
	gl_FragColor = tex * vec4(light, 1);
}