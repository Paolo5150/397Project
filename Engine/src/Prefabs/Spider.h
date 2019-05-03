#pragma once
#include "../GameObject/GameObject.h"
#include "../Graphics/AnimatedModel.h"
#include "../Components/AIBase.h"
#include "../Components/BoxCollider.h"

class Spider : public GameObject
{
public:
	Spider();

	Spider(Transform& targetTransform);

	~Spider();

	void SetTarget(Transform& transform);

	Transform* GetTarget() const;

private:

};

