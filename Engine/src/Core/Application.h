#pragma once
#include <string>


class Application 
{

public:
	friend class Core;
	std::string name;

	virtual void AppInitialize() = 0;
	virtual void AppStart() = 0;
	virtual void AppUpdate() = 0;

	virtual void AppShutdown() = 0;

	virtual ~Application();
	bool isPaused;


protected:
	

};