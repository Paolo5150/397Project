#pragma once
#include <string>
#include "..\Scene\Scene.h"


class Application 
{

public:
	friend class Core;
	std::string name;

	Application();

	virtual void AppInitialize(){};

	virtual void AppLogicUpdate();
	virtual void AppShutdown(){};

	virtual void AppEngineUpdate();
	virtual void AppLateUpdate();


	virtual ~Application() {};

protected:


};