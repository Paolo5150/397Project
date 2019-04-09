#pragma once
#include "Event.h"
#include "..\Core\Logger.h"
#include "..\Utils\FileUtils.h"
#include <functional>
#include <list>
#include <map>
#include <sstream>

class CallbackObj
{
public:
	CallbackObj(std::string id, std::function<bool(Event*)> f) : ID(id),fn(f){};
	std::function<bool(Event*)> fn;
	std::string ID;

};

class EventDispatcher
{
public:
	static EventDispatcher& Instance();


	void DispatchEvent(Event* e);

	template<class T>	
	std::string SubscribeCallback(std::function<bool(Event*)> callback);

	template<class T>
	void UnsubscribeCallback(std::string token);

private:
	EventDispatcher() {};
	EventDispatcher& operator=(const EventDispatcher& other) = delete;
	EventDispatcher(const EventDispatcher& other) = delete;

	std::map<std::string,std::list < CallbackObj >> allCallbacks;
};


template<class T>
void EventDispatcher::UnsubscribeCallback(std::string token)
{
	std::string eventName = FileUtils::GetClassNameW<T>();

	auto it = allCallbacks[eventName].begin();

	for (; it != allCallbacks[eventName].end();)
	{
		if (it->ID == token)
		{
			it = allCallbacks[eventName].erase(it);
		}
		else
			it++;
	}

}


template<class T>
std::string EventDispatcher::SubscribeCallback(std::function<bool(Event*)> callback)
{
	std::string eventName = FileUtils::GetClassNameW<T>();

	std::stringstream ss;
	ss << eventName;
	ss << "_";
	ss << *(long *)(char *)&callback;

	allCallbacks[eventName].push_back(CallbackObj(ss.str(),callback));
	return ss.str();
}