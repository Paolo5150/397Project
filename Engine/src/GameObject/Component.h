#pragma once
#include <string>

#include "GameObject.h"
#include "..\Graphics\Shader.h"

/**
* @class Component
* @brief Represents a component that can be attached to a GameObject to provide functionality
*
*
* Superclass for all component types
*
* @author Dylan Green
* @version 01
* @date 06/03/2019
*
*
* @bug No known bugs.
*/
class Component : public InternalAsset
{
public:
//---- Public Member Functions ----//
	//-- Constructors --//
	/**
	* @brief		Creates a Component object which contains the name and parent of the Component
	*
	* @pre			The Component object does not exist
	* @post			The Component object is created with the specified parameters
	*
	* @param		name		String representing the name of the Component
	* @param		parent		the GameObject that this Component is a child of, nullptr if it has no parent
	*/
	Component(std::string name, GameObject* parent = nullptr);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Deconstructors --//
	/**
	* @brief		Destroys a Component object.
	*
	* @pre			At least one Component object must exist
	* @post			The Component object will no longer exist
	*/
	virtual ~Component();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Setters --//
	/**
	* @brief		Sets the IsActive state of the Component to the specified parameter.
	*
	* @pre			The Component must exist
	* @post			The Component object's IsActive state is set to the parameter value, if it is valid
	*
	* @param		active		State of the Component
	*/
	void SetActive(bool active);

	/**
	* @brief		Sets the name of the Component to the specified parameter.
	*
	* @pre			The Component must exist
	* @post			The Component object's name is set to the parameter value, if it is valid
	*
	* @param		name		Name of the Component, must have a length greater than 0
	*/
	void SetName(std::string name);

	/**
	* @brief		Sets the parent of the Component to the specified parameter.
	*
	* @pre			The Component must exist
	* @pre			Parent parameter GameObject must exist
	* @post			The Component object's parent is set to the parameter value, if it is valid
	*
	* @param		parent		Parent of the Component, must be a valid GameObject
	*/
	void SetParent(GameObject* parent);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Accessors --//
	/**
	* @brief		Retrieves the IsActive state of the Component.
	*
	* @pre			The Component must exist.
	* @post			The IsActive state of the Component will be retrieved.
	*
	* @return		The IsActive state of the Component.
	*/
	bool GetActive() const;

	/**
	* @brief		Retrieves the name of the Component.
	*
	* @pre			The Component must exist.
	* @post			The name of the Component will be retrieved.
	*
	* @return		The name of the Component.
	*/
	std::string GetName() const;

	/**
	* @brief		Retrieves the type of the Component.
	*
	* @pre			The Component must exist.
	* @post			The type of the Component will be retrieved.
	*
	* @return		The type of the Component.
	*/
	std::string GetType() const;

	/**
	* @brief		Retrieves the parent of the Component.
	*
	* @pre			The Component must exist.
	* @post			The parent of the Component will be retrieved, or a nullptr if there is no parent.
	*
	* @return		The parent of the Component, or nullptr if it has no parent.
	*/
	GameObject* GetParent() const;

	virtual void Update(){};
	virtual void EngineUpdate(){};
	virtual void OnAttach(){};


protected:
	std::string _name;
	std::string _type;
	bool _isActive;
	GameObject* _parent;
};

