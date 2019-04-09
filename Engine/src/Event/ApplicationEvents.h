#pragma once
#include "Event.h"

class Scene;

class SceneChangedEvent : public Event
{
public:
	SceneChangedEvent(Scene* s) :  currentScene(s) {}
	~SceneChangedEvent() {}
	Scene* currentScene;
};

class QuitRequestEvent : public Event
{
public:
	QuitRequestEvent() {}
	~QuitRequestEvent() {}

};

