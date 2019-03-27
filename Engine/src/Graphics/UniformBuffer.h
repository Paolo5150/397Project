#pragma once

class UniformBuffer
{
public:
	UniformBuffer(unsigned totalSize, unsigned binding){};
	virtual ~UniformBuffer(){};

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void AddDataRange(unsigned stride, unsigned dataSize, const void* data) = 0;


protected:
	unsigned m_id;
	unsigned m_bindingId;
};