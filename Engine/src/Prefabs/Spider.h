#pragma once
#include "../GameObject/GameObject.h"
#include "../Components/AIBase.h"
#include "../Components/BoxCollider.h"

class Spider : public GameObject
{
public:
	Spider(Transform& targetTransform);

	~Spider();

	void SetTarget(Transform& transform);

	Transform* GetTarget() const;

private:

};

