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
	static void SaveGame(std::string filePath = "user/saves/save.dat");
	static bool LoadGame(std::string filePath = "user/saves/save.dat");
	static bool IsSaveable(std::string type);

	static bool loadWhenPossible;

private:
	static std::string GetCurrentTime();
};

