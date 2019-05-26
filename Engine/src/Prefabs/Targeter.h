#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"

class Companion;

/**
* @class Targeter
* @brief Premade gameobject for the Targeter object
*
*
* @author Paolo Ferri
* @version 01
* @date 15/05/2019
*
*
* @bug No known bugs.
*/
class Targeter : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The Targeter object does not exist
	* @post			The Targeter object is created
	*/
	Targeter();

	/**
	* @brief		Destructor
	* @pre			The Targeter object must exist
	* @post			The Targeter object is destroyed
	*/
	~Targeter();


	/**
	* @brief		Initialize Targeter
	* @pre			The Targeter object must exist
	* @post			The Targeter object is initialized, colliders are added
	*/
	void Start() override;
	/**
	* @brief		Overridden callback for update method
	* @pre			The player object must exist
	*/
	void Update() override;

	/**
	* @brief		The direction of movement
	*/
	glm::vec3 shootDirection;


private:
	/**
	* @brief		Reference to companion object
	*/
	Companion* companionRef;

	/**
	* @brief		Movement speed
	*/
	float speed;

	/**
	* @brief		Tracks the amount of time the object has been alive for
	*/
	float lifeTimer;
};