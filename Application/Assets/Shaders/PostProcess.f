#version 430 core
#define MAX_LIGHTS 10

out vec4 FragColor; 
in vec2 Textcoords;


uniform sampler2D diffuse0;
uniform sampler2D special0;
uniform float timer;
uniform int underwater;



void main()
{
   
   
	vec3 distortion = texture(special0,Textcoords).rgb;
	
	vec2 dudvTexture = texture(special0,vec2(Textcoords.x + timer/100.0f,Textcoords.y + timer/100.0f) * 3.0).rg * 2.0 - 1.0;
	vec2 dudvTexture2 = texture(special0,vec2(Textcoords.x - timer/100.0f,Textcoords.y + timer/100.0f) *3.0).rg * 2.0 - 1.0;
	
	vec2 totalDistortion = (0.015 * dudvTexture + 0.015* dudvTexture2) * underwater;
	
	 vec3 diffuseColor = texture(diffuse0,Textcoords + totalDistortion).rgb;
	
	gl_FragColor =  vec4(diffuseColor,1.0);


} 

