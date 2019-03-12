#include "API_Opengl.h"
#include "Texture2DGL.h"

API_Opengl::API_Opengl()
{
	apiName = OPENGL;
}
API_Opengl::~API_Opengl()
{
}

void API_Opengl::Initialize()
{
	glewExperimental = true;
	//Initialize glew
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("GLEW failed to initialize");
	}

	//OpengGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glClearColor(0, 0, 0, 1);
}

void API_Opengl::ClearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void API_Opengl::ClearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void API_Opengl::SetViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

Shader* API_Opengl::CreateShader(std::string name, std::string vertexSource, std::string fragmentSource)
{
	return new ShaderGL(name,vertexSource, fragmentSource);
}

Texture2D* API_Opengl::CreateTexture2D(std::string textureName, int width, int height, int channels, unsigned char* data)
{
	return new Texture2DGL(textureName, width, height, channels, data);
}
Texture2D* API_Opengl::CreateTexture2D(std::string name, unsigned width, unsigned height, bool isDepth )
{
	return new Texture2DGL(name, width, height, isDepth);
}

void API_Opengl::Shutdown()
{

}