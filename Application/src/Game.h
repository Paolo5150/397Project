#pragma once
#include "Core/Application.h"

class Game : public Application
{

public:

	Game(std::string appName);

	virtual ~Game();
	virtual void AppInitialize() override;
	virtual void AppLogicUpdate() override;	
	virtual void AppShutdown() override;


};
Application* CreateApplication();