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

void GameObject::SetActive(bool active)
{
	_isActive = active;
}

void GameObject::SetLayer(unsigned int layer)
{
	_layer = layer;
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

void GameObject::AddComponent(Component *component)
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
		_components.remove_if([&](Component* component) {return component->GetName() == componentName; });
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

std::list<GameObject*> GameObject::GetChildList() const
{
	return _children;
}

std::list<Component*> GameObject::GetComponentList() const
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