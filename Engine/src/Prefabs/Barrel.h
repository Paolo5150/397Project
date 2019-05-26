#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"

/**
* @class Barrel
* @brief Premade gameobject for the barrel object
*
*
* @author Paolo Ferri
* @version 01
* @date 11/05/2018
*
*
* @bug No known bugs.
*/
class Barrel : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The Barrel object does not exist
	* @post			The Barrel object is created
	*/
	Barrel();

	/**
	* @brief		Destructor
	* @pre			The Barrel object must exist
	* @post			The Barrel object is destroyed
	*/
	~Barrel();

	/**
	* @brief		Initialize barrel
	* @pre			The barrel object must exist
	* @post			The barrel object is initialized, colliders are added
	*/
	void Start() override;
private:

};