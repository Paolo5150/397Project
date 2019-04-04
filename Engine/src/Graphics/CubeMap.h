#pragma once
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Core\Logger.h"
#include "..\Utils\Asset.h"
#include <vector>


class CubeMap : public Asset
{

public:

	CubeMap(std::string name, unsigned char* data[6], int width[6], int height[6]){};
	virtual ~CubeMap(){};
	virtual void Bind() = 0;

protected:
	unsigned cubemapID;



};

