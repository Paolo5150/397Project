
#include "RenderingEngine.h"
#include "..\Core\Core.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\ApplicationEvents.h"
#include "..\Components\Renderer.h"
#include "..\Core\Camera.h"
#include "..\Lighting\LightingManager.h"

#include <algorithm>
std::vector<Renderer*> RenderingEngine::allRenderers;


RenderingEngine& RenderingEngine::Instance()
{
	static RenderingEngine instance;
	return instance;
}

RenderingEngine::RenderingEngine()
{
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e){		
		ClearRendererList();
		return 0;
	});
}


RenderingEngine::~RenderingEngine()
{

}

void RenderingEngine::Initialize()
{

}


void RenderingEngine::SubmitRenderer(Renderer* rend)
{
	if (!rend->submitted)
	{
			
		allRenderers.push_back(rend);

		rend->submitted = true;
	}
}



void RenderingEngine::RenderBuffer(Camera* cam,MaterialType mt)
{
	RenderVector(*cam, allRenderers, mt);
	
	Core::Instance().GetGraphicsAPI().ResetTextures();
}

void RenderingEngine::RenderBuffer(MaterialType mt)
{
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

	//Logger::LogInfo("Render buffer of",allRenderers.size());


	int previousDepth = 0;
	//Render opaque
	for (int camIndex = 0; camIndex < Camera::GetAllCameras().size(); camIndex++)
	{
		Camera& cam = *Camera::GetAllCameras()[camIndex];

		if (!cam.GetActive()) continue;
	
		if (previousDepth != cam.GetDepth())
		Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

		RenderVector(cam, allRenderers,mt);
		previousDepth = cam.GetDepth();

	}
	Core::Instance().GetGraphicsAPI().ResetTextures();
}

void RenderingEngine::RenderBufferOverrideColor(Camera* camera, glm::vec3 color, MaterialType mt )
{
	RenderVectorOverrideColor(*camera, allRenderers, color, mt);

	Core::Instance().GetGraphicsAPI().ResetTextures();
}


void RenderingEngine::RenderVector(Camera& cam, std::vector<Renderer*>& r, MaterialType m)
{

	for (int i = 0; i < r.size(); i++)
	{
		if (cam.GetCullingMask() & r[i]->_parent->GetLayer()) //Check for culling mask
		{			
			//Logger::LogWarning("Rendering", r[i]->GetParent()->GetName());
			LightManager::Instance().UpdateShader(r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).BindMaterial();
			Logger::LogWarning("Prerender", r[i]->GetParent()->GetName());

			r[i]->_parent->GetRoot()->OnPreRender(cam,&r[i]->GetMaterial(m).GetShader()); 
			r[i]->Render(cam);
			r[i]->_parent->GetRoot()->OnPostRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).UnbindMaterial();
		}
	}
}

void RenderingEngine::RenderVectorOverrideColor(Camera& cam, std::vector<Renderer*>& r, glm::vec3 color, MaterialType m)
{

	for (int i = 0; i < r.size(); i++)
	{
		if (cam.GetCullingMask() & r[i]->_parent->GetLayer()) //Check for culling mask
		{
			LightManager::Instance().UpdateShader(r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).BindMaterial();
			r[i]->GetMaterial(m).SetColor(color.x, color.y, color.z);
			r[i]->_parent->GetRoot()->OnPreRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->Render(cam);
			r[i]->_parent->GetRoot()->OnPostRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).UnbindMaterial();
		}
	}
}

void RenderingEngine::ClearRendererList()
{
	for (int i = 0; i < allRenderers.size(); i++)
		allRenderers[i]->submitted = 0;

	allRenderers.clear();

}

