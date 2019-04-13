#pragma once
#include "Scene/Scene.h"


class MainScene : public Scene
{
public:
	MainScene();
	virtual void LoadAssets() override;
	virtual void UnloadAssets() override;
	virtual void QuitScene() override;
	virtual void Initialize() override;
	virtual void LogicUpdate() override;


	//Camera* cam;
	GameObject* quad;

private:


};