#pragma once
#include <vector>

template <class T>
class ArrayBuffer
{
public:
	ArrayBuffer(){};
	virtual ~ArrayBuffer(){};
	virtual void Bind() = 0;

	virtual void AddData(std::vector<T>& data) = 0;

protected:
	unsigned m_id;


};