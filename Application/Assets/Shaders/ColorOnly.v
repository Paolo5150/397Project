#version 430 core

layout(location =0 ) in vec3 pos;

layout (std140) uniform CameraMatrices
{
	mat4 projection;
	mat4 view;

};


uniform mat4 mvp;



void main()
{
gl_Position = mvp * vec4(pos,1);
}