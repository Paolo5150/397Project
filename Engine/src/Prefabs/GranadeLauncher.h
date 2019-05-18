#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\BoxCollider.h"
#include "..\Lighting\PointLight.h"
class GranadeLauncher : public GameObject
{
public:
	GranadeLauncher();
	~GranadeLauncher();

	void Start() override;
	void Update() override;
	BoxCollider* boxCollider;
	PointLight* pointLight;
	bool spin;
private:

};