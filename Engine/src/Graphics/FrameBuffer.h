#pragma once
#include "Texture2D.h"

class FrameBuffer 
{
public:
	FrameBuffer(int w, int h, bool hasColorAttachment = true);
	virtual ~FrameBuffer();
	virtual void Bind();
	virtual void Unbind();

	Texture2D* GetColorTexture(){ return colortexture; };
	Texture2D* GetDepthTexture(){ return depthTexture; };
	void ResizeTexture(int w, int h);

protected:

	int width;
	int height;
	bool hasColorAttachment;
	Texture2D* colortexture;
	Texture2D* depthTexture;
	unsigned bufferID;
};
