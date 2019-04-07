#pragma once
#include  "GUIObject.h"

class GUIText : public GUIObject
{
public:
	GUIText(std::string message, float posX = 0, float posY = 0, float r = 1, float g = 1, float b = 1) : _message(message){
		_color = glm::vec4(r, g, b, 1);
		position = glm::vec2(posX, posY);
	};
	~GUIText(){};
	
	std::string _message;
	glm::vec4 _color;
};