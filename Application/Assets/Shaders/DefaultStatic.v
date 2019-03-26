#version 330 core

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

uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_cameraPosition;


void main()
{
vec4 fragPos = u_model * vec4(inPosition,1);

gl_Position = u_projection * u_view * fragPos;

Textcoords = inTextcoords;

Normal = vec3(u_model * vec4(normalize(inNormals),0.0));
Tangent = vec3(u_model * vec4(normalize(inTangent),0.0));
Binormal = vec3(u_model * vec4(normalize(-inBinormal),0.0));

CameraPosition = u_cameraPosition;
FragPosition = fragPos.xyz;

}