#pragma once
#include "Event.h"
#include <functional>
#include <vector>
#include <map>



class EventDispatcher
{
public:
	static EventDispatcher& Instance();


	void DispatchEvent(Event* e);

	template<class T>	
	void SubscribeCallback(std::function<bool(Event*)> callback);

private:
	EventDispatcher() {};
	EventDispatcher& operator=(const EventDispatcher& other) = delete;
	EventDispatcher(const EventDispatcher& other) = delete;

	std::map<std::string,std::vector < std::function<bool(Event*)>>> allCallbacks;
};





template<class T>
void EventDispatcher::SubscribeCallback(std::function<bool(Event*)> callback)
{
	std::string eventName = typeid(T).name();
	allCallbacks[eventName].push_back(callback);

}