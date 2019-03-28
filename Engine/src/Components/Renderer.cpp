#include "Renderer.h"

#include "..\Core\Timer.h"
#include "..\Event\EventDispatcher.h"
#include "..\Core\Camera.h"
#include "..\Event\ApplicationEvents.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Utils\AssetLoader.h"




Renderer::Renderer(std::string name, Material m) : Component(name) {

	submitted = 0;
	_type = "Renderer";
	isCullable = true;
	SetMaterial(m);
	
	

}

Renderer::Renderer(std::string name) : Component(name) {

	submitted = 0;
	_type = "Renderer";
	isCullable = true;




}

void Renderer::CreateOtherMaterials(Material& defaultMat)
{
	//Create a ColorOnly material for all renderers
	Material co;
	co.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));

	float r, g, b;
	defaultMat.GetColor(r, g, b);
	co.SetColor(r, g, b);
	SetMaterial(co, COLORONLY);

	//Create a NoLight material for all renderers, copy from default one (textures and color)

	Material nolight(defaultMat); //Copy from default
	nolight.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNoLight"));
	nolight.SetColor(r, g, b);
	SetMaterial(nolight, NOLIGHT);
}

void Renderer::EngineUpdate()
{
	if (_isActive)
	{
		RenderingEngine::Instance().SubmitRenderer(this);
		submitted = true;
	}

}

void Renderer::Update()
{
	
}

void Renderer::OnPreRender(Camera& cam, Shader* currentShader )
{
	
	glm::mat4 mvp = cam.projectionMatrix * cam.viewMatrix * _parent->transform.GetMatrix();
	Shader::GetCurrentShader().SetMat4("u_mvp", mvp);
	Shader::GetCurrentShader().SetMat4("u_model", _parent->transform.GetMatrix());
	Shader::GetCurrentShader().SetMat4("u_view", cam.viewMatrix);
	Shader::GetCurrentShader().SetMat4("u_projection", cam.projectionMatrix);
	//Shader::GetCurrentShader().SetFloat("heightPlane", Water::heightPlane);
	//Shader::GetCurrentShader().SetInt("heightPlaneActive", Water::heightPlaneActive);
	//Shader::GetCurrentShader().SetVec3("fogColor", LightManager::Instance().fogColor);
	//Shader::GetCurrentShader().SetInt("fogEnabled", LightManager::Instance().GetFogEnable());


	/*static double shaderTimer = 0;
	static double lastValue;
	shaderTimer = Timer::GetTimeS() / 4.0f;
	if (shaderTimer != 0)
	lastValue = shaderTimer;
	Shader::GetCurrentShader().SetFloat("timeSeconds", lastValue);


	Shader::GetCurrentShader().SetFloat("nearPlane", cam.nearPlane);
	Shader::GetCurrentShader().SetFloat("farPlane", cam.farPlane);

	if (_parent != NULL)
	Shader::GetCurrentShader().SetVec3("camPosition", cam.transform.GetPosition());*/
}


void Renderer::SendDataToShader(Camera& cam)
{
	

}

Material& Renderer::GetMaterial(MaterialType mt)
{
	auto it = allMaterials.find(mt);

	if (it != allMaterials.end())
		return allMaterials[mt];
	else
		return allMaterials[DEFAULT];


}
void Renderer::SetMaterial(Material m, MaterialType mt) {
	allMaterials[mt] = m;

	if (mt == MaterialType::DEFAULT)
		CreateOtherMaterials(m);

};