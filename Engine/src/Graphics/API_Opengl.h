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

};