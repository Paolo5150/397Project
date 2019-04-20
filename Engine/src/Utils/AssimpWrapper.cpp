#include "..\pch.h"
#include "AssimpWrapper.h"
#include "AssetLoader.h"
#include "FileUtils.h"
#include "Maths.h"

static std::string fileNameOnly;
static std::string modelFolderName;
static std::string pathToFolder;

Model* AssimpWrapper::LoadModel(const std::string& path)
{
	Assimp::Importer import;

	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_FixInfacingNormals |
		aiProcess_ForceGenNormals | aiProcessPreset_TargetRealtime_Quality);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::LogError("Assimp error: {}", import.GetErrorString());
		return NULL;
	}
	
	modelFolderName = FileUtils::GetLastFolderNameFromAbsolutePath(path);

	pathToFolder = "Assets\\Models\\" + modelFolderName ;
	Model* model = new Model();	

	ProcessNode(scene->mRootNode, scene, NULL, model, false);
	model->name = modelFolderName;

	import.FreeScene();

	if (model != NULL)
		return model;
}

void AssimpWrapper::ProcessNode(aiNode* node, const aiScene* scene, ModelNode* parentNode, Model* model, bool isAnimated)
{
	ModelNode* n = new ModelNode();
	n->name = node->mName.C_Str();
	n->transform = Maths::aiMatrix4x4ToGlm(node->mTransformation);
//	model->allNodes[n->name] = n;

	//if (model->rootNode == NULL)
	//	model->rootNode = n;

	if (parentNode != NULL)
		parentNode->children.push_back(n);

	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];
		//V2_WARNING("Processing mesh {}", ai_mesh->mName.C_Str());
		ProcessMesh(ai_mesh, scene, model, isAnimated);

	}

	for (int i = 0; i < node->mNumChildren; i++)
		ProcessNode(node->mChildren[i], scene, n, model, isAnimated);

}

void AssimpWrapper::ProcessMesh(aiMesh* mesh, const aiScene* scene, Model* model, bool isAnimated)
{
	LoadMesh(mesh, model, isAnimated);

	//Logger::LogInfo("Processing mesh {}", mesh->mName.C_Str());
	Material associatedMaterial ;
	//material
	if (mesh->mMaterialIndex >= 0 && scene->mNumMaterials != 0)
	{
		//all pointers created in assimp will be deleted automaticaly when we call import.FreeScene();
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::string textureFolder = pathToFolder + "\\Textures";
		associatedMaterial = Material(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));

		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			//Logger::LogInfo("This mesh has {} diffuse", material->GetTextureCount(aiTextureType_DIFFUSE));
			LoadTextureIntoMaterial(aiTextureType_DIFFUSE, material, &associatedMaterial, textureFolder, model);
		}

		if (material->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			//Logger::LogInfo("This mesh has {} normal", material->GetTextureCount(aiTextureType_NORMALS));
			LoadTextureIntoMaterial(aiTextureType_NORMALS, material, &associatedMaterial, textureFolder, model);
		}

		if (material->GetTextureCount(aiTextureType_EMISSIVE) > 0)
		{
			//Logger::LogInfo("This mesh has {} normal", material->GetTextureCount(aiTextureType_NORMALS));
			LoadTextureIntoMaterial(aiTextureType_EMISSIVE, material, &associatedMaterial, textureFolder, model);
		}

		//Load material color
		aiColor4D diffuse;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		{
			associatedMaterial.LoadVec3("color", diffuse.r, diffuse.g, diffuse.b);
		}
		else
			associatedMaterial.LoadVec3("color", 1,1,1);

	}
	else
	{
		//Logger::LogInfo("No material, applying default one {}", mesh->mMaterialIndex);
		associatedMaterial = Material(AssetLoader::Instance().GetAsset<Shader>("ColorOnly")); 
		associatedMaterial.LoadVec3("color", 1,0,1);

	}


	//if (scene->HasAnimations())
	//	associatedMaterial.SetShader(defaultShader);

	int index = model->allMaterials.size();

	model->allMaterials[index] = associatedMaterial;

}

void AssimpWrapper::LoadMesh(aiMesh* mesh, Model* model, bool isanimated)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture2D> textures;
	//std::vector<VertexBoneData> bones_id_weights_for_each_vertex;

	vertices.reserve(mesh->mNumVertices);
	indices.reserve(mesh->mNumVertices);

//	bones_id_weights_for_each_vertex.resize(mesh->mNumVertices);

	//vertices
	for (unsigned i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 v;
		v.x = mesh->mVertices[i].x;
		v.y = mesh->mVertices[i].y;
		v.z = mesh->mVertices[i].z;
		vertex.position = v;

		if (mesh->mNormals != NULL)
		{
			v.x = mesh->mNormals[i].x;
			v.y = mesh->mNormals[i].y;
			v.z = mesh->mNormals[i].z;
			vertex.normal = v;
		}
		else
		{
			vertex.normal = glm::vec3();
		}


		// in assimp model can have 8 different texture coordinates
		// we only care about the first set of texture coordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.UV = vec;
		}
		else
		{
			vertex.UV = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	//indices
	for (unsigned i = 0; i < mesh->mNumFaces; i++)
	{

		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);

	}

	//if (isAnimated)
	//	LoadBones(mesh, dynamic_cast<AnimatedModel*>(model), bones_id_weights_for_each_vertex);


	int index = model->allMeshes.size();

	model->allMeshes[index].vertices = vertices;
	model->allMeshes[index].indices = indices;
	model->allMeshes[index].CalculateNormals();
	model->allMeshes[index].InitializeVertexArray();

	model->meshesNames[index] = mesh->mName.C_Str();
}

void AssimpWrapper::LoadTextureIntoMaterial(aiTextureType type, aiMaterial* material, Material* mymaterial, std::string textureFolder, Model* model)
{
	TextureUniform myUniform;
	std::string typeInString;

	switch (type)
	{
	case aiTextureType_DIFFUSE:
		myUniform = TextureUniform::DIFFUSE0;
		typeInString = "Diffuse";
		break;
	case aiTextureType_NORMALS:
		myUniform = TextureUniform::NORMAL0;
		typeInString = "Normal";

		break;
	case aiTextureType_EMISSIVE:
		myUniform = TextureUniform::EMISSIVE0;
		typeInString = "Emissive";

		break;
	case aiTextureType_SPECULAR:
		myUniform = TextureUniform::SPECULAR0;
		typeInString = "Specular";

		break;
	}

	for (int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString assimpPath;
		material->GetTexture(type, i, &assimpPath);
		std::string fileNameOnly = FileUtils::GetFileNameFromAbsolutePath(assimpPath.C_Str());
		std::string finalPath = textureFolder + "\\" + fileNameOnly;
		//Logger::LogWarning("Trying to get texture from", finalPath);
		Texture2D* t = AssetLoader::Instance().LoadTexture(finalPath);
		model->allTextures.push_back(t);


		mymaterial->Loadtexture(t, static_cast<TextureUniform>(static_cast<int>(myUniform)+i));
		//Logger::LogInfo("Loaded {} {}, counter {}", typeInString, assimpPath.C_Str(), i);

	}
}

