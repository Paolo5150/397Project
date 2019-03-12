#pragma once
#include "GraphicsAPI.h"
#include <GL/glew.h>
#include "ShaderGL.h"

class API_Opengl : public GraphicsAPI
{
public:
	API_Opengl();
	~API_Opengl();

	void Initialize()override;
	void Shutdown()override;
	void ClearColorBuffer() override;
	void ClearDepthBuffer() override;
	void SetViewPort(int w, int h) override;
	Shader* CreateShader(std::string name, std::string vertexSource, std::string fragmentSource) override;
	Texture2D* CreateTexture2D(std::string textureName, int width, int height, int channels, unsigned char* data) override;
	Texture2D* CreateTexture2D(std::string name, unsigned width, unsigned height, bool isDepth = false) override;

};