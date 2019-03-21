#version 330 core

out vec4 FragColor; 


struct Material
{
vec3 color;
};

uniform Material material;


void main()
{
   
gl_FragColor =  vec4(1.0,0.0,0.0,1.0);


} 