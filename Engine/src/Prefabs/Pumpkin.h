#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#

/**
* @class Pumpkin
* @brief Premade gameobject for the Pumpkin object
*
*
* @author Paolo Ferri
* @version 01
* @date 15/05/2019
*
*
* @bug No known bugs.
*/
class Pumpkin : public GameObject
{
public:
	/**
	* @brief		Available states
	*/
	enum STATE
	{
		SHOT,
		GROUND
	};
	/**
	* @brief		Constructor
	* @pre			The Pumpkin object does not exist
	* @post			The Pumpkin object is created
	*/
	Pumpkin();

	/**
	* @brief		Destructor
	* @pre			The Pumpkin object must exist
	* @post			The Pumpkin object is destroyed
	*/
	~Pumpkin();

	/**
	* @brief		Initialize Pumpkin
	* @pre			The Pumpkin object must exist
	* @post			The Pumpkin object is initialized, colliders are added
	*/
	void Start() override;

	/**
	* @brief		The current state
	*/
	STATE state;

	/**
	* @brief		Overridden callback for update method
	* @pre			The pumpkin object must exist
	*/
	void Update() override;

	/**
	* @brief		Direciton of movement
	* @pre			The pumpkin object must exist
	*/
	glm::vec3 shootDirection;

	/**
	* @return		The damage given
	*/
	static float GetDamageGiven(){ return damageGiven; }

private:
	/**
	* @return		The damage given to colliding objects
	*/
	static float damageGiven;

	/**
	* @return		Movement speed
	*/
	float speed;

	/**
	* @return		Tracks the time the pumpkin has been alive
	*/
	float lifeTimer;
};