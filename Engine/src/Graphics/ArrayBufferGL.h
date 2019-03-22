#pragma once
#include <string>
#include "ArrayBuffer.h"
#include "..\Core\Logger.h"
template <class T>
class ArrayBufferGL : public ArrayBuffer<T>
{
public:


	ArrayBufferGL();
	~ArrayBufferGL();
	void Bind() override;

	void AddData(std::vector<T>& data) override;

private:
	unsigned bufferType;

};

template <class T>
ArrayBufferGL<T>::ArrayBufferGL()
{
	glGenBuffers(1, &m_id);
	//Ugly, but necessary
	std::string typeName = typeid(T).name();

	if (typeName == "unsigned int")
	{
		bufferType = GL_ELEMENT_ARRAY_BUFFER;
	}
	else
		bufferType = GL_ARRAY_BUFFER;
}

template <class T>
ArrayBufferGL<T>::~ArrayBufferGL()
{
	glDeleteBuffers(1, &m_id);
}

template <class T>
void ArrayBufferGL<T>::Bind()
{	
	glBindBuffer(bufferType, m_id);
}



template <class T>
void ArrayBufferGL<T>::AddData(std::vector<T>& data)
{
	Bind();
	glBufferData(bufferType, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
}