#pragma once
#include "UniformBuffer.h"

class UniformBufferGL : public UniformBuffer
{
public:
	UniformBufferGL(unsigned totalSize, unsigned binding) ;
	~UniformBufferGL();

	void AddDataRange(unsigned stride, unsigned dataSize, const void* datao) override;
	void Bind();
	void Unbind();



};