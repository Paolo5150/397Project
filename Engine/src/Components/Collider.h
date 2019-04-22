#pragma once

#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"
#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"


class Collider : public Component
{
public:

	friend class RigidBody;

	Collider(std::string name) : Component(name){ 
		_type = "Collider";
		enableRender = 1; }
	virtual ~Collider(){ delete meshRenderer; };

	Transform transform;
	virtual void OnAttach(GameObject* go) override ;
	MeshRenderer* meshRenderer;

	void EngineUpdate() override;
	virtual void InitializeMeshRenderer(){};
	glm::vec3 GlobalTranslationFromGameObject();
	void Update() override {
		transform.Update(); }

	bool enableRender;

protected:
	btCollisionShape* collisionShape;
};