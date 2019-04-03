#include "DirectionalLight.h"
#include "..\Core\Core.h"

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
		shadowMap = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(1024 * 4, 1024 * 4, false);
}

bool DirectionalLight::GetIsCastingShadow()
{
	return isCastingShadows;
}

DirectionalLight::~DirectionalLight()
{
	if (shadowMap != NULL)
		delete shadowMap;
}