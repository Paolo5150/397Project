#include "API_Opengl.h"
#include "Texture2DGL.h"
#include "VertexArrayGL.h"
#include "ArrayBufferGL.h"
#include "UniformBufferGL.h"
#include "FrameBufferGL.h"

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
	glClearColor(0.3f, 0.3f, 0.3f, 1);
	
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

void API_Opengl::ResetTextures()
{
	//Reset active textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

ArrayBuffer<Vertex>* API_Opengl::CreateVertexBuffer()
{
	return new ArrayBufferGL<Vertex>();
}
ArrayBuffer<unsigned>* API_Opengl::CreateIndexBuffer()
{
	return new ArrayBufferGL<unsigned>();
}

VertexArray* API_Opengl::CreateVertexArray()
{
	return new VertexArrayGL();
}

UniformBuffer* API_Opengl::CreateUniformBuffer(unsigned totalSize, unsigned binding)
{
	return new UniformBufferGL(totalSize, binding);
}

FrameBuffer* API_Opengl::CreateFrameBuffer(int w, int h, bool hasColorAttachment)
{
	return new FrameBufferGL(w, h, hasColorAttachment);
}

void  API_Opengl::SetClipPlaneActive(bool ac)
{
	if (ac)
		glEnable(GL_CLIP_DISTANCE0);
	else
		glDisable(GL_CLIP_DISTANCE0);
}


