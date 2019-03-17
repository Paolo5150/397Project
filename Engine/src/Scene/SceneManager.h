#pragma once

#include <map>
#include <string>

class Scene;

class SceneManager
{
public:
	static SceneManager& Instance();

	Scene& GetCurrentScene();
	void AddScene(Scene* s);
	void LoadNewScene(std::string sceneName);
	void DestroyAllScenes();

	~SceneManager();

private:
	SceneManager();
	SceneManager(const SceneManager& s) = delete;
	std::map<std::string, Scene*> m_allScenes;
	Scene* m_currentScene;

};

