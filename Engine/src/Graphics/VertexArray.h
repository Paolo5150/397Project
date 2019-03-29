#pragma once

class VertexArray
{
public:
	VertexArray(){};
	virtual ~VertexArray(){};

	virtual void Bind() = 0;
	virtual void Unbind() = 0;


	virtual void AddLayoutf(unsigned id, unsigned numOfElements, bool normalized, unsigned size, void* data) = 0;
	virtual void RenderArrayTriangles(unsigned size) = 0;
	virtual void RenderArrayLines(unsigned size) = 0;


protected:
	unsigned m_id;

};