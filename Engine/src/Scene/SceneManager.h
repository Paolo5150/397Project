#pragma once
#include "Scene.h"
#include <map>
#include <string>

class SceneManager
{
public:
	static SceneManager& Instance();

	Scene& GetCurrentScene();
	void AddScene(Scene* s);
	void LoadNewScene(std::string sceneName);
	~SceneManager();

private:
	SceneManager();
	SceneManager(const SceneManager& s) = delete;
	std::map<std::string, Scene*> m_allScenes;
	Scene* m_currentScene;

};