#pragma once

#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"
#include "..\Physics\PhysicsWorld.h"

class Collider : public Component
{
public:
	Collider(std::string name) : Component(name){ 
		
		enableRender = 1; }
	virtual ~Collider(){ delete meshRenderer; };

	Transform transform;
	virtual void OnAttach(GameObject* go) override ;
	MeshRenderer* meshRenderer;

	void EngineUpdate() override;
	virtual void InitializeMeshRenderer(){};

	bool enableRender;

protected:
	btCollisionShape* collisionShape;
};