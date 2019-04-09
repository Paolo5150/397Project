#pragma once
#include  "GUIObject.h"

class GUIText : public GUIObject
{
public:
	GUIText(std::string message, float posX = 0, float posY = 0, float r = 1, float g = 1, float b = 1, bool isPercentage = false) : _message(message){
		_color = glm::vec4(r, g, b, 1);
		int winX, winY;
		Window::Instance().GetWindowSize(winX, winY);
		if (!isPercentage)
		{
			winX = winY = 100;
		}

		position = glm::vec2(posX * winX / 100, posY * winY / 100);
	
	};
	~GUIText(){};
	
	std::string _message;
	glm::vec4 _color;
};