#pragma once
#include "FrameBuffer.h"
#include "..\Core\Window.h"
class FrameBufferGL : public FrameBuffer
{
public:
	FrameBufferGL(int w, int h, bool hasColorAttachment = true);
	~FrameBufferGL();
	void Bind();
	void Unbind();
	void ResizeTexture(int w, int h) override;




};
