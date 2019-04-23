#pragma once

#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"
#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
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

	void Update() override {
		transform.Update(); }

	bool enableRender;

	virtual bool IsColliding(BoxCollider* other){ return 0; };
	virtual bool IsColliding(SphereCollider* other){ return 0; };


	std::function<void(GameObject*)> collisionCallback;
	COLLIDER_TYPE colliderType;
protected:
	btCollisionShape* collisionShape;
};