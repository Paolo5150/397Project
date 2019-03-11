#pragma once
#include <iostream>
#include "..\Core\Logger.h"


class GraphicsAPI
{
public:
	
	enum API_NAME
	{
		OPENGL,
		DIRECTX
	};

	GraphicsAPI(){};
	~GraphicsAPI(){};

	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void ClearColorBuffer() = 0;
	virtual void ClearDepthBuffer() = 0;
	virtual void SetViewPort(int w, int h) = 0;
	API_NAME GetApiName(){ return apiName; }


protected:
	API_NAME apiName;
};