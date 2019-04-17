#pragma once
#include "Collision.h"

SphereCollider::SphereCollider() : Collider("SphereCollider"){
	trans.parent = &_parent->transform;
	Mesh* m = new Mesh(AssetLoader::Instance().GetAsset<Model>("sphere_low")->GetMeshes()[0]);
	mr = new MeshRenderer(m, mat);
};

bool SphereCollider::checkCollision(SphereCollider other){
	double Xsquared = trans.GetPosition().x - other.trans.GetPosition().x;
	Xsquared *= Xsquared;

	double Ysquared = trans.GetPosition().y - other.trans.GetPosition().y;
	Ysquared *= Ysquared;

	double Zsquared = trans.GetPosition().z - other.trans.GetPosition().z;
	Zsquared *= Zsquared;

	double sumRadii = (trans.GetScale().x) + (other.trans.GetScale().x);
	sumRadii *= sumRadii;

	if (Xsquared + Ysquared + Zsquared <= sumRadii)
		return true;
	return false;

}