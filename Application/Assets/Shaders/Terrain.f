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
in vec4 fragLightSpaces[MAX_LIGHTS];
in vec4 clipSpace;
in float HeightRatio;

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
uniform sampler2D diffuse0; //Sand
uniform sampler2D diffuse1; //grass
uniform sampler2D diffuse2; //Rock
uniform sampler2D special0; //blend
uniform sampler2D normal0; // rock normal map
uniform sampler2D shadowMap[MAX_LIGHTS]; //shadowmap

uniform int shadowMapCount;

uniform vec3 AmbientLight;

vec3 CalculatePointLights();
vec3 CalculateDirectionalLights();


vec3 NormalToUse;
vec3 FragPosToUse;
vec3 CamPosToUse;

vec3 dirToUse;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec3 GenerateTerrainColor()
{
    vec3 terrainColor = vec3(0.0, 0.0, 0.0);
    float height = max(0.0f,(HeightRatio));;
    float regionMin = 0.0;
    float regionMax = 1.0;
    float regionRange = 0.0;
    float regionWeight = 0.0;
    

    regionMin = -0.2f;
    regionMax = 0.3f;
    regionRange = regionMax - regionMin;
    regionWeight = (regionRange - abs(height - regionMax)) / regionRange;
    regionWeight = max(0.0, regionWeight);
    terrainColor += regionWeight * texture(diffuse0,Textcoords * material.UVScale).rgb;
	

    regionMin = 0.5f;
    regionMax = 1.0f;
    regionRange = regionMax - regionMin;
    regionWeight = (regionRange - abs(height - regionMax)) / regionRange;
    regionWeight = max(0.0, regionWeight);
    terrainColor += regionWeight * texture(diffuse2,Textcoords * material.UVScale).rgb;
	
	
    regionMin = 0.1f;
    regionMax = 0.5f;
    regionRange = regionMax - regionMin;
    regionWeight = (regionRange - abs(height - regionMax)) / regionRange;
    regionWeight = max(0.0, regionWeight);
    terrainColor += regionWeight * texture(diffuse1,Textcoords * material.UVScale).rgb;

    return terrainColor;
}

float ShadowCalculation();

void main()
{
   vec3 blendColor = texture(special0,Textcoords).rgb;
   
   vec3 sandColor = texture(diffuse0,Textcoords * material.UVScale).rgb;
   vec3 grassColor = texture(diffuse1,Textcoords * material.UVScale).rgb * blendColor.r;
   vec3 rockColor = texture(diffuse2,Textcoords * material.UVScale).rgb * (1.0 - blendColor.r);
   
 vec3 colorRatio = vec3(1,1,1) * max(0.0f,(HeightRatio+0.2f));

   vec3 DirLights =  CalculateDirectionalLights();   
   vec3 PointLights = CalculatePointLights();
   
   	float shadowFactor = ShadowCalculation();
	float shadowAlpha = max(0.0,(500 - length(FragPosition - CameraPosition)) / 500.0);
	float shadowColor = (1.0  - shadowFactor* shadowAlpha )  ;
   
   vec3 total =  shadowColor* colorRatio *(AmbientLight + DirLights + PointLights) * GenerateTerrainColor() * material.color;

	gl_FragColor =  vec4(total,1.0);

} 

float ShadowCalculation()
{

	float shadow = 0;
	for(int i=0; i < MAX_LIGHTS; i++) 
	{
	if(i >= shadowMapCount) break;
		vec3 projCoords = fragLightSpaces[i].xyz / fragLightSpaces[i].w;

		projCoords = projCoords * 0.5 + 0.5;

		float closestDepth = texture(shadowMap[i], projCoords.xy).r; 

		float currentDepth = projCoords.z;

		float bias = 0.005;
		shadow += currentDepth - bias > closestDepth  ? 0.7 : 0.0; 
	

	}

    return shadow;
} 


vec3 CalculateDirectionalLights()
{
	vec3 totalColor = vec3(0,0,0);

	int i = 0;
	for(; i < MAX_LIGHTS; i++)
	{
	if(i >= activeDirectionalLights) break;

		//Specular
		vec3 lightdir = normalize(allDirLights[i].rotation);
		vec3 fragToCam = normalize(CameraPosition - FragPosition);
		vec3 reflection = reflect(lightdir,Normal);
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

vec3 CalculatePointLights()
{
	vec3 totalColor = vec3(0,0,0);

	int i = 0;
	for(; i < MAX_LIGHTS; i++)
	{
	if(i >= activePointLights) break;
	
		//Specular

		//diffuse
		vec3 lightToFrag = FragPosition - allPointLights[i].position;
		vec3 lightdir = normalize(lightToFrag);

		float distance = length(lightToFrag);
		float attenuation = allPointLights[i].intensity / distance ;
		
		float d = max(0.0,dot(-normalize(lightdir),Normal));
		vec3 diffuseColor = allPointLights[i].diffuseColor * d;		
		totalColor += diffuseColor * attenuation ;	
	}

	return totalColor;
}