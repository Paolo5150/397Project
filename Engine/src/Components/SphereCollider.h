#pragma once

#include "Collider.h"


class SphereCollider : public Collider
{

public:

	SphereCollider() : Collider("SphereCollider")
	{

	}

	~SphereCollider(){}

	virtual void InitializeMeshRenderer() override;
	void Update() override;


};