#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"

/**
* @class Tree
* @brief Premade gameobject for the Tree object
*
*
* @author Dylan Green
* @version 01
* @date 18/05/2019
*
*
* @bug No known bugs.
*/
class Tree : public GameObject
{
public:
	/**
	* @brief		Constructor
	*
	* @pre			The tree object does not exist
	* @post			The tree object is created
	*/
	Tree();

	/**
	* @brief		Destructor
	*
	* @pre			The tree object must exist
	* @post			The tree object is destroyed
	*/
	~Tree();

	/**
	* @brief		Initialize tree
	*
	* @pre			The tree object must exist
	* @post			The tree object is initialized, colliders are added
	*/
	void Start() override;

private:

};