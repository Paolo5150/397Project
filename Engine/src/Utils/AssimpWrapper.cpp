#include "..\pch.h"
#include "AssimpWrapper.h"
#include "AssetLoader.h"
#include "FileUtils.h"

static std::string fileNameOnly;
static std::string modelFolderName;
static std::string pathToFolder;

Shader* defaultShader;

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

	defaultShader = AssetLoader::Instance().GetAsset<Shader>("ModelShader");

	modelFolderName = FileUtils::GetLastFolderNameFromAbsolutePath(path);
	Logger::LogWarning("Model folder", modelFolderName);

	//Model* model = new Model();	

	//processNode(scene->mRootNode, scene, NULL, model, false);
	//model->name = modelFolderName;

	import.FreeScene();

	//if (model != NULL)
	//	return model;
}