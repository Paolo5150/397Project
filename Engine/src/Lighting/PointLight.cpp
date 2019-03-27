#include "PointLight.h"
#include "..\Components\MeshRenderer.h"
#include "..\Utils\AssetLoader.h"
#include "..\Graphics\Material.h"

PointLight::PointLight() : Light("PointLight",POINT)
{

	intensity = 20.0f;
	lightType = POINT;

	Model* m = AssetLoader::Instance().GetAsset<Model>("Sphere");

	GameObject* sphere = m->CreateGameObject();

	Material mat;
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	mat.SetColor(diffuseColor.x, diffuseColor.y, diffuseColor.z);

	sphere->ApplyMaterial(mat);
	sphere->ApplyMaterial(mat,NOLIGHT);
	sphere->ApplyMaterial(mat,COLORONLY);
	AddChild(sphere);

}
PointLight::~PointLight()
{

}

void PointLight::Update()
{
	GameObject::Update();


}