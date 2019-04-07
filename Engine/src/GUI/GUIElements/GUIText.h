#pragma once
#include  "GUIObject.h"

class GUIText : public GUIObject
{
public:
	GUIText(std::string message, float posX = 0, float posY = 0) : _message(message){
		_color = glm::vec4(1, 1, 1, 1);
		position = glm::vec2(posX, posY);
	};
	~GUIText(){};
	
	std::string _message;
	glm::vec4 _color;
};