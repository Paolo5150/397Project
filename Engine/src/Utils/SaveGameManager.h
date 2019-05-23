#pragma once
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include "FileUtils.h"

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
	static void SaveGame();
	static void LoadGame();
	static void Dump();

	static bool loadWhenPossible;

private:
	static std::string GetCurrentTime();
};

