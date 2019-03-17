#pragma once
#include <map>
#include <vector>
#include <list>
#include <string>
#include "..\Core\Timer.h"

class GameObject;
class Skybox;


class Scene
{
public:
	friend class SceneManager;



	Scene(std::string n);
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

	bool GetIsReady() { return m_isReady; };

	std::string name;



protected:
	std::list<GameObject*> m_allGameObjects;
	bool m_isReady;

private:


};