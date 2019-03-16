#pragma once

#include "..\Graphics\API_Opengl.h"
#include "Window.h"
#include "Logger.h"
#include "Timer.h"
#include "Application.h"
#include <iostream>

extern "C++" Application* CreateApplication();



class Core
{
public:
	static Core& Instance();

	void Initialize();
	void Run();
	void Shutdown();

	bool LogicUpdate(Event* e);
	bool EngineUpdate(Event* e);
	bool LateUpdate(Event* e);
	bool Render(Event* e);

	GraphicsAPI& GetGraphicsAPI();

	~Core();
	bool IsRunning();


private:

	Core();
	Core& operator=(const Core& other) = delete;
	Core(const Core& other) = delete;

	Application* m_runningApplication;
	bool m_isRunning;
	GraphicsAPI* graphicsAPI;


};