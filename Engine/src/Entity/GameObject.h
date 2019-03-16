#pragma once
#include <list>
#include <algorithm>
#include <string>
#include "Component.h"

//DEBUG
#include <iostream>
//DEBUG

//Initial version, not for use in program yet
class GameObject
{
public:
	GameObject(std::string name, bool isActive = true, unsigned int layer = 0, GameObject* parent = nullptr);
	~GameObject();

	void SetName(std::string name);
	std::string GetName() const;

	void SetActive(bool active);
	bool GetActive() const;

	void SetLayer(unsigned int layer);
	unsigned int GetLayer() const;

	void SetParent(GameObject *parent);
	GameObject* GetParent() const;

	void AddChild(GameObject* child);
	GameObject* GetChild(std::string childName) const;
	bool HasChild(std::string childName);
	std::list<GameObject*> GetChildList() const;

	void AddComponent(Component *component);
	Component* GetComponent(std::string componentName) const;
	bool HasComponent(std::string componentName);
	std::list<Component*> GetComponentList() const;

private:
	std::string _name;
	bool _isActive;
	unsigned int _layer;
	GameObject* _parent;
	std::list<GameObject*> _children;
	std::list<Component*> _components;
};

