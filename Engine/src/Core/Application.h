#pragma once
#include <string>
#include "..\Scene\Scene.h"


class Application 
{

public:
	friend class Core;
	std::string name;

	Application();

	virtual void AppInitialize() = 0;

	virtual void AppLogicUpdate() = 0;
	virtual void AppShutdown() = 0;

	virtual void AppEngineUpdate();
	virtual void AppLateUpdate();


	virtual ~Application() {};

protected:
	Scene* m_currentScene;

};