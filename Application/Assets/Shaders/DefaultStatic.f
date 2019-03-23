#version 330 core

out vec4 FragColor; 

in vec2 Textcoords;
in vec3 Normal;
in vec3 FragPosition;
in vec3 CameraPosition;


struct Material
{
vec3 color;
};



uniform Material material;
uniform sampler2D diffuse0;


void main()
{
   
   vec3 diffuseColor = texture(diffuse0,Textcoords).rgb;
   vec3 total = diffuseColor * material.color;

	gl_FragColor =  vec4(total,1.0);


} 