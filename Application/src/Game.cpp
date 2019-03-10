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
{}
void Game::AppStart()
{}
void Game::AppUpdate()
{}
void Game::AppShutdown()
{}