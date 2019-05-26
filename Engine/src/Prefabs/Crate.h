#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"

/**
* @class Crate
* @brief Premade gameobject for the Crate object
*
*
* @author Paolo Ferri
* @version 01
* @date 11/05/2019
*
*
* @bug No known bugs.
*/
class Crate : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The Crate object does not exist
	* @post			The Crate object is created
	*/
	Crate();

	/**
	* @brief		Destructor
	* @pre			The Crate object must exist
	* @post			The Crate object is destroyed
	*/
	~Crate();

	/**
	* @brief		Initialize Crate
	* @pre			The Crate object must exist
	* @post			The Crate object is initialized, colliders are added
	*/
	void Start() override;

private:

};