#version 430 core
#define MAX_LIGHTS 10

out vec4 FragColor; 

in vec2 Textcoords;
in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPosition;
in vec3 CameraPosition;
in vec3 FragPositionTS;
in vec3 CameraPositionTS;
in float HasNormalMap;
in vec3 dirLightsTS[MAX_LIGHTS];
in vec3 pointLightsTS[MAX_LIGHTS];
in vec4 clipSpace;

struct Material
{
vec3 color;
float shininess;
float UVScale;
};

// Light buffers

struct DirectionalLight
{
	mat4 lightSpace;
	vec3 position;
	vec3 rotation;
	vec3 diffuseColor;
	vec3 specularColor;
	float intensity;
};

struct PointLight
{
	vec3 position;
	vec3 rotation;
	vec3 diffuseColor;
	vec3 specularColor;
	float intensity;

};

//All directional lights
layout (std140, binding = 1) uniform AllDirectionalLights
{
	DirectionalLight allDirLights[MAX_LIGHTS];
	int activeDirectionalLights;
};

//All point lights
layout (std140, binding = 2) uniform AllPointLights
{
	PointLight allPointLights[MAX_LIGHTS];
	int activePointLights;
};

uniform Material material;
uniform sampler2D refraction0;
uniform sampler2D reflection0;
uniform sampler2D normal0;
uniform sampler2D special0; //Distortionmap
uniform vec3 AmbientLight;
uniform float timer;

vec3 NormalToUse;
vec3 FragPosToUse;
vec3 CamPosToUse;

vec3 CalculatePointLights(vec3 nm);
vec3 CalculateDirectionalLights(vec3 nm);

void main()
{
    vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
   
    vec2 dudvTexture = texture(special0,vec2(Textcoords.x + timer/50.0f,Textcoords.y + timer/50.0f) * material.UVScale*4.0).rg * 2.0 - 1.0;
	vec2 dudvTexture2 = texture(special0,vec2(Textcoords.x - timer/50.0f,Textcoords.y + timer/50.0f) * material.UVScale*4.0).rg * 2.0 - 1.0;
	
	vec2 totalDistortion = 0.005 * dudvTexture + 0.005 * dudvTexture2;
   
    vec3 reflectionColor = texture(reflection0,totalDistortion + vec2(ndc.x,1.0 - ndc.y)).rgb;
    vec3 refractionColor = texture(refraction0,totalDistortion + ndc).rgb;

    vec3 normalMap = texture(normal0,totalDistortion + Textcoords * material.UVScale).rgb *2.0 -1.0;
    vec3 normalMap2 = texture(normal0,totalDistortion - Textcoords * material.UVScale*1.5f).rgb *2.0 -1.0;
	
   
	NormalToUse = normalMap;
	FragPosToUse = FragPositionTS;
	CamPosToUse = CameraPositionTS;

   
    vec3 DirLights = CalculateDirectionalLights(normalMap) * CalculateDirectionalLights(normalMap2);
    vec3 PointLights = CalculatePointLights(normalMap) * CalculatePointLights(normalMap2);

    vec3 total = (AmbientLight + DirLights + PointLights) * refractionColor* material.color;

	gl_FragColor =  vec4(total,1.0);

} 

vec3 CalculateDirectionalLights(vec3 nm)
{
	vec3 totalColor = vec3(0,0,0);

	int i = 0;
	for(; i < MAX_LIGHTS; i++)
	{
		if(i >= activeDirectionalLights) break;
		
		//Specular
		vec3 lightdir = normalize(dirLightsTS[i]);
		vec3 fragToCam = normalize(CamPosToUse - FragPosToUse);
		vec3 reflection = reflect(lightdir,nm);
		
		float spec = pow(max(dot(fragToCam, reflection), 0.0),material.shininess );
		vec3 specular =  spec * allDirLights[i].specularColor ; 
		totalColor+=specular;
		
		//diffuse
		lightdir = normalize(allDirLights[i].rotation);
		float d = max(0.0,dot(-lightdir,Normal));
		vec3 diffuseColor = allDirLights[i].diffuseColor * d;
		diffuseColor *= allDirLights[i].intensity;
		totalColor += diffuseColor;	
	
	}
	return totalColor;
}

vec3 CalculatePointLights(vec3 nm)
{
	vec3 totalColor = vec3(0,0,0);

	int i = 0;
	for(; i < MAX_LIGHTS; i++)
	{
	if(i >= activePointLights) break;
	
		//Specular
		vec3 lightToFragTS = FragPosToUse - pointLightsTS[i];
		float distance = length(lightToFragTS);
		float attenuation = allPointLights[i].intensity / distance ;
		vec3 lightdir = normalize(lightToFragTS);
		vec3 fragToCam = normalize(CamPosToUse - FragPosToUse);
		vec3 reflection = reflect(lightdir,nm);
		
		float spec = pow(max(dot(fragToCam, reflection), 0.0),material.shininess );
		vec3 specular =  spec * allPointLights[i].specularColor ; 
		totalColor += specular * attenuation;
		
		//diffuse
		
		
		float d = max(0.5,dot(-normalize(lightdir),nm));
		vec3 diffuseColor = allPointLights[i].diffuseColor * d;		
		totalColor += diffuseColor * attenuation ;	
	}

	return totalColor;
}