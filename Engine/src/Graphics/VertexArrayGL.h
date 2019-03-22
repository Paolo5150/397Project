#pragma once
#include "..\pch.h"
#include "VertexArray.h"

class VertexArrayGL : public VertexArray
{
public:
	VertexArrayGL(){
		glGenVertexArrays(1, &m_id);
	};
	~VertexArrayGL()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void Bind()
	{
		glBindVertexArray(m_id);

	}
	void Unbind()
	{
		glBindVertexArray(0);
	}

	void AddLayoutf(unsigned id, unsigned numOfElements, bool normalized, unsigned size, void* data)
	{
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id, numOfElements, GL_FLOAT, normalized, size, data);
	}

	void RenderArrayTriangles(unsigned size)
	{
		glBindVertexArray(m_id);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	}

protected:
	unsigned m_id;

};