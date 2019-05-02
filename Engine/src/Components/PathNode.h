#pragma once

#include "..\GameObject\GameObject.h"

class PathNode : public GameObject
{
public:
	PathNode();
	~PathNode();

	void OnCollision(GameObject* go) override;


};