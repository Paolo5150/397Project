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


