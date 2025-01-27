#include "Collider.h"
#include "..\Physics\PhysicsWorld.h"


Collider::Collider(std::string name) : transform(Transform(GetParent())), Component(name){
	_type = "Collider";
	enableRender = 0;
	collisionLayer = CollisionLayers::DEFAULT;
	collideAgainstLayer = CollisionLayers::DEFAULT;

}


void Collider::EngineUpdate()
{
	if ( _isActive)
	{
		if (!_parent->GetIsStatic())
			PhysicsWorld::Instance().AddCollider(this);
		
		if (enableRender)
			meshRenderer->EngineUpdate();

	}


}



void Collider::OnAttach(GameObject* go)
{
	transform.parent = &go->transform;
	transform.Update();
	InitializeMeshRenderer();
	meshRenderer->transform = &transform;
	meshRenderer->SetParent(go);

	collisionCallback = std::bind(&GameObject::OnCollision, go, std::placeholders::_1);
	meshRenderer->AddPreRenderCallback([](Camera& cam, Shader* s){		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);	
	});


	meshRenderer->AddPostRenderCallback([](Camera& cam, Shader* s){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	});

	Initialize();
	PhysicsWorld::Instance().AddCollider(this);
	
}


