#pragma once

#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"
#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "..\Physics\CollisionChecks.h"
#include "..\Core\Timer.h"
#include "..\Physics\CollisionLayer.h"
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
		enableRender = 1;
		collisionLayer = CollisionLayers::DEFAULT;
		collideAgainstLayer = CollisionLayers::DEFAULT;

	}
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

	void AddCollisionLayer(unsigned int layer) { collisionLayer |= layer; }
	void ResetCollisionLayer() { collisionLayer = 0; }
	void RemoveCollisionLayer(unsigned layer) { collisionLayer = collisionLayer & (~layer); }
	unsigned GetCollisionLayer() { return collisionLayer; }

	void AddCollideAgainstLayer(unsigned layer) { collideAgainstLayer |= layer; }
	void ResetCollideAgainstLayer() { collideAgainstLayer = 0; }
	void RemoveCollideAgainstLayer(unsigned layer) { collideAgainstLayer = collideAgainstLayer & (~layer); }
	unsigned GetCollideAgainstLayer() { return collideAgainstLayer; }

protected:
	btCollisionShape* collisionShape;
	int collisionLayer;
	int collideAgainstLayer;
};