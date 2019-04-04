#pragma once
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Core\Logger.h"
#include "CubeMap.h"
#include <vector>


class CubeMapGL : public CubeMap
{

public:

	CubeMapGL(std::string name, unsigned char* data[6], int width[6], int height[6]);
	~CubeMapGL();
	virtual void Bind() override;




};

