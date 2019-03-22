#version 330 core

layout(location=0) in vec3 pos;


uniform mat4 mvp;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main()
{
gl_Position = mvp* vec4(pos,1);
}