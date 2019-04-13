#pragma once
#include "Game.h"
#include "Core\Window.h"
#include "Core\Logger.h"
#include "Scene/SceneManager.h"

#include "Scenes/MainScene.h"
#include "Scenes/ExitScene.h"


Application* CreateApplication()
{
	return new Game("397 Project");
}

Game::Game(std::string appName)
{
	this->name = appName;


	
}

Game::~Game()
{}


void Game::AppInitialize()
{
	//Create all scenes here, might need to use LUA...?
	SceneManager::Instance().AddScene(new MainScene());
	SceneManager::Instance().AddScene(new ExitScene());


	//Load first scene
	SceneManager::Instance().LoadNewScene("MainScene"); //Scene initialize is called here


	
}

void Game::AppLogicUpdate()
{
	//Logger::LogInfo("Game logic update");
	Application::AppLogicUpdate();
}
void Game::AppShutdown()
{
	
	SceneManager::Instance().DestroyAllScenes();
	//Logger::LogInfo("Game shutdown");
}