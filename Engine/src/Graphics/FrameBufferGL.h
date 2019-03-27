#pragma once
#include "FrameBuffer.h"
#include "..\Core\Window.h"
class FrameBufferGL : FrameBuffer
{
public:
	FrameBufferGL(int w, int h, bool hasColorAttachment = true);
	~FrameBufferGL();
	void Bind();
	void Unbind();




};
