#include "SaveGameManager.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Core\Logger.h"
#include "..\GameObject\Saveable.h"
#include "..\Prefabs\Hive.h"
#include "..\Prefabs\Player.h"
#include "..\Prefabs\Spider.h"
#include "..\Prefabs\Companion.h"
#include "..\Components\AIBase.h"
#include "..\Components\HealthComponent.h"

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

bool SaveGameManager::LoadGame(std::string filePath)
{
	if (FileUtils::IsFileThere(filePath))
	{
		Logger::LogInfo("Save file found, loading \"", filePath, "\"...");

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

						std::getline(inputFile, line, '\n');
						float pumpkinsShot = stof(line);

						std::getline(inputFile, line, '\n');
						float spidersKilled = stof(line);

						obj->transform.SetPosition(x, y, z);

						obj->healthComponent->AddToHealth(-(obj->healthComponent->GetMaxHealth() - health));

						if (hasGun)
						{
							obj->gn->SetActive(1);
							obj->gn->GetCollider()->SetActive(0);
							obj->gn->pointLight->SetActive(0);
							obj->hasGun = true;
						}

						obj->ammoCounter = ammo;

						Player::SetTotalPumpkinsShot(pumpkinsShot);
						Spider::SetTotalSpidersKilled(spidersKilled);

						SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
						player = obj;
					}
					else if (objectType == "Spider")
					{
						Spider* obj = (Spider*)GameAssetFactory::Instance().Create("Spider");

						float x = stof(line);

						std::getline(inputFile, line, '\n');
						float y = stof(line);

						std::getline(inputFile, line, '\n');
						float z = stof(line);

						std::getline(inputFile, line, '\n');
						float health = stof(line);

						obj->transform.SetPosition(x, y, z);
						obj->GetComponent<HealthComponent>("HealthComponent")->AddToHealth(-(obj->GetComponent<HealthComponent>("HealthComponent")->GetMaxHealth() - health));

						SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
					}
					else if (objectType == "Companion")
					{
						Companion* obj = (Companion*)GameAssetFactory::Instance().Create("Companion");

						float x = stof(line);

						std::getline(inputFile, line, '\n');
						float y = stof(line);

						std::getline(inputFile, line, '\n');
						float z = stof(line);

						std::getline(inputFile, line, '\n');
						float health = stof(line);

						obj->transform.SetPosition(x, y, z);
						obj->GetComponent<HealthComponent>("HealthComponent")->AddToHealth(-(obj->GetComponent<HealthComponent>("HealthComponent")->GetMaxHealth() - health));

						SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
					}
					else if (objectType == "Hive")
					{
						Hive* obj = (Hive*)GameAssetFactory::Instance().Create("Hive");

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
						obj->GetComponent<HealthComponent>("HealthComponent")->AddToHealth(-(obj->GetComponent<HealthComponent>("HealthComponent")->GetMaxHealth() - health));
						obj->SetState(state);

						SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (IsSaveable(line))
				{
					inObject = true;
					objectType = line;
				}
			}
		}
		inputFile.close();
		Logger::LogInfo("Save game loaded!");
		return true;
	}
	else
	{
		Logger::LogInfo("No save file found");
		return false;
	}
}

bool SaveGameManager::CanLoadGame(std::string filePath)
{
	if (FileUtils::IsFileThere(filePath))
	{
		std::ifstream inputFile(filePath);
		std::string line;
		std::getline(inputFile, line, '\n'); //Time/date

		bool inObject = false; //True when 'inside' the variables for an object
		std::string objectType = "";

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
						//x
						std::getline(inputFile, line, '\n'); //y
						std::getline(inputFile, line, '\n'); //z
						std::getline(inputFile, line, '\n'); //health
						std::getline(inputFile, line, '\n'); //hasGun
						std::getline(inputFile, line, '\n'); //ammo
						std::getline(inputFile, line, '\n'); //pumpkinsshot
						std::getline(inputFile, line, '\n'); //spiderskilled
					}
					else if (objectType == "Spider")
					{
						//x
						std::getline(inputFile, line, '\n'); //y
						std::getline(inputFile, line, '\n'); //z
						std::getline(inputFile, line, '\n'); //health
					}
					else if (objectType == "Companion")
					{
						//x
						std::getline(inputFile, line, '\n'); //y
						std::getline(inputFile, line, '\n'); //z
						std::getline(inputFile, line, '\n'); //health
					}
					else if (objectType == "Hive")
					{
						//x
						std::getline(inputFile, line, '\n'); //y
						std::getline(inputFile, line, '\n'); //z
						std::getline(inputFile, line, '\n'); //health
						std::getline(inputFile, line, '\n'); //state
					}
					else
					{
						return false; //Not valid save
					}
				}
			}
			else
			{
				if (IsSaveable(line))
				{
					inObject = true;
					objectType = line;
				}
			}
		}
		inputFile.close();
		return true; //Valid save
	}
	else
	{
		return false; //No save found
	}
}

bool SaveGameManager::IsSaveable(std::string type)
{
	if (type == "Player" || type == "Spider" || type == "Companion" || type == "Hive")
	{
		return true;
	}
	else
	{
		return false;
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