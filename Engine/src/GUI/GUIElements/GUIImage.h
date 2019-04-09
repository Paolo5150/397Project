#pragma once
#include  "GUIObject.h"
#include "..\..\Graphics\Texture2D.h"
#include "..\..\Core\Window.h"

class GUIImage : public GUIObject
{
public:
	GUIImage(Texture2D* t, float posX = 0, float posY = 0, float sizeX = 10, float sizeY = 10, bool isPercentage = false) {
		int winX, winY;
		Window::Instance().GetWindowSize(winX, winY);
		if (!isPercentage)
		{
			winX = winY = 100;
		}

		position = glm::vec2(posX * winX / 100, posY * winY / 100);
		size.x = sizeX * winX / 100;
		size.y = sizeY * winY / 100;
		_textID = t->GetID();
	};
	~GUIImage(){};

	ImTextureID GetTextureID(){ return (ImTextureID)_textID; }
private:
	unsigned _textID;
};