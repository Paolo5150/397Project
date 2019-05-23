#include "SaveGameManager.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Core\Logger.h"
#include "..\GameObject\Saveable.h"
#include "..\Prefabs\Player.h"
#include "..\Prefabs\Spider.h"
#include "..\Components\AIBase.h"

void SaveGameManager::SaveGame()
{
	Logger::LogInfo("Saving game to \"user/saves/save.dat\"");
	std::ofstream file;
	file.open("user/saves/save.dat");

	file << GetCurrentTime() << "\n";
	for (std::list<Saveable*>::const_iterator it = Saveable::GetSaveableObects().begin(); it != Saveable::GetSaveableObects().end(); it++)
	{
		file << (*it)->Save();
	}
	file.close();
}

void SaveGameManager::LoadGame()
{
	if (FileUtils::IsFileThere("user/saves/save.dat"))
	{
		Logger::LogInfo("Save file found, loading...");

		SceneManager::Instance().GetCurrentScene().RemoveGameobjectsByName("Player");
		SceneManager::Instance().GetCurrentScene().RemoveGameobjectsByName("Spider");
		std::ifstream inputFile("user/saves/save.dat");
		std::string line;
		std::getline(inputFile, line, '\n'); //Throw away time/date, can use this later for saves if required

		bool inObject = false; //True when 'inside' the variables for an object
		std::string objectType = "";
		GameObject* obj = nullptr;
		GameObject* player = nullptr;
		while (std::getline(inputFile, line, '\n'))
		{
			if (inObject)
			{
				if (line == "end")
				{
					inObject = false;
					break;
				}

				if (objectType == "Player")
				{
					obj = new Player();
					obj->Start();
					player = obj;
				}
				else if (objectType == "Spider")
				{
					obj = new Spider();
				}
				else
				{
					return;
				}

				float x = stof(line);

				std::getline(inputFile, line, '\n');
				float y = stof(line);

				std::getline(inputFile, line, '\n');
				float z = stof(line);

				std::getline(inputFile, line, '\n');
				float rotX = stof(line);

				std::getline(inputFile, line, '\n');
				float rotY = stof(line);

				std::getline(inputFile, line, '\n');
				float rotZ = stof(line);

				float health;
				if (objectType == "Player" || objectType == "Spider")
				{
					std::getline(inputFile, line, '\n');
					health = stof(line);
				}

				if (objectType == "Player")
				{
					std::getline(inputFile, line, '\n');
					bool hasGun = bool(stoi(line));

					std::getline(inputFile, line, '\n');
					float ammo = stof(line);

					if (hasGun)
					{
						SceneManager::Instance().GetCurrentScene().RemoveGameobjectsByName("GranadeLauncher");
						((Player*)obj)->gn->SetActive(1);
						((Player*)obj)->gn->boxCollider->SetActive(0);
						((Player*)obj)->gn->pointLight->SetActive(0);
						((Player*)obj)->hasGun = true;
						((Player*)obj)->ammoCounter = ammo;
						((Player*)obj)->healthComponent->AddToHealth(-(((Player*)obj)->healthComponent->GetMaxHealth() - health));
					}
					((Player*)obj)->SetRotation(rotX, rotY, rotZ);
				}
				else if (objectType == "Spider")
				{
					Spider* obj = new Spider();
					((Spider*)obj)->aiBase->SetTarget(player->transform);
					((Spider*)obj)->transform.SetRotation(rotX, rotY, rotZ);
					((Spider*)obj)->healthComponent->AddToHealth(-(((Spider*)obj)->healthComponent->GetMaxHealth() - health));
				}


				if (obj != nullptr)
				{
					obj->transform.SetPosition(x, y, z);
					SceneManager::Instance().GetCurrentScene().AddGameObject(obj);
				}
			}
			else
			{
				if (line == "Player" || line == "Spider")
				{
					inObject = true;
					objectType = line;
				}
			}
			inputFile.close();
			SaveGameManager::loadWhenPossible = false;
		}
	}
	else
	{
		Logger::LogInfo("No save file found");
	}
}

void SaveGameManager::Dump()
{
	for (std::list<Saveable*>::const_iterator it = Saveable::GetSaveableObects().begin(); it != Saveable::GetSaveableObects().end(); it++)
	{
		Logger::LogInfo((*it)->Save());
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