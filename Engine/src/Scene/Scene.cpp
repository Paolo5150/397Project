#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(std::string n) : name(n)
{
}
void Scene::AddGameObject(GameObject* go)
{
	/*auto it = allGameObjects.begin();

	for (; it != allGameObjects.end(); it++)
	{
		if (*it == go)
			return;
	}

	allGameObjects.push_back(go);

	auto child = go->children.begin();

	for (; child != go->children.end(); child++)
		AddGameObject(*child);*/
}

void Scene::RemoveGameObject(GameObject* go)
{
}