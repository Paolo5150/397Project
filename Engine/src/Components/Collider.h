#pragma once

#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"
#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "..\Physics\CollisionChecks.h"
#include "..\Core\Timer.h"
#include <functional>

class SphereCollider;
class BoxCollider;


class Collider : public Component
{
public:

	friend class RigidBody;

	enum COLLIDER_TYPE
	{
		SPHERE,
		BOX
	};

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
	virtual void Initialize(){};

	void Update() override {
		
		if (Timer::GetTickCount() == 0 || !_parent->GetIsStatic())
		transform.Update(); }

	bool enableRender;

	std::function<void(GameObject*)> collisionCallback;
	COLLIDER_TYPE colliderType;
protected:
	btCollisionShape* collisionShape;
};