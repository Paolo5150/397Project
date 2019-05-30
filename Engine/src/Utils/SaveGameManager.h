#pragma once
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>

#include "FileUtils.h"
#include "GameAssetFactory.h"

/*
--------------------
Format Information
--------------------
First line is time/date of save
----------
ObjectType (Player, Pumpkin, etc)
PosX
PosY
PosZ
RotX
RotY
RotZ
Health (Living objects)
Ammo (Player)
TotalPumpkinsShot (Player)
TotalSpidersKilled (Player)
end
----------
*/

/**
* @class SaveGameManager
* @brief Save assets inheriting from Saveable and allows for loading them back into the game
*
* @author Dylan Green
* @version 01
* @date 22/05/2019
*
*
* @bug No known bugs.
*/
static class SaveGameManager
{
public:
	/**
	* @brief	Saves all the objects that inherit from the Saveable class
	*
	* @param	filePath	path to the file to save to, folders must exist already
	*/
	static void SaveGame(std::string filePath = "user/saves/save.dat");

	/**
	* @brief	Loads all valid objects in a save file, returns false if it encounters an invalid save file
	*
	* @param	filePath	path to the file to load from
	* @return	true if file was loaded successfully, false if it was not found or invalid/corrupted
	*/
	static bool LoadGame(std::string filePath = "user/saves/save.dat");

	/**
	* @brief	Returns whether the specified file exists and is a valid save file
	*
	* @param	filePath	path to the file to check
	* @return	true if file exists, false if it was not found or invalid/corrupted
	*/
	static bool CanLoadGame(std::string filePath = "user/saves/save.dat");

	/**
	* @brief	Returns whether the given type is set up for saving and loading
	*
	* @return	true if the type is considered saveable
	*/
	static bool IsSaveable(std::string type);

	/**
	* @brief	Variable to allow scenes to manage what to do when loading a game
	*/
	static bool loadWhenPossible;

private:
	/**
	* @brief	Returns the current date and time
	*/
	static std::string GetCurrentTime();
};

