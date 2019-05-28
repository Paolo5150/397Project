#pragma once
#include "..\GameObject\GameObject.h"
#include "AssetLoader.h"
#include <vector>

/**
* @class GameAssetFactory
* @brief Helper class that creates objects of type internal asset by name
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2019
*
*
* @bug No known bugs.
*/
class GameAssetFactory
{
public:
	/**
	* @brief						Return the game asset factory instance
	* @pre							The instance musts exist
	* @post							The instance is returned
	* @return						The game asset factory instance
	*/
	static GameAssetFactory Instance();

	/**
	* @brief						Destroy the game asset factory
	* @pre							The instance musts exist
	* @post							The game asset factory is destroyed
	*/
	~GameAssetFactory();

	/**
	* @brief						Create an object of specific type
	* @pre							The instance musts exist
	* @post							The object is created and returned
	* @param type					The object type
	* @param name					The object name
	* @return						The created object (will need to be casted to the appropriate type)
	*/
	InternalAsset* Create(std::string type,std::string name = "");

	/**
	* @brief						Destroy unmanaged internal assets
	* @pre							The instance musts exist
	* @post							The internal assets stored are destroyed

	*/
	void CleanUp();


private:
	/**
	* @brief						All the internal assets managed bybthis class
	*/
	std::vector<InternalAsset*> toBeDeletedASsets;

	/**
	* @brief						Create the game asset factory instance
	*/
	GameAssetFactory();
};


