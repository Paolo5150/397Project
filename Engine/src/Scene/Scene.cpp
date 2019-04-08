#include "Scene.h"
#include "SceneManager.h"
#include "..\Core\Logger.h"
#include "..\Utils\GameAssetFactory.h"
#include "..\Core\Input.h"
Scene::Scene(std::string n) : name(n)
{
	skybox = nullptr;
}
void Scene::AddGameObject(GameObject* go)
{
	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
		{
			if (*it == go)
				return;
		}

	m_allGameObjects.push_back(go);

	auto child = go->GetChildList().begin();

	for (; child != go->GetChildList().end(); child++)
			AddGameObject(*child);
}


void Scene::LateUpdate()
{
	// Delete ToBeDestroyed gameobjects here
	//Logger::LogInfo("Late update");
	auto it = m_allGameObjects.begin();
	for (; it != m_allGameObjects.end();)
	{
		if ((*it)->GetToBeDestroyed())
		{
			delete *it;
			it = m_allGameObjects.erase(it);
		}
		else
			it++;
	}	
}

void Scene::EngineUpdate()
{
	//Logger::LogError("Updating", m_allGameObjects.size());
	if (skybox != nullptr)
		skybox->EngineUpdate();

	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
	{
		(*it)->EngineUpdate();
	}
}

void Scene::LogicUpdate()
{
	//Logger::LogError("Updating", m_allGameObjects.size());
	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
	{
		(*it)->Update();
	}
}

void Scene::ExitScene()
{
	auto it = m_allGameObjects.begin();

	for (; it != m_allGameObjects.end(); it++)
	{

		delete (*it);
	}

	m_allGameObjects.clear();
	GameAssetFactory::Instance().CleanUp();
	Input::Update();
}