#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(bool castShadows) : Light("DirectionalLight",DIRECTIONAL)
{
	transform.SetRotation(90, 0, 0);	
	//shadowMap = NULL;

	//if (castShadows)
	//	shadowMap = new FrameBuffer(640, 640, false);
	//isCastingShadows = castShadows;
}
/*
void DirectionalLight::SetCastShadowEnable(bool enable)
{
	isCastingShadows = enable;

	if (shadowMap == NULL)
		shadowMap = new FrameBuffer(1024 * 4, 1024 * 4, false);
}

bool DirectionalLight::GetIsCastingShadow()
{
	return isCastingShadows;
}
*/
DirectionalLight::~DirectionalLight()
{
	//if (shadowMap != NULL)
	//	delete shadowMap;
}