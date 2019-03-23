#pragma once

#include "GL\glew.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include <map>
#include "Texture2D.h"
#include "Material.h"
#include "ModelNode.h"

class GameObject;

class Model
{
public:
	friend class AssimpWrapper;
	friend class ModelAnimation;

	Model();
	virtual ~Model();


	std::vector<Mesh> GetMeshes();
	virtual GameObject* CreateGameObject();
	std::string name;

protected:

	ModelNode* rootNode;
	std::map<std::string, ModelNode*> allNodes;
	std::vector<Texture2D*> allTextures;
	std::map<int, Mesh*> allMeshes;
	std::map<int, Material*> allMaterials;
	std::map<int, std::string> meshesNames;
};

