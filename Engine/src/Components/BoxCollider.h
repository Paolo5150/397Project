#pragma once

#include "Collider.h"


class BoxCollider : public Collider
{

public:
	
	BoxCollider() : Collider("BoxCollider")
	{
		colliderType = BOX;
	}

	~BoxCollider(){}

	virtual void InitializeMeshRenderer() override;
	void Update() override;
	void Initialize(){ transform.SetIgnoreParentRotation(1); };



};