#pragma once
#include  "GUIObject.h"
#include "..\..\Graphics\Texture2D.h"

class GUIImage : public GUIObject
{
public:
	GUIImage(Texture2D* t, float posX = 0, float posY = 0, float sizeX = 10, float sizeY = 10) {
		position = glm::vec2(posX, posY);
		size.x = sizeX;
		size.y = sizeY;
		_textID = t->GetID();
	};
	~GUIImage(){};

	ImTextureID GetTextureID(){ return (ImTextureID)_textID; }
private:
	unsigned _textID;
};