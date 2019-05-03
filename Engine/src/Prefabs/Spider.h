#pragma once
#include "../GameObject/GameObject.h"
#include "../Graphics/AnimatedModel.h"
#include "../Components/AIBase.h"
#include "../Components/BoxCollider.h"

class Spider : public AnimatedModel
{
public:
	Spider();

	Spider(Transform& targetTransform);

	~Spider();

	void SetTarget(Transform& transform);

	Transform* GetTarget() const;

private:

};

