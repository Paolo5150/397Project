#pragma once
#include "FileUtils.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Core\Logger.h"
#include "..\GameObject\Saveable.h"

static class SaveGameManager
{
public:
	static void SaveGame();
	static void LoadGame();
	static void Dump();

private:

};

