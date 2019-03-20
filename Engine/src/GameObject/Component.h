#pragma once
#include <string>

#include "GameObject.h"

class Component
{
public:
//---- Public Member Functions ----//
	//-- Constructors --//
	Component(std::string name, GameObject* parent = nullptr);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Deconstructors --//
	virtual ~Component();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Setters --//
	void SetActive(bool active);
	void SetName(std::string name);
	void SetParent(GameObject* parent);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Accessors --//
	bool GetActive() const;
	std::string GetName() const;
	GameObject* GetParent() const;


private:
	std::string _name;
	bool _isActive;
	GameObject* _parent;
};

