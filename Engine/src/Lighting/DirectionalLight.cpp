#include "DirectionalLight.h"
#include "..\Core\Core.h"
#include "LightingManager.h"

DirectionalLight::DirectionalLight(bool castShadows) : Light("DirectionalLight",DIRECTIONAL)
{
	transform.SetRotation(90, 0, 0);	
	shadowMap = NULL;

	SetCastShadowEnable(castShadows);

}

void DirectionalLight::SetCastShadowEnable(bool enable)
{
	isCastingShadows = enable;

	if (shadowMap == NULL)
		shadowMap = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(1024 * 8, 1024 * 8, 0);
}

bool DirectionalLight::GetIsCastingShadow()
{
	return isCastingShadows;
}

DirectionalLight::~DirectionalLight()
{
	if (shadowMap != NULL)
		delete shadowMap;

	LightManager::Instance().RemoveLight(this);
}