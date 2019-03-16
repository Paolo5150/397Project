#pragma once
#include "Event.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int w, int h) : width(w),height(h) {}
	~WindowResizeEvent() {}

	int width;
	int height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent()  {}
	~WindowCloseEvent() {}


};

