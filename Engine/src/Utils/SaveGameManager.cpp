#include "SaveGameManager.h"

void SaveGameManager::SaveGame()
{
	//SceneManager::Instance().GetCurrentScene().GetGameobjectsByName();
}

void SaveGameManager::LoadGame()
{

}

void SaveGameManager::Dump()
{
	std::list<Saveable*>::const_iterator it;
	//it = std::find_if(std::begin(Saveable::GetSaveableObects()), std::end(Saveable::GetSaveableObects()), [&](Saveable* object) {return child->GetName() == childName; });

	for (it = Saveable::GetSaveableObects().begin; it != Saveable::GetSaveableObects().end; it++)
	{
		Logger::LogInfo((*it)->Save());
	}
}