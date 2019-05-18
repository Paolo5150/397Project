#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\BoxCollider.h"

class GranadeLauncher : public GameObject
{
public:
	GranadeLauncher();
	~GranadeLauncher();

	void Start() override;
	BoxCollider* boxCollider;
private:

};