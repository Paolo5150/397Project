#pragma once
#include "..\Core\Transform.h"
#include "..\Graphics\Layers.h"
#include <list>
#include <algorithm>
#include <string>
#include "..\Graphics\Material.h"
#include "..\Utils\Asset.h"

class Component;
class Shader;
class Camera;



/**
* @class GameObject
* @brief Represents an entity in the engine
*
*
* Contains an entity and can contain children and components
*
* @author Dylan Green
* @version 01
* @date 05/03/2019
*
*
* @bug No known bugs.
*/
class GameObject : public InternalAsset
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
	GameObject(std::string name, bool isActive = true, unsigned int layer = Layers::DEFAULT, GameObject* parent = nullptr);

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
	* @param		active				State of the GameObject
	* @param		includeChildren		Whether to set all children to the same state
	*/
	void SetActive(bool active, bool includeChildren = true);

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
	* @param		layer				Layer of the GameObject, must be greater than 0
	* @param		includeChildren		Whether to set all children to the same layer
	*/
	void SetLayer(unsigned int layer, bool includeChildren = true);

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
	template <class T>
	T* GetComponent(std::string componentName) const;

	/**
	* @brief		Retrieves a component in the GameObject by the type
	*
	* @pre			The GameObject must exist
	* @post			A component in the GameObject will be retrieved, or a nullptr if there is no component
	*
	* @param		componentType	Type of component to search for
	*
	* @return		A component in the GameObject, or nullptr if there is no component with that name
	*/
	Component* GetComponentByType(std::string componentType) const;

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
	template <class T>
	T* GetComponentInChild(std::string childName, std::string componentName) const;

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


	/**
	* @brief		Update the gameobject in the Engine Update loop
	*
	* @pre			The GameObject must exist.
	* @post
	*
	* @return		none
	*/
	virtual void EngineUpdate();


	/**
	* @brief		Print the game object hierarchy (children) to the console
	*
	* @pre			The GameObject must exist.
	* @post			The hierarchybis printed to the console
	*
	* @return		none
	*/

	void PrintHierarchy();

	/**
	* @brief		Get the GameObject on top of the hierarchy
	*
	* @pre			The GameObject must exist.
	* @post			The top GameObject is returned
	*
	* @return		The top GameObject
	*/
	GameObject* GetRoot();

	/**
	* @brief		Apply a material to the gameobject and its children
	*
	* @pre			The GameObject must exist.
	* @post			The material is applied to the gameobject and its children
	* @param mat	The material to be applied
	* @param mt		The material type
	*/
	void ApplyMaterial(Material mat, MaterialType mt = DEFAULT);

	/**
	* @brief		Apply a color to the gameobject and its children
	*
	* @pre			The GameObject must exist.
	* @post			The color is applied to the gameobject and its children
	* @param r		The red chnnel of the color
	* @param g		The green chnnel of the color
	* @param b		The blue chnnel of the color
	*/
	void ApplyColor(float r, float g, float b);

	/**
	* @param The transform of the object
	*/
	Transform transform;

	/**
	* @brief		Set whether an object is static
	*
	* @pre			The GameObject must exist.
	* @post			The new value is applied to isStatic
	* @param s		The isStatic new value
	* @param includeChildren		Whether the value will be applied to the children


	*/
	void SetIsStatic(bool st, bool includeChildren = true);

protected:
	/**
	* @param The name of the object
	*/
	std::string _name;

	/**
	* @param The active state of the object
	*/
	bool _isActive;

	/**
	* @param Flag the object to be destroyed in the next late update
	*/
	bool _toBeDestroyed;

	/**
	* @param The layer mask
	*/
	unsigned int _layer;

	bool _isStatic;

	/**
	* @param The parent object.
	*/
	GameObject* _parent;

	/**
	* @param The list of children
	*/
	std::list<GameObject*> _children;

	/**
	* @param The list of components
	*/
	std::list<Component*> _components; //Possibly Map

	/**
	* @param Helper method used to print the hierarchy recursively
	* @param indentation	The indentation used for the next line
	* @param output			The string to be printed
	*/
	void PrintHierarchy(int indentation, std::string& output);

};


template <class T>
T* GameObject::GetComponent(std::string componentName) const
{
	std::list<Component*>::const_iterator it;
	it = std::find_if(std::begin(_components), std::end(_components), [&](Component* const component) -> Component* {if (component->GetName() == componentName){ return component; } else { return nullptr; }});

	if (it != std::end(_components))
	{
		return (T*)*it;
	}
	else
	{
		return nullptr;
	}
}

template <class T>
T* GameObject::GetComponentInChild(std::string childName, std::string componentName) const
{
	if (HasChild(childName) == true)
	{
		return (T*)(GetChild(childName)->GetComponent<T>(componentName));
	}
	else
	{
		return nullptr;
	}
}
