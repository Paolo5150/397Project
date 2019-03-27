#pragma once
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Core\Logger.h"
#include "..\Utils\Asset.h"


class Texture2D : public Asset
{
public:
	unsigned GetID() { return id; }
	virtual void Bind() = 0;
	virtual ~Texture2D(){};

protected:
	Texture2D(){}
	Texture2D(std::string textureName, int width, int height, int channels,unsigned char* data){};
	Texture2D(unsigned width, unsigned height, bool isDepth = false){};

		unsigned id;
		int width;
		int height;
		int channels;
		unsigned char* data;

	};
