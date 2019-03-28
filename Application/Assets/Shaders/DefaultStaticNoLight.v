#version 430 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;


out vec2 Textcoords;

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

}