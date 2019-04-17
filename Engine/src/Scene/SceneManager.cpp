#pragma once
#include "SceneManager.h"
#include <assert.h>
#include "..\Core\Logger.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\ApplicationEvents.h"
#include "Scene.h"
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
	{
		Logger::LogInfo("Added scene",s->name);

		m_allScenes[s->name] = s;
	}
}
void SceneManager::LoadNewScene(std::string sceneName)
{
	//Check if scene is already loaded
	if(m_currentScene != nullptr)
	{
		if (m_currentScene->name == sceneName)
			return;
	}

	auto it = m_allScenes.find(sceneName);

	if (it == m_allScenes.end())
	{
		Logger::LogError("The scene",sceneName,"does not exists.");
		return;		
	}

	if (m_currentScene != nullptr)
	{
		m_currentScene->QuitScene();
		m_currentScene->UnloadAssets();
		m_currentScene->m_isReady = false;
	}

	EventDispatcher::Instance().DispatchEvent(new SceneChangedEvent(m_currentScene));
	m_currentScene = it->second;

	m_currentScene->LoadAssets();
	m_currentScene->Initialize();
	m_currentScene->m_isReady = true;
}

void SceneManager::DestroyAllScenes()
{
	auto it = m_allScenes.begin();

	for (; it != m_allScenes.end(); it++)
	{
		it->second->QuitScene();
		it->second->UnloadAssets(); //Not sure about this one
		delete it->second;
	}
}
SceneManager::~SceneManager()
{


}