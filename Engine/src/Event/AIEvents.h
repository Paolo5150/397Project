#pragma once
#include "Event.h"

class EnemySpottedEvent : public Event
{
public:
	/**
	* @brief		Creates event object
	*
	* @pre			The event object does not exist
	* @post			The event object is created
	*/
	EnemySpottedEvent() {}

	/**
	* @brief		Destroy the event object
	*
	* @pre			The event object exists
	* @post			The event object is destroyed
	*/
	~EnemySpottedEvent() {}
};