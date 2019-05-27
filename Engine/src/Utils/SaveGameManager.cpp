#include "SaveGameManager.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Core\Logger.h"
#include "..\GameObject\Saveable.h"
#include "..\Prefabs\Hive.h"
#include "..\Prefabs\Player.h"
#include "..\Prefabs\Spider.h"
#include "..\Components\AIBase.h"

void SaveGameManager::SaveGame(std::string filePath)
{
	Logger::LogInfo("Saving game to \"", filePath, "\"");
	std::ofstream file;
	file.open(filePath);

	file << GetCurrentTime() << "\n";
	for (std::list<Saveable*>::const_iterator it = Saveable::GetSaveableObects().begin(); it != Saveable::GetSaveableObects().end(); it++)
	{
		file << (*it)->Save();
	}
	file.close();
}

void SaveGameManager::LoadGame(std::string filePath)
{
	if (FileUtils::IsFileThere(filePath))
	{
		Logger::LogInfo("Save file found, loading \"", filePath, "\"...");

		SceneManager::Instance().GetCurrentScene().RemoveGameobjectsByName("Player");
		SceneManager::Instance().GetCurrentScene().RemoveGameobjectsByName("Spider");
		SceneManager::Instance().GetCurrentScene().RemoveGameobjectsByName("Hive");
		std::ifstream inputFile(filePath);
		std::string line;
		std::getline(inputFile, line, '\n'); //Throw away time/date, can use this later for saves if required
		Logger::LogInfo("Save file originally created at: ", line);

		bool inObject = false; //True when 'inside' the variables for an object
		std::string objectType = "";
		Player* player = nullptr;
		while (std::getline(inputFile, line, '\n'))
		{
			if (inObject)
			{
				if (line == "end")
				{
					inObject = false;
				}
				else
				{
					if (objectType == "Player")
					{
						Player* obj = (Player*)GameAssetFactory::Instance().Create("Player");
						obj->Start();

						float x = stof(line);

						std::getline(inputFile, line, '\n');
						float y = stof(line);

						std::getline(inputFile, line, '\n');
						float z = stof(line);

						std::getline(inputFile, line, '\n');
						float health = stof(line);

						std::getline(inputFile, line, '\n');
						bool hasGun = (bool)stoi(line);

						std::getline(inputFile, line, '\n');
						float ammo = stof(line);

						if (hasGun)
						{
							obj->gn->SetActive(1);
							obj->gn->boxCollider->SetActive(0);
							obj->gn->pointLight->SetActive(0);
							obj->hasGun = true;
						}
						obj->transform.SetPosition(x, y, z);
						//obj->SetRotation(rotX, rotY, rotZ);
						obj->ammoCounter = ammo;
						Logger::LogInfo("Removing ", obj->healthComponent->GetMaxHealth() - health, " health from player");
						obj->healthComponent->AddToHealth(-(obj->healthComponent->GetMaxHealth() - health));
						Logger::LogInfo("New Health: ", obj->healthComponent->GetCurrentHealth());

						SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
						Logger::LogInfo("Added Player from save");
						player = obj;
					}
					else if (objectType == "Spider")
					{
						Spider* obj = (Spider*)GameAssetFactory::Instance().Create("Spider");
						obj->Start();

						float x = stof(line);

						std::getline(inputFile, line, '\n');
						float y = stof(line);

						std::getline(inputFile, line, '\n');
						float z = stof(line);

						std::getline(inputFile, line, '\n');
						float health = stof(line);

						obj->transform.SetPosition(x, y, z);
						//obj->transform.SetRotation(rotX, rotY, rotZ);
						obj->SetTarget(player->transform);
						obj->healthComponent->AddToHealth(-(obj->healthComponent->GetMaxHealth() - health));

						SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
						Logger::LogInfo("Added Spider from save");
					}
					else if (objectType == "Hive")
					{
						Hive* obj = (Hive*)GameAssetFactory::Instance().Create("Hive");
						obj->Start();

						float x = stof(line);

						std::getline(inputFile, line, '\n');
						float y = stof(line);

						std::getline(inputFile, line, '\n');
						float z = stof(line);

						std::getline(inputFile, line, '\n');
						float health = stof(line);

						std::getline(inputFile, line, '\n');
						int state = stoi(line);

						obj->transform.SetPosition(x, y, z);
						obj->healthComponent->AddToHealth(-(obj->healthComponent->GetMaxHealth() - health));
						obj->SetState(state);

						SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
						Logger::LogInfo("Added Hive from save");
					}
					else
					{
						return;
					}
				}
			}
			else
			{
				if (line == "Player" || line == "Spider" || line == "Hive")
				{
					inObject = true;
					objectType = line;
				}
			}
		}
		inputFile.close();
		Logger::LogInfo("Save game loaded!");
	}
	else
	{
		Logger::LogInfo("No save file found");
	}
}

bool SaveGameManager::loadWhenPossible = false;

std::string SaveGameManager::GetCurrentTime()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string s(20, '\0');
	std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return s;
}