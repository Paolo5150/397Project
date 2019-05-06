#pragma once
#include <string>

#include "../GameObject/GameObject.h"
#include "..\Utils\AssetLoader.h"

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

	void Start() override;

	void Update() override;

private:

};

