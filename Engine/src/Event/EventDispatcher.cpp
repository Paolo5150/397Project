#include "EventDispatcher.h"

EventDispatcher& EventDispatcher::Instance()
{
	static EventDispatcher instance;
	return instance;
}

void EventDispatcher::DispatchEvent(Event* e)
{
	std::string eventName = typeid(*e).name();
	auto it = allCallbacks.find(eventName);

	if (it != allCallbacks.end())
	{
		for (auto i = 0; i < it->second.size(); i++)
		{
			it->second[i](e);
		}
	}

	delete e;
}