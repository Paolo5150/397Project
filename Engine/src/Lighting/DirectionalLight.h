#pragma once
#include "Light.h"
#include "..\Core\Camera.h"
#include "..\Graphics\FrameBuffer.h"


class DirectionalLight : public Light
{
public:
	
	DirectionalLight(bool castsShadows = true);
	~DirectionalLight();
	FrameBuffer* shadowMap;
	void SetCastShadowEnable(bool enable);
	bool GetIsCastingShadow();

private:
	bool isCastingShadows;

};
