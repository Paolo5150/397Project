#pragma once

#include <GLFW/glfw3.h>
#include "Logger.h"

class Core
{
public:
	static Core& Instance();

	void Initialize();
	void Run();
	void Shutdown();


	~Core();
	bool IsRunning();


private:


	Core();
	bool m_isRunning;
	Core& operator=(Core& other) = delete;
	Core(Core& other) = delete;



};