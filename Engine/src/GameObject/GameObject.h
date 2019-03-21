#pragma once
#include <list>
#include <algorithm>
#include <string>

#include "..\Core\Transform.h"
class Component;
class Shader;

/**
* @class GameObject
* @brief Represents an entity in the engine
*
*
*Contains an entity and can contain children and components
*
* @author Dylan Green
* @version 01
* @date 05/03/2018
*
*
* @bug No known bugs.
*/
class GameObject
{
public:
//---- Public Member Functions ----//
	//-- Constructors --//
	/**
	* @brief		Creates a GameObject object which contains the name, active state, layer, and parent of the GameObject
	*
	* @pre			The GameObject object does not exist
	* @post			The GameObject object is created with the specified parameters
	*
	* @param		name		String representing the name of the GameObject
	* @param		isActive	Whether the GameObject should be included in calculations currently
	* @param		layer		The rendering layer the GameObject is on
	* @param		parent		the GameObject that this GameObject is a child of, nullptr if it has no parent
	*/
	GameObject(std::string name, bool isActive = true, unsigned int layer = 0, GameObject* parent = nullptr);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Deconstructors --//
	/**
	* @brief		Destroys a GameObject object.
	*
	* @pre			At least one GameObject object must exist
	* @post			The GameObject object will no longer exist
	*/
	virtual ~GameObject();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Setters --//
	/**
	* @brief		Sets the name of the GameObject to the specified parameter.
	*
	* @pre			The GameObject must exist
	* @post			The GameObject object's name is set to the parameter value, if it is valid
	*
	* @param		name		Name of the GameObject, must have a length greater than 0
	*/
	void SetName(std::string name);

	/**
	* @brief		Sets the IsActive state of the GameObject to the specified parameter.
	*
	* @pre			The GameObject must exist
	* @post			The GameObject object's IsActive state is set to the parameter value, if it is valid
	*
	* @param		active		State of the GameObject
	* @param		includeChildren		Whether to set all children to the same state
	*/
	void SetActive(bool active, bool includeChildren = false);

	/**
	* @brief		Signal that the objet will be destroyed in the next late update
	*
	* @pre			The GameObject must exist
	* @post			The GameObject is deleted
	*
	*/
	void FlagToBeDestroyed();

	/**
	* @brief		Sets the layer of the GameObject to the specified parameter.
	*
	* @pre			The GameObject must exist
	* @post			The GameObject object's layer is set to the parameter value, if it is valid
	*
	* @param		layer		Layer of the GameObject, must be greater than 0
	* @param		includeChildren		Whether to set all children to the same layer
	*/
	void SetLayer(unsigned int layer, bool includeChildren = false);

	/**
	* @brief		Sets the parent of the GameObject to the specified parameter.
	*
	* @pre			The GameObject must exist
	* @pre			Parent parameter GameObject must exist
	* @post			The GameObject object's parent is set to the parameter value, if it is valid
	*
	* @param		parent		Parent of the GameObject, must be a valid GameObject and must not be this GameObject
	*/
	void SetParent(GameObject *parent);
	

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Accessors --//
	/**
	* @brief		Retrieves the name of the GameObject.
	*
	* @pre			The GameObject must exist.
	* @post			The name of the GameObject will be retrieved.
	*
	* @return		The name of the GameObject.
	*/
	std::string GetName() const;

	/**
	* @brief		Retrieves the IsActive state of the GameObject.
	*
	* @pre			The GameObject must exist.
	* @post			The IsActive state of the GameObject will be retrieved.
	*
	* @return		The IsActive state of the GameObject.
	*/
	bool GetActive() const;

	/**
	* @brief		Retrieves ToBeDestroyed.
	*
	* @pre			The GameObject must exist.
	*
	* @return		The ToBeDestroyed state of the GameObject.
	*/
	bool GetToBeDestroyed() const;

	/**
	* @brief		Retrieves the layer of the GameObject.
	*
	* @pre			The GameObject must exist.
	* @post			The layer of the GameObject will be retrieved.
	*
	* @return		The layer of the GameObject.
	*/
	unsigned int GetLayer() const;

	/**
	* @brief		Retrieves the parent of the GameObject.
	*
	* @pre			The GameObject must exist.
	* @post			The parent of the GameObject will be retrieved, or a nullptr if there is no parent.
	*
	* @return		The parent of the GameObject, or nullptr if it has no parent.
	*/
	GameObject* GetParent() const;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- List Setters/Adders --//
	/**
	* @brief		Adds a child to the GameObject.
	*
	* @pre			The GameObject must exist
	* @pre			The child GameObject must exist
	* @post			If there is no child with the same name, the child GameObject is added to the GameObject
	*
	* @param		child		Child to add to the GameObject
	*/
	void AddChild(GameObject* child);

	/**
	* @brief		Adds a component to the GameObject.
	*
	* @pre			The GameObject must exist
	* @pre			The Component must exist
	* @post			If there is no component with the same name, the Component is added to the GameObject
	*
	* @param		component	Component to add to the GameObject
	*/
	void AddComponent(Component *component);

	/**
	* @brief		Adds a component to a child of the GameObject.
	*
	* @pre			The GameObject must exist
	* @pre			The Component must exist
	* @post			If there is no component in the child with the same name, the component is added to the child GameObject
	*
	* @param		component	Component to add to the child GameObject
	*/
	void AddComponentToChild(Component* component);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- List Removers --//
	/**
	* @brief		Removes a child from the GameObject.
	*
	* @pre			The GameObject must exist
	* @post			If there is a child with the parameter name, the child GameObject is removed from the GameObject
	*
	* @param		childName	Child to be removed from the GameObject
	*/
	void RemoveChild(std::string childName);

	/**
	* @brief		Removes a component from the GameObject.
	*
	* @pre			The GameObject must exist
	* @post			If there is a component with the parameter name, the component is removed from the GameObject
	*
	* @param		componentName	Componenet to be removed from the GameObject
	*/
	void RemoveComponent(std::string componentName);

	/**
	* @brief		Removes a component from the child in the GameObject.
	*
	* @pre			The GameObject must exist
	* @post			If there is a component in the child with the parameter name, the component is removed from the child GameObject
	*
	* @param		childName		Child GameObject to remove the component from
	* @param		componentName	Component to remove from the child GameObject
	*/
	void RemoveComponentInChild(std::string childName, std::string componentName);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- List Accessors --//
	/**
	* @brief		Retrieves a child of the GameObject
	*
	* @pre			The GameObject must exist
	* @post			A child of the GameObject will be retrieved, or a nullptr if there is no child
	*
	* @param		childName		Name of child to search for
	*
	* @return		A child of the GameObject, or nullptr if it has no child with that name
	*/
	GameObject* GetChild(std::string childName) const;

	/**
	* @brief		Retrieves a component in the GameObject
	*
	* @pre			The GameObject must exist
	* @post			A component in the GameObject will be retrieved, or a nullptr if there is no component
	*
	* @param		componentName	Name of component to search for
	*
	* @return		A component in the GameObject, or nullptr if there is no component with that name
	*/
	Component* GetComponent(std::string componentName) const;

	/**
	* @brief		Retrieves a component in a child of the GameObject
	*
	* @pre			The GameObject must exist
	* @post			A component in a child of the GameObject will be retrieved, or nullptr if the component was not found
	*
	* @param		childName		Name of child to search for
	* @param		componentName	Name of component to search for
	*
	* @return		A component in a child of the GameObject, or nullptr if the component/child was not found
	*/
	Component* GetComponentInChild(std::string childName, std::string componentName) const;

	/**
	* @brief		Retrieves the parent of the GameObject
	*
	* @pre			The GameObject must exist
	* @post			The parent of the GameObject will be retrieved
	*
	* @return		The parent of the GameObject, or nullptr if it has no parent
	*/
	std::list<GameObject*>& GetChildList();

	/**
	* @brief		Retrieves the parent of the GameObject
	*
	* @pre			The GameObject must exist
	* @post			The parent of the GameObject will be retrieved
	*
	* @return		The parent of the GameObject, or nullptr if it has no parent
	*/
	std::list<Component*>& GetComponentList();
	
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- List Contains Accessors --//
	/**
	* @brief		Returns whether the GameObject has a child with the parameter name
	*
	* @pre			The GameObject must exist.
	* @post			Whether the child exists will be retreived
	*
	* @param		childName		Name of child to search for
	*
	* @return		True if the child is in the GameObject, else false
	*/
	bool HasChild(std::string childName) const;

	/**
	* @brief		Returns whether the GameObject has a component with the parameter name
	*
	* @pre			The GameObject must exist.
	* @post			Whether the component exists will be retreived
	*
	* @param		componentName	Name of component to search for
	*
	* @return		True if the component is in the GameObject, else false
	*/
	bool HasComponent(std::string componentName) const;

	/**
	* @brief		Returns whether the GameObject has a component in a child with the parameter name
	*
	* @pre			The GameObject must exist.
	* @post			Whether the component exists in the child will be retreived
	*
	* @param		childName		Name of child to search for
	* @param		componentName	Name of component to search for
	*
	* @return		True if the component is in the child GameObject, else false
	*/
	bool ChildHasComponent(std::string childName, std::string componentName) const;

	/**
	* @brief		Update the gameobject, its children and components.
	*
	* @pre			The GameObject must exist.
	* @post			
	*
	* @return		none
	*/
	virtual void Update();


	virtual void OnPreRender(Shader* currentShader = nullptr);

	void DestroyChildrenAndComponents();


	Transform transform;

protected:
	std::string _name;
	bool _isActive;
	bool _toBeDestroyed;
	unsigned int _layer;
	GameObject* _parent;
	std::list<GameObject*> _children;
	std::list<Component*> _components; //Possibly Map
};

