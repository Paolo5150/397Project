#pragma once

#include "Timer.h"
#include "..\Event\TimerEvents.h"

bool Timer::displayFPS;
double Timer::timerMultiplier;
double Timer::delta;
int Timer::FPSCounter;
double Timer::FPS;
double Timer::limitFPS;
double Timer::now;
double Timer::prev;


void Timer::Initialize()
{
	delta = 0;

	FPSCounter = 0;
	FPS = 1;
	limitFPS = 1.0 / FPS;
	now = glfwGetTime();
	prev = glfwGetTime();
	timerMultiplier = 1.0;
	displayFPS = 0;
}

float Timer::GetDeltaS()
{
	return delta * timerMultiplier;
}

void Timer::SetDisplayFPS(bool dfps)
{
	displayFPS = dfps;
}

float Timer::GetTimeS()
{
	return glfwGetTime()* timerMultiplier;
}


void Timer::Update()
{
	static float accumulator = 0;

	now = glfwGetTime();
	delta = (now - prev);
	prev = now;

	accumulator += delta;

	if (accumulator >= limitFPS)
	{
		static float fixedNow = glfwGetTime();
		static float fixedPrev = glfwGetTime();

		fixedNow = glfwGetTime();
		delta = (fixedNow - fixedPrev);
		fixedPrev = fixedNow;

		accumulator = 0;

		EventDispatcher::Instance().DispatchEvent(new LogicUpdateEvent());
		EventDispatcher::Instance().DispatchEvent(new EngineUpdateEvent());
		EventDispatcher::Instance().DispatchEvent(new RenderEvent());
		EventDispatcher::Instance().DispatchEvent(new LateUpdateEvent());


	}

	FPSCounter++;

	if (displayFPS)
	{
		static double st = 0;
		st += delta;
		if (st >= 1)
		{
			st = 0;
			LOG_INFO("FPS: {}", FPSCounter);
			FPSCounter = 0;
		}
	}
}