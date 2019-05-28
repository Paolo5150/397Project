#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"

/**
* @class Cabin
* @brief Premade gameobject for the Cabin object
*
*
* @author Paolo Ferri
* @version 01
* @date 11/05/2019
*
*
* @bug No known bugs.
*/
class Cabin : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The cabin object does not exist
	* @post			The cabin object is created
	*/
	Cabin();

	/**
	* @brief		Destructor
	* @pre			The cabin object must exist
	* @post			The cabin object is destroyed
	*/
	~Cabin();

	/**
	* @brief		Initialize barrel
	* @pre			The cabin object must exist
	* @post			The cabin object is initialized, colliders are added
	*/
	void Start() override;
private:

};