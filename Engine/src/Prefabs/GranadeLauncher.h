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
	void Update() override;
	BoxCollider* boxCollider;
	bool spin;
private:

};