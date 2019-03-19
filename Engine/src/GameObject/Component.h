#pragma once
#include <string>

#include "GameObject.h"

class Component
{
public:
	Component(GameObject* parent = nullptr);
	~Component();

	void SetParent(GameObject* parent);
	GameObject* GetParent() const;

	void SetName(std::string name);
	std::string GetName() const;

private:
	std::string _name; //Temp
	GameObject *_parent;
};

