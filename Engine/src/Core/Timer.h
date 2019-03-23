#pragma once
#include <GLFW/glfw3.h>

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
	static bool m_displayFPS;
	static double m_timerMultiplier;
	static double m_delta;
	static int m_FPSCounter;
	static double m_FPS;
	static double m_limitFPS;
	static double m_now;
	static double m_prev;





};