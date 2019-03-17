#pragma once
#include <map>
#include <vector>
#include <list>
#include <string>


class GameObject;
class Skybox;


class Scene
{
public:
	Scene(std::string n) : name(n)
	{

	}

	virtual ~Scene() {};

	void AddGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go);

	virtual void LoadAssets() = 0;
	virtual void UnloadAssets() = 0;
	virtual void ExitScene() = 0;
	virtual void Initialize() = 0;
	virtual void LogicUpdate() = 0;
	virtual void EngineUpdate() = 0;
	virtual void LateUpdate() = 0;

	std::string name;
	Skybox* skybox;

private:
	std::list<GameObject*> m_allGameObjects;


};