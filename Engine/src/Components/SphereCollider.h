#pragma once

#include "Collider.h"


class SphereCollider : public Collider
{

public:

	SphereCollider() : Collider("SphereCollider")
	{
		colliderType = SPHERE;

	}

	~SphereCollider(){}

	virtual void InitializeMeshRenderer() override;
	void Update() override;
	void Initialize(){ transform.SetIgnoreParentRotation(1); };

};