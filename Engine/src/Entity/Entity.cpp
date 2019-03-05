#include "../pch.h"
#include "Entity.h"


Entity::Entity(std::string name, unsigned int layer, Entity* parent)
{
	_name = name;
	_layer = layer;
	_parent = parent;
}

Entity::~Entity()
{
}

void Entity::SetName(std::string name)
{
	if (name.length() > 0)
	{
		_name = name;
	}
}

std::string Entity::GetName() const
{
	return _name;
}

void Entity::SetActive(bool active)
{
	_isActive = active;
}

bool Entity::GetActive() const
{
	return _isActive;
}

void Entity::SetLayer(unsigned int layer)
{
	_layer = layer;
}

unsigned int Entity::GetLayer() const
{
	return _layer;
}

void Entity::SetParent(Entity *parent)
{
	_parent = parent;
}

Entity* Entity::GetParent() const
{
	return _parent;
}

void Entity::AddChild(Entity* child)
{
	//stub
}

Entity* Entity::GetChild(std::string childName) const
{
	//stub
}

void Entity::AddComponent(Component *component)
{
	//stub
}

Component* Entity::GetComponent(std::string componentName) const
{
	//stub
}

bool Entity::HasComponent(std::string componentName)
{
	return(std::find(_components.begin(), _components.end(), componentName) != _components.end());
}

std::list<Component*> Entity::GetComponentList() const
{
	return _components;
}