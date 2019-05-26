#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"

/**
* @class Ship
* @brief Premade gameobject for the Ship object
*
*
* @author Paolo Ferri
* @version 01
* @date 15/05/2018
*
*
* @bug No known bugs.
*/
class Ship : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The Ship object does not exist
	* @post			The Ship object is created
	*/
	Ship();
	/**
	* @brief		Destructor
	* @pre			The Ship object must exist
	* @post			The Ship object is destroyed
	*/
	~Ship();

	/**
	* @brief		Initialize Ship
	* @pre			The Ship object must exist
	* @post			The Ship object is initialized, colliders are added
	*/
	void Start() override;
private:

};