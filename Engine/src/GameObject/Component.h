#pragma once
#include <string>

#include "GameObject.h"
#include "..\Graphics\Shader.h"

class Component : public InternalAsset
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

	/**
	* @brief		Update called during Logic Update
	*
	* @pre			The Component exists and is attached to a GameObject
	* @post			The Component is updated
	*/
	virtual void Update(){};

	/**
	* @brief		Update called during Engine Update
	*
	* @pre			The Component exists and is attached to a GameObject
	* @post			The Component is updated
	*/
	virtual void EngineUpdate(){};

	/**
	* @brief		Callback invoked when the component is attached to a GameObject
	*
	* @pre			The Component exists 
	* @post			The Component is attached to a GameObject
	*/
	virtual void OnAttach(){};


protected:
	/**
	* @brief The component name
	*/
	std::string _name;

	/**
	* @brief The component type
	*/
	std::string _type;

	/**
	* @brief Whether the component is active
	*/
	bool _isActive;

	/**
	* @brief The GameObject this component is attached to
	*/
	GameObject* _parent;
};

