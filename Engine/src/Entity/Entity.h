#pragma once
#include <list>
#include <string>
#include "Component.h"

//Initial version, not for use in program yet
class Entity
{
public:
	Entity(std::string name, unsigned int layer = 0, Entity* parent = nullptr);
	~Entity();

	void SetName(std::string name);
	std::string GetName() const;

	void SetActive(bool active);
	bool GetActive() const;

	void SetLayer(unsigned int layer);
	unsigned int GetLayer() const;

	void SetParent(Entity *parent);
	Entity* GetParent() const;

	void AddChild(Entity* child);
	Entity* GetChild(std::string childName) const;

	void AddComponent(Component *component);
	Component* GetComponent(std::string componentName) const;
	bool HasComponent(std::string componentName);
	std::list<Component*> GetComponentList() const;

private:
	std::string _name;
	bool _isActive;
	unsigned int _layer;
	Entity* _parent;
	std::list<Entity*> _children;
	std::list<Component*> _components;
};

