#pragma once
#include <GLFW/glfw3.h>
#include "Logger.h"
#include "..\Event\EventDispatcher.h"

class Timer
{
public:

	static void Initialize();
	static void Update();
	static float GetDeltaS();
	static float GetTimeS();
	static void SetDisplayFPS(bool dfps);

private:
	static bool displayFPS;
	static double timerMultiplier;
	static double delta;
	static int FPSCounter;
	static double FPS;
	static double limitFPS;
	static double now;
	static double prev;





};