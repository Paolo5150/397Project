#pragma once
#include "Game.h"
#include "Core\Window.h"
#include "Core\Logger.h"

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
	Logger::LogInfo("Game initialized");
}
void Game::AppStart()
{
	Logger::LogInfo("Game Start");
}
void Game::AppLogicUpdate()
{
	Logger::LogInfo("Game logic update");
}
void Game::AppShutdown()
{
	Logger::LogInfo("Game shutdown");
}