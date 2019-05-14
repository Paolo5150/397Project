
#include "RenderingEngine.h"
#include "..\Core\Core.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\ApplicationEvents.h"
#include "..\Components\Renderer.h"
#include "..\Core\Camera.h"
#include "..\Lighting\LightingManager.h"
#include "FrameBuffer.h"
#include "..\Utils\AssetLoader.h"
#include "..\GUI\GUIElements\GUIManager.h"

#include <algorithm>
std::vector<Renderer*> RenderingEngine::allRenderers;
bool RenderingEngine::godRays;

RenderingEngine& RenderingEngine::Instance()
{
	static RenderingEngine instance;
	return instance;
}

RenderingEngine::RenderingEngine()
{
	godRays = false;
}


RenderingEngine::~RenderingEngine()
{
	delete renderTexture;
	delete godraysTexture;
	delete occludedTexture;
}

void RenderingEngine::Initialize()
{
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e){

		ClearRendererList();
		return 0;
	});

	EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>([this](Event* e){

		WindowResizeEvent* wc = dynamic_cast<WindowResizeEvent*>(e);

		renderTexture->ResizeTexture(wc->width, wc->height);
		renderTexture->ResizeTexture(wc->width, wc->height);

		occludedTexture->ResizeTexture(wc->width, wc->height);
		occludedTexture->ResizeTexture(wc->width, wc->height);
		return 0;
	});

	int w, h;
	Window::Instance().GetWindowSize(w, h);
	renderTexture = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w, h);	
	occludedTexture = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w, h);
	godraysTexture = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w, h);

	godRayShader = AssetLoader::Instance().GetAsset<Shader>("GodRays");
	postProcessShader = AssetLoader::Instance().GetAsset<Shader>("PostProcess");

	Vertex v1(-1.0, -1.0, 0.0);
	v1.UV = glm::vec2(0, 0);

	Vertex v2(1.0, -1.0, 0.0);
	v2.UV = glm::vec2(1, 0);

	Vertex v3(1.0, 1.0, 0.0);
	v3.UV = glm::vec2(1, 1);

	Vertex v4(-1.0, 1.0, 0.0);
	v4.UV = glm::vec2(0, 1);

	std::vector<Vertex> vertices;
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	std::vector<unsigned> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	quadMesh = new Mesh(vertices, indices);

}

void RenderingEngine::RenderBufferToTexture(MaterialType mt )
{

	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

	int previousDepth = 0;
	if (godRays)
	{

		occludedTexture->Bind();

		Core::Instance().GetGraphicsAPI().ClearColorBuffer();
		Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

		//Render opaque
		for (int camIndex = 0; camIndex < Camera::GetAllCameras().size(); camIndex++)
		{
			Camera& cam = *Camera::GetAllCameras()[camIndex];

			if (!cam.GetActive()) continue;

			if (previousDepth != cam.GetDepth())
				Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

			RenderBufferOverrideColor(&cam, glm::vec3(0, 0, 0), MaterialType::COLORONLY);
			previousDepth = cam.GetDepth();

		}
		Core::Instance().GetGraphicsAPI().ResetTextures();
		
		occludedTexture->Unbind();

		godraysTexture->Bind();		
		Core::Instance().GetGraphicsAPI().ClearColorBuffer();
		Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
		glActiveTexture(GL_TEXTURE0);
		occludedTexture->GetColorTexture()->Bind();

		godRayShader->Bind();
		quadMesh->Render();
		godraysTexture->Unbind();

	}

	

	renderTexture->Bind();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

	previousDepth = 0;
	//Render opaque
	for (int camIndex = 0; camIndex < Camera::GetAllCameras().size(); camIndex++)
	{
		Camera& cam = *Camera::GetAllCameras()[camIndex];

		if (!cam.GetActive()) continue;

		if (previousDepth != cam.GetDepth())
			Core::Instance().GetGraphicsAPI().ClearDepthBuffer();

		RenderVector(cam, allRenderers, mt);
		previousDepth = cam.GetDepth();

	}
	Core::Instance().GetGraphicsAPI().ResetTextures();
	renderTexture->Unbind();

	postProcessShader->Bind();
	static float timer = 0;
	timer += Timer::GetDeltaS();
	postProcessShader->SetFloat("timer", timer);
	if (Camera::GetCameraByName("Main Camera") != nullptr)
	postProcessShader->SetInt("underwater", Camera::GetCameraByName("Main Camera")->transform.GetGlobalPosition().y < 750 ? 1 : 0);


	glActiveTexture(GL_TEXTURE0);
	renderTexture->GetColorTexture()->Bind();
	postProcessShader->SetInt("diffuse0", 0);

	glActiveTexture(GL_TEXTURE1);
	postProcessShader->SetInt("special0", 1);
	distortionTexture->Bind();

	if (godRays)
	{
	glActiveTexture(GL_TEXTURE2);
	postProcessShader->SetInt("godrays", 2);

	Camera* cam = Camera::GetCameraByName("Main Camera");
	float dot = 0;;
	if (cam != nullptr)
		dot =  max(0.0, glm::dot(-cam->transform.GetLocalFront(), glm::vec3(0.630037, -0.707107, -0.32102)));

	postProcessShader->SetFloat("camLightDot", dot);

	godraysTexture->GetColorTexture()->Bind();
	}
	quadMesh->Render();

	glActiveTexture(GL_TEXTURE0);
	Core::Instance().GetGraphicsAPI().ResetTextures();


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
			
			r[i]->GetMaterial(m).BindMaterial();		

			r[i]->OnPreRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->Render(cam);
			r[i]->OnPostRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).UnbindMaterial();
			r[i]->submitted = 0;
		}
	}
}

void RenderingEngine::RenderVectorOverrideColor(Camera& cam, std::vector<Renderer*>& r, glm::vec3 color, MaterialType m)
{

	for (int i = 0; i < r.size(); i++)
	{
		if (cam.GetCullingMask() & r[i]->_parent->GetLayer()) //Check for culling mask
		{
			
			r[i]->GetMaterial(m).BindMaterial();
			r[i]->GetMaterial(m).SetColor(color.x, color.y, color.z);
			r[i]->GetMaterial(m).GetShader().SetVec3("AmbientLight", LightManager::Instance().GetAmbientLight());
			r[i]->OnPreRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->Render(cam);
			r[i]->OnPostRender(cam, &r[i]->GetMaterial(m).GetShader());
			r[i]->GetMaterial(m).UnbindMaterial();
			r[i]->submitted = 0;

		}
	}
}

void RenderingEngine::ClearRendererList()
{
	allRenderers.clear();

}

