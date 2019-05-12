#include "MainCamera.h"
#include "Timer.h"
#include "..\Prefabs\Terrain.h"



MainCamera::MainCamera() : CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 100000.0f)
{
	this->SetName("Main Camera");
	RemoveLayerMask(Layers::GUI);
	
}


