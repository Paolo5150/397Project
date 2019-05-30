#pragma once
#include<string>

#include "..\GameObject\GameObject.h"
#include "..\GameObject\Saveable.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\HealthComponent.h"

/**
* @class Hive
* @brief Premade gameobject for the Hive object
*
*
* @author Dylan Green
* @version 01
* @date 14/05/2019
*
*
* @bug No known bugs.
*/
class Hive : public GameObject, public Saveable
{
public:
	/**
	* @brief		Constructor
	*
	* @pre			The hive object does not exist
	* @post			The hive object is created
	*/
	Hive();

	/**
	* @brief		Constructor
	*
	* @pre			The hive object does not exist
	* @post			The hive object is created
	*
	* @param		maxSpiders
	*/
	Hive(int maxSpiders);

	/**
	* @brief		Destructor
	*
	* @pre			The hive object must exist
	* @post			The hive object is destroyed
	*/
	~Hive();

	/**
	*@brief			Sets the maximum number of spiders in the scene before this hive will stop spawning them
	*
	* @pre			The hive object must exist
	*
	* @param		maxSpiders	maximum number of spiders in the scene before this hive will stop spawning them
	*/
	void SetMaxSpiders(unsigned int maxSpiders);

	/**
	*@brief			Gets the maximum number of spiders in the scene before this hive will stop spawning them
	*
	* @pre			The hive object must exist
	*
	* @return		maximum number of spiders in the scene before this hive will stop spawning them
	*/
	unsigned int GetMaxSpiders() const;

	/**
	* @brief		Sets the current model state of the hive
	*
	* @pre			The hive object must exist
	*
	* @param		index	the index of the hive state to set (0-2)
	*/
	void SetState(unsigned int index);

	/**
	* @brief		Returns the current model state of the hive
	*
	* @pre			The hive object must exist
	*
	* @return		the model state of the hive
	*/
	unsigned int GetState() const;

	/**
	* @brief		Initialize hive
	*
	* @pre			The hive object must exist
	* @post			The hive object is initialized, colliders are added
	*/
	void Start() override;

	/**
	* @brief		Overridden callback for update method
	*
	* @pre			The hive object must exist
	*/
	void Update() override;

	/**
	* @brief		Overridden callback for save method
	*
	* @pre			The hive object must exist
	*
	* @return		String containing information to be saved
	*/
	std::string Save() override;
	
	static unsigned int totalHives; //Total number of hives in the game
	HealthComponent* healthComponent;
private:

	bool canSpawnSpiders; //Whether the hive can currently spawn spiders
	int _lastSpawnedSpider; //The last time a spider was spawned
	unsigned int _currentState; //Current model state of the hive
	unsigned int _maxSpiders; //Maximum spiders that can be active in the game before the hive stops spawning them
};