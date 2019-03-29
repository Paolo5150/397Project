#include "FrameBufferGL.h"
#include "..\Core\Core.h"

FrameBufferGL::FrameBufferGL(int w, int h, bool hasColorAttachment) : FrameBuffer(w,h,hasColorAttachment)
{
	width = w;
	height = h;
	this->hasColorAttachment = hasColorAttachment;
	glGenFramebuffers(1, &bufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);

	if (hasColorAttachment)
	{
		colortexture = Core::Instance().GetGraphicsAPI().CreateTexture2D("",w, h);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colortexture->GetID(), 0);
	}
	else
	{
		colortexture = NULL;
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	depthTexture = Core::Instance().GetGraphicsAPI().CreateTexture2D("", w, h,true);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->GetID(), 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Logger::LogError("Error while creating the FRAME BUFFER");
	}
	Unbind();




}

void FrameBufferGL::ResizeTexture(int w, int h)
{
	
	this->width = w;
	this->height = h;

	if (colortexture != NULL)
	{

		colortexture->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	}

	if (depthTexture != NULL)
	{

		depthTexture->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBufferGL::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
}
void FrameBufferGL::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int w, h;
	Window::Instance().GetWindowSize(w, h);
	glViewport(0, 0, w,h);
}

FrameBufferGL::~FrameBufferGL()
{
	if (colortexture != NULL)
		delete colortexture;

	if (depthTexture != NULL)
		delete depthTexture;

	glDeleteFramebuffers(1, &bufferID);
}