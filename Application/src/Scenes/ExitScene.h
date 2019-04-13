#pragma once
#include "Scene/Scene.h"
#include "GUI\GUIElements\GUIImage.h"
#include "GUI\GUIElements\GUIText.h"


class ExitScene : public Scene
{
public:
	ExitScene();
	virtual void LoadAssets() override;
	virtual void UnloadAssets() override;
	virtual void QuitScene() override;
	virtual void Initialize() override;
	virtual void LogicUpdate() override;
	virtual void EngineUpdate() override;
	virtual void LateUpdate() override;

private:



};