#include "Renderer.h"

#include "..\Core\Timer.h"
#include "..\Event\EventDispatcher.h"
#include "..\Core\Camera.h"
#include "..\Graphics\RenderingEngine.h"





Renderer::Renderer(std::string name, Material m) : Component(name) {

	submitted = 0;
	
	isCullable = true;
	SetMaterial(m);
}


void Renderer::Update()
{
	if (_isActive)
	{
		RenderingEngine::Instance().SubmitRenderer(this);
		submitted = true;
	}

}

void Renderer::SendDataToShader(Camera& cam)
{
	glm::mat4 model;

	if (_parent != NULL)
		model = _parent->transform.GetMatrix();

	
	glm::mat4 mvp = model;
	Shader::GetCurrentShader().SetMat4("mvp", mvp);
	if (_parent != NULL)
	Shader::GetCurrentShader().SetVec3("pos", _parent->transform.GetPosition());

	Shader::GetCurrentShader().SetMat4("model", model);
	Shader::GetCurrentShader().SetMat4("view", cam.viewMatrix);
	Shader::GetCurrentShader().SetMat4("projection", cam.projectionMatrix);
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

Material& Renderer::GetMaterial(MaterialType mt)
{
	auto it = allMaterials.find(mt);

	if (it != allMaterials.end())
		return allMaterials[mt];
	else
		return allMaterials[PRIMARY];


}
void Renderer::SetMaterial(Material m, MaterialType mt) {
	allMaterials[mt] = m;
};