#include "../pch.h"
#include "Component.h"


Component::Component(std::string name)
{
	SetName(name);
}

Component::~Component()
{
}

void Component::SetName(std::string name)
{
	if (name.length() > 0)
	{
		_name = name;
	}
}

std::string Component::GetName() const
{
	return _name;
}