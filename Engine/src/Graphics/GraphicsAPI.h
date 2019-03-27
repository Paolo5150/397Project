#pragma once
#include <iostream>

#include "..\Core\Logger.h"
#include "ArrayBuffer.h"
#include "VertexArray.h"
#include "Vertex.h"
#include "UniformBuffer.h"

class Shader;
class Texture2D;

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
	virtual Texture2D* CreateTexture2D(std::string textureName, int width, int height, int channels, unsigned char* data) = 0;
	virtual Texture2D* CreateTexture2D(std::string name, unsigned width, unsigned height, bool isDepth = false) = 0;
	virtual void ResetTextures()=0;

	virtual ArrayBuffer<Vertex>* CreateVertexBuffer() = 0;
	virtual ArrayBuffer<unsigned>* CreateIndexBuffer() = 0;
	virtual VertexArray* CreateVertexArray() = 0;

	virtual UniformBuffer* CreateUniformBuffer(unsigned totalSize, unsigned binding) = 0;




protected:
	API_NAME apiName;
};