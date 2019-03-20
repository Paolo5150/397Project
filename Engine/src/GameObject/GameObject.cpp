#include "../pch.h"
#include "GameObject.h"
#include "Component.h"


GameObject::GameObject(std::string name, bool isActive, unsigned int layer, GameObject* parent)
{
	SetName(name);
	SetActive(isActive);
	SetLayer(layer);
	SetParent(parent);
}

GameObject::~GameObject()
{
	for (auto it = std::begin(_children); it != std::end(_children); it++)
	{
		delete (*it);
	}

	_children.clear();

	for (auto it = std::begin(_components); it != std::end(_components); it++)
	{
		delete (*it);
	}

	_components.clear();
}

void GameObject::SetName(std::string name)
{
	if (name.length() > 0)
	{
		_name = name;
	}
}

void GameObject::SetActive(bool active, bool includeChildren)
{
	_isActive = active;

	for (auto it = std::begin(_components); it != std::end(_components); it++)
	{
		(*it)->SetActive(active);
	}

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetActive(active);
		}
	}
}

void GameObject::SetLayer(unsigned int layer, bool includeChildren)
{
	_layer = layer;

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetLayer(layer);
		}
	}
}

void GameObject::SetParent(GameObject *parent)
{
	if (parent != this)
	{
		_parent = parent;
	}
}

std::string GameObject::GetName() const
{
	return _name;
}

bool GameObject::GetActive() const
{
	return _isActive;
}


unsigned int GameObject::GetLayer() const
{
	return _layer;
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

void GameObject::AddComponent(Component* component)
{
	if (HasComponent(component->GetName()) == false)
	{
		_components.push_back(component);
	}
}

void GameObject::AddComponentToChild(Component* component)
{

}

void GameObject::RemoveChild(std::string childName)
{
	if (HasChild(childName) == true)
	{
		GetChild(childName)->SetParent(nullptr);
		_children.remove_if([&](GameObject* gameObject) {return gameObject->GetName() == childName; });
	}
}

void GameObject::RemoveComponent(std::string componentName)
{
	if (HasComponent(componentName) == true)
	{
		auto it = std::remove_if(std::begin(_components), std::end(_components), [&](Component* component) {return component->GetName() == componentName; });
		_components.erase(it, std::end(_components));
	}
}

void GameObject::RemoveComponentInChild(std::string childName, std::string componentName)
{
	if (HasChild(childName) == true)
	{
		GetChild(childName)->RemoveComponent(componentName);
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

Component* GameObject::GetComponent(std::string componentName) const
{
	std::list<Component*>::const_iterator it;
	it = std::find_if(std::begin(_components), std::end(_components), [&](Component* const component) -> Component* {if (component->GetName() == componentName){ return component; } else { return nullptr; }});

	if (it != std::end(_components))
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}

Component* GameObject::GetComponentInChild(std::string childName, std::string componentName) const
{
	if (HasChild(childName) == true)
	{
		return GetChild(childName)->GetComponent(componentName);
	}
	else
	{
		return nullptr;
	}
}

std::list<GameObject*>& GameObject::GetChildList()
{
	return _children;
}

std::list<Component*>& GameObject::GetComponentList()
{
	return _components;
}

bool GameObject::HasChild(std::string childName) const
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

bool GameObject::HasComponent(std::string componentName) const
{
	std::list<Component*>::const_iterator it;
	it = std::find_if(std::begin(_components), std::end(_components), [&](Component* const component) {return component->GetName() == componentName; });

	if (it != std::end(_components))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameObject::ChildHasComponent(std::string childName, std::string componentName) const
{
	return false; //Temp
}

void GameObject::Update()
{
	auto it = _children.begin();
	for (; it != _children.end(); it++)
		(*it)->Update();

	auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		(*itc)->Update();
}