#pragma once
#include "SceneManager.h"
#include <assert.h>
#include "..\Core\Logger.h"
#include <stdlib.h>
SceneManager::SceneManager()
{

}

SceneManager& SceneManager::Instance()
{
	static SceneManager instance;
	return instance;
}

Scene& SceneManager::GetCurrentScene()
{
	
	return *m_currentScene;
}
void SceneManager::AddScene(Scene* s)
{
	auto it = m_allScenes.find(s->name);

	if(it != m_allScenes.end())
	{ 
		Logger::LogError("ERROR: A scene named", s->name, "already exists! Program will crash brutally now");
		exit(EXIT_FAILURE);
	}
	else	
	m_allScenes[s->name] = s;
}
void SceneManager::LoadNewScene(std::string sceneName)
{
	auto it = m_allScenes.find(sceneName);

	if (it == m_allScenes.end())
	{
		Logger::LogError("The scene",sceneName,"does not exists.");
		return;		
	}

	if (m_currentScene != nullptr)
	{
		m_currentScene->ExitScene();
		m_currentScene->UnloadAssets();
	}

	m_currentScene = it->second;

	m_currentScene->LoadAssets();
	m_currentScene->Initialize();

	

}
SceneManager::~SceneManager()
{
	auto it = m_allScenes.begin();

	for (; it != m_allScenes.end(); it++)
		delete it->second;

}