#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#

/**
* @class PumpkinBunch
* @brief Premade gameobject for the PumpkinBunch object
*
*
* @author Dylan Green
* @version 01
* @date 19/05/2019
*
*
* @bug No known bugs.
*/
class PumpkinBunch : public GameObject
{
public:
	enum STATE
	{
		SHOT,
		GROUND
	};

	/**
	* @brief		Constructor
	*
	* @pre			The pumpkinbunch object does not exist
	* @post			The pumpkinbunch object is created
	*/
	PumpkinBunch();

	/**
	* @brief		Destructor
	*
	* @pre			The pumpkinbunch object must exist
	* @post			The pumpkinbunch object is destroyed
	*/
	~PumpkinBunch();

	/**
	* @brief		Initialize pumpkinbunch
	*
	* @pre			The pumpkinbunch object must exist
	* @post			The pumpkinbunch object is initialized, colliders are added
	*/
	void Start() override;

	static unsigned totalPumpkinBunches; //Total number of pumpkinbunches in the game

private:
};