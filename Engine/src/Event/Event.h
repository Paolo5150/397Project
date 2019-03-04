#pragma once

class Event
{
public:
	Event() {};
	virtual ~Event() {};

};

class LogicUpdateEvent : public Event
{
public:
	LogicUpdateEvent() {}
	~LogicUpdateEvent() {}
};