#pragma once
#include "Scene/Scene.h"


class TestScene1 : public Scene
{
public:
	TestScene1();
	virtual void LoadAssets() override;
	virtual void UnloadAssets() override;
	virtual void ExitScene() override;
	virtual void Initialize() override;
	virtual void LogicUpdate() override;


	//Camera* cam;
	GameObject* quad;

private:


};