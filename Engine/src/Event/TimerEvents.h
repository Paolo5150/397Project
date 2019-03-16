#pragma once
#include "Event.h"

class LogicUpdateEvent : public Event
{
public:
	LogicUpdateEvent() {}
	~LogicUpdateEvent() {}
};

class EngineUpdateEvent : public Event
{
public:
	EngineUpdateEvent() {}
	~EngineUpdateEvent() {}
};

class LateUpdateEvent : public Event
{
public:
	LateUpdateEvent() {}
	~LateUpdateEvent() {}
};

class RenderEvent : public Event
{
public:
	RenderEvent() {}
	~RenderEvent() {}
};