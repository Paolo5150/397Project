#version 330 core

layout(location=0) in vec3 inPosition;


uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;


void main()
{
gl_Position = u_mvp* vec4(inPosition,1);
}