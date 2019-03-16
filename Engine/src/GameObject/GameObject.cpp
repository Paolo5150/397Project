#include "../pch.h"
#include "GameObject.h"


GameObject::GameObject(std::string name, bool isActive, unsigned int layer, GameObject* parent)
{
	SetName(name);
	SetActive(isActive);
	SetLayer(layer);
	SetParent(parent);
}

GameObject::~GameObject()
{
}

void GameObject::SetName(std::string name)
{
	if (name.length() > 0)
	{
		_name = name;
	}
}

std::string GameObject::GetName() const
{
	return _name;
}

void GameObject::SetActive(bool active)
{
	_isActive = active;
}

bool GameObject::GetActive() const
{
	return _isActive;
}

void GameObject::SetLayer(unsigned int layer)
{
	_layer = layer;
}

unsigned int GameObject::GetLayer() const
{
	return _layer;
}

void GameObject::SetParent(GameObject *parent)
{
	_parent = parent;
}

GameObject* GameObject::GetParent() const
{
	return _parent;
}

void GameObject::AddChild(GameObject* child)
{
	if (HasChild(child->GetName()) == false)
	{
		child->SetParent(this);
		_children.push_back(child);
	}
}

void GameObject::RemoveChild(std::string childName)
{
	if (HasChild(childName) == true)
	{
		GetChild(childName)->SetParent(nullptr);
		_children.remove_if([&](GameObject* gameObject) {return gameObject->GetName() == childName; });
	}
}

GameObject* GameObject::GetChild(std::string childName) const
{
	std::list<GameObject*>::const_iterator it;
	it = std::find_if(std::begin(_children), std::end(_children), [&](GameObject* gameObject) -> GameObject* {if (gameObject->GetName() == childName){ return gameObject; } else { return nullptr; }});

	if (it != std::end(_children))
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}

bool GameObject::HasChild(std::string childName)
{
	std::list<GameObject*>::const_iterator it;
	it = std::find_if(std::begin(_children), std::end(_children), [&](GameObject* child) {return child->GetName() == childName; });

	if (it != std::end(_children))
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::list<GameObject*> GameObject::GetChildList() const
{
	return _children;
}

void GameObject::AddComponent(Component *component)
{
	if (HasComponent(component->GetName()) == false)
	{
		_components.push_back(component);
	}
}

void GameObject::RemoveComponent(std::string componentName)
{
	if (HasComponent(componentName) == true)
	{
		_components.remove_if([&](Component* component) {return component->GetName() == componentName; });
	}
}

Component* GameObject::GetComponent(std::string componentName) const
{
	std::list<Component*>::const_iterator it;
	it = std::find_if(std::begin(_components), std::end(_components), [&](Component* component) -> Component* {if (component->GetName() == componentName){ return component; } else { return nullptr; }});

	if (it != std::end(_components))
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}

bool GameObject::HasComponent(std::string componentName)
{
	std::list<Component*>::const_iterator it;
	it = std::find_if(std::begin(_components), std::end(_components), [&](Component* component) {return component->GetName() == componentName; });

	if (it != std::end(_components))
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::list<Component*> GameObject::GetComponentList() const
{
	return _components;
}