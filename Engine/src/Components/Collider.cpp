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

glm::vec3 Collider::GlobalTranslationFromGameObject()
{
	return glm::vec3(transform.GetPosition().x * transform.GetScale().x * _parent->transform.GetScale().x,
		transform.GetPosition().y * transform.GetScale().y * _parent->transform.GetScale().y,
		transform.GetPosition().z * transform.GetScale().z * _parent->transform.GetScale().z );
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


