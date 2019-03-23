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
	std::string GetType() const;

	GameObject* GetParent() const;

	virtual void Update(){};
	virtual void OnAttach(){};
	virtual void OnPreRender(Camera& cam,Shader* currentShader = nullptr){};



protected:
	std::string _name;
	std::string _type;
	bool _isActive;
	GameObject* _parent;
};

