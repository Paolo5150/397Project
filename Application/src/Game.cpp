#pragma once
#include "Game.h"

Application* CreateApplication()
{
	return new Game("My Game");
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