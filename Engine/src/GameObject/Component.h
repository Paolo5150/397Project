#pragma once
#include <string>

#include "GameObject.h"
#include "..\Graphics\Shader.h"

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

	virtual void Update(){};
	virtual void OnAttach(){};
	virtual void OnPreRender(Shader* currentShader = nullptr){};


protected:
	std::string _name;
	bool _isActive;
	GameObject* _parent;
};

