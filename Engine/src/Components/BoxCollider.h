#pragma once

#include "Collider.h"


class BoxCollider : public Collider
{

public:
	
	BoxCollider() : Collider("BoxCollider")
	{

	}

	~BoxCollider(){}

	virtual void InitializeMeshRenderer() override;
	void Update() override;


};