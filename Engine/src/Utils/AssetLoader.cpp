#include "AssetLoader.h"
#include "FileUtils.h"

AssetLoader* AssetLoader::instance;

AssetLoader::AssetLoader(GraphicsAPI* gAPI)
{
	graphucsAPI = gAPI;
}
AssetLoader::~AssetLoader()
{
	delete graphucsAPI;
}

AssetLoader& AssetLoader::Instance()
{
	return *instance;
}

void AssetLoader::Initialize(GraphicsAPI* gAPI)
{
	if (instance == nullptr)
		instance = new AssetLoader(gAPI);
}

Shader* AssetLoader::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath)
{
	std::string vertexFileContent = FileUtils::ReadFileToString(vertexPath);
	std::string fragFileContent = FileUtils::ReadFileToString(fragmentPath);

	Shader* s = graphucsAPI->CreateShader(name, vertexFileContent, fragFileContent);
	allShaders.Load(name, s);
	return s;
}