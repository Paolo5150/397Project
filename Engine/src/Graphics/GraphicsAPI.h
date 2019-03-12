#pragma once
#include <iostream>

#include "..\Core\Logger.h"

class Shader;

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
	API_NAME GetApiName(){ return apiName; }


	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void ClearColorBuffer() = 0;
	virtual void ClearDepthBuffer() = 0;
	virtual void SetViewPort(int w, int h) = 0;
	virtual Shader* CreateShader(std::string name, std::string vertexSource, std::string fragmentSource) = 0;

protected:
	API_NAME apiName;
};