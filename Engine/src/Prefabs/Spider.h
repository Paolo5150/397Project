#pragma once
#include <string>

#include "../GameObject/GameObject.h"
#include "../Graphics/AnimatedModel.h"
#include "../Components/AIBase.h"
#include "../Components/BoxCollider.h"

class Spider : public GameObject
{
public:
	Spider();

	Spider(float posX, float posY, float posZ);

	Spider(Transform& targetTransform);

	Spider(Transform& targetTransform, float posX, float posY, float posZ);

	~Spider();

	void SetTarget(Transform& transform);

	Transform* GetTarget() const;

private:

};

