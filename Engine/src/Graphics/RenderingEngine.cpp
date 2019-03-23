
#include "RenderingEngine.h"
#include "..\Core\Core.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\ApplicationEvents.h"
#include "..\Components\Renderer.h"
#include "..\Core\Camera.h"

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


void RenderingEngine::RenderCurrentScene(Camera* camera, MaterialType mt)
{
	if (!camera->GetActive()) return;


	//Render skybox

	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	RenderVector(*camera, allRenderers, mt);

	Core::Instance().GetGraphicsAPI().ResetTextures();




}

void RenderingEngine::RenderVector(Camera& cam, std::vector<Renderer*>& r, Material* forcedMaterial)
{
	for (int i = 0; i < r.size(); i++)
	{
		if (cam.GetCullingMask() & r[i]->_parent->GetLayer()) //Check for culling mask
		{
			forcedMaterial->BindMaterial();
			//LightManager::Instance().UpdateShader(r[i]->GetMaterial().GetShader());
			r[i]->_parent->OnPreRender(cam,&r[i]->GetMaterial().GetShader());
			r[i]->Render(cam);
			forcedMaterial->UnbindMaterial();
		}
	}
}



void RenderingEngine::RenderCurrentScene(Camera* camera, Material* simplifiedMaterial)
{
	/*if (!camera->isActive) return;

	glClear(GL_DEPTH_BUFFER_BIT);

	RenderVector(*camera, allRenderers, simplifiedMaterial);

	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Render transparent	



	std::sort(allTransparentRenderer.begin(), allTransparentRenderer.end(), [&](Renderer* lhs, Renderer* rhs)
	{

		float leftDistance = glm::length(lhs->GetEntity()->transform.position - camera->GetEntity()->transform.position);
		float rightDistance = glm::length(rhs->GetEntity()->transform.position - camera->GetEntity()->transform.position);

		return lhs > rhs;

	});
	RenderVector(*camera, allTransparentRenderer);


	glDisable(GL_BLEND);
	//Reset active textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

}

void RenderingEngine::RenderBuffer(MaterialType mt)
{
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

	//Render opaque
	for (int camIndex = 0; camIndex < Camera::GetAllCameras().size(); camIndex++)
	{
		if (!Camera::GetAllCameras()[camIndex]->GetActive()) continue;
		//Render skybox here when ready
	

		Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

		RenderVector(*Camera::GetAllCameras()[camIndex], allRenderers,mt);

	}


	Core::Instance().GetGraphicsAPI().ResetTextures();
}




void RenderingEngine::RenderVector(Camera& cam, std::vector<Renderer*>& r, MaterialType m)
{

	for (int i = 0; i < r.size(); i++)
	{
		if (cam.GetCullingMask() & r[i]->_parent->GetLayer()) //Check for culling mask
		{
			//V2Core::LightManager::Instance().UpdateShader(r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).BindMaterial();
			r[i]->OnPreRender(cam,&r[i]->GetMaterial(m).GetShader()); //Change to get root->OnPrerender
			r[i]->Render(cam);
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

