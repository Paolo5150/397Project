#version 430 core
#define MAX_LIGHTS 10
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;
layout(location = 4) in vec3 inTangent;
layout(location = 5) in vec3 inBinormal;


out vec2 Textcoords;
out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;
out vec3 FragPosition;
out vec3 CameraPosition;
out float HasNormalMap;
out vec3 FragPositionTS;
out vec3 CameraPositionTS;
out vec3 dirLightsTS[MAX_LIGHTS];

uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_cameraPosition;
uniform float u_hasNormalMap;

struct DirectionalLight
{
	mat4 lightSpace;
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


void main()
{


vec4 fragPos = u_model * vec4(inPosition,1);

gl_Position = u_projection * u_view * fragPos;

Textcoords = inTextcoords;
HasNormalMap = u_hasNormalMap;
Normal = vec3(u_model * vec4(normalize(inNormals),0.0));
Tangent = vec3(u_model * vec4(normalize(inTangent),0.0));
Binormal = vec3(u_model * vec4(normalize(-inBinormal),0.0));

CameraPosition = u_cameraPosition;
FragPosition = fragPos.xyz;

//TBN matrix
if(u_hasNormalMap == 1)
{
	vec3 T = normalize(vec3(u_model * vec4(inTangent,0.0)));
	vec3 B = normalize(vec3(u_model * vec4(inBinormal,0.0)));
	vec3 N = normalize(vec3(u_model * vec4(inNormals,0.0)));
	mat3 TBN = transpose(mat3(T,B,N));
	CameraPositionTS = TBN * CameraPosition;
	FragPositionTS = TBN * FragPosition;
	
	for(int i=0; i<MAX_LIGHTS;i++)
	{
	if(i >= activeDirectionalLights) break;
	
	dirLightsTS[i] = TBN * allDirLights[i].rotation ;

	}
	
	
}	



}