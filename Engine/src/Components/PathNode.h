#pragma once

#include "..\GameObject\GameObject.h"
#include "BoxCollider.h"

class PathNode : public GameObject
{
public:
	PathNode();
	~PathNode();

	void OnCollision(GameObject* go) override;
	void Start() override;

	int cost;
	BoxCollider* sc;

};