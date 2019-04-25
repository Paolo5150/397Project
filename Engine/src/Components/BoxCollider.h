#pragma once

#include "Collider.h"
#include <vector>

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
	void Initialize(){ transform.SetIgnoreParentRotation(0); };

	std::vector<glm::vec3> GetWorldPoints();


};