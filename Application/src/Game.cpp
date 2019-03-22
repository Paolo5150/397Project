#pragma once
#include "Game.h"
#include "Core\Window.h"
#include "Core\Logger.h"
#include "Scene/SceneManager.h"

#include "Scenes/TestScene1.h"
#include "Scenes/TestScene2.h"


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
	SceneManager::Instance().AddScene(new TestScene1());
	SceneManager::Instance().AddScene(new TestScene2());


	//Load first scene
	SceneManager::Instance().LoadNewScene("TestScene1"); //Scene initialize is called here


	
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