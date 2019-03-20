#include "../pch.h"
#include "Component.h"


Component::Component(std::string name, GameObject* parent)
{
	SetName(name);
	SetParent(parent);
}

Component::~Component()
{
}

void Component::SetActive(bool active)
{
	_isActive = active;
}

void Component::SetName(std::string name)
{
	if (name.length() > 0)
	{
		_name = name;
	}
}

void Component::SetParent(GameObject* parent)
{
	_parent = parent;
}

bool Component::GetActive() const
{
	return _isActive;
}

std::string Component::GetName() const
{
	return _name;
}

GameObject* Component::GetParent() const
{
	return _parent;
}