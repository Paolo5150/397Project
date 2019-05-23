#include "Saveable.h"

Saveable::Saveable()
{
	_saveableObjects.push_back(this);
}

Saveable::~Saveable()
{
	_saveableObjects.remove_if([&](Saveable* object) {return object == this; });
}

std::list<Saveable*>& Saveable::GetSaveableObects()
{
	return _saveableObjects;
}

std::list<Saveable*> Saveable::_saveableObjects;