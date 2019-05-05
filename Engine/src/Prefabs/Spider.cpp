#include "Spider.h"
#include "..\Components\AIBase.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

Spider::Spider() : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);
	
	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	AddComponent(new AIBase("Assets\\Scripts\\AI\\Spider.lua"));
}

Spider::Spider(float posX, float posY, float posZ) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);
	
	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	AddComponent(new AIBase("Assets\\Scripts\\AI\\Spider.lua"));
	transform.SetPosition(posX, posY, posZ);
}

Spider::Spider(Transform& targetTransform) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	AddComponent(new AIBase(targetTransform, "Assets\\Scripts\\AI\\Spider.lua"));
}

Spider::Spider(Transform& targetTransform, float posX, float posY, float posZ) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	AddComponent(new AIBase(targetTransform, "Assets\\Scripts\\AI\\Spider.lua"));
	transform.SetPosition(posX, posY, posZ);
}

Spider::~Spider()
{
}

void Spider::SetTarget(Transform& transform)
{
	GetComponent<AIBase>("AIBase")->SetTarget(transform);
}

Transform* Spider::GetTarget() const
{
	return GetComponent<AIBase>("AIBase")->GetTarget();
}

void Spider::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::ENEMY);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::OBSTACLE);
	sc->transform.SetScale(80, 40, 80);

	sc->transform.SetPosition(0, 35, 0);
	sc->enableRender = 1;
	AddComponent(sc);
}

void Spider::Update()
{
	GameObject::Update(); //call base Update

	float h = Terrain::Instance().GetHeightAt(transform.GetPosition().x, transform.GetPosition().z);
	transform.SetPosition(transform.GetPosition().x, h, transform.GetPosition().z);
}