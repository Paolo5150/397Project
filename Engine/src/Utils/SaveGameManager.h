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

static class SaveGameManager
{
public:
	static void SaveGame(std::string filePath = "user/saves/save.dat");
	static void LoadGame(std::string filePath = "user/saves/save.dat");
	static bool IsSaveable(std::string type);

	static bool loadWhenPossible;

private:
	static std::string GetCurrentTime();
};

