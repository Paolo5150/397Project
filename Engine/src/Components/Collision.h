#pragma once
#include "../GameObject/Component.h"
#include "../Core/Transform.h"
#include "MeshRenderer.h"
#include "../GameObject/GameObject.h"
#include "../Utils/AssetLoader.h"

class Collider : public Component
{
	public:
		Collider(std::string name) : Component(name){}
		Transform trans;
		MeshRenderer* mr;
		Material mat;
};

class SphereCollider : public Collider
{
	public:
		SphereCollider();
		void EngineUpdate() override;
		bool checkCollision(SphereCollider);
		void OnAttach(GameObject* go) override;


};