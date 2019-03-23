#include "AssetLoader.h"
#include "FileUtils.h"
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_aug.h"
#include "..\Graphics\Texture2D.h"
#include "..\Graphics\Shader.h"

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

Model* AssetLoader::LoadModel(std::string name, std::string path)
{

}


Texture2D* AssetLoader::LoadTexture(std::string name, std::string path)
{
	int width;
	int height;
	int channels;
	Asset* t = nullptr;

	unsigned char* data = SOIL_load_image(path.c_str(), &width, &height, &channels, 0);

	if (data)
	{
		 t = graphucsAPI->CreateTexture2D(name, width, height, channels, data);
		 containers[typeid(Texture2D).name()].Load(name, t);
		
	}
	else
		Logger::LogError("Error while loading", path, "Error", SOIL_last_result());
	Texture2D* tt = dynamic_cast<Texture2D*>(t);
	return tt;
}

Shader* AssetLoader::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath)
{
	std::string vertexFileContent = FileUtils::ReadFileToString(vertexPath);
	std::string fragFileContent = FileUtils::ReadFileToString(fragmentPath);

	Shader* s = graphucsAPI->CreateShader(name, vertexFileContent, fragFileContent);
	containers[typeid(Shader).name()].Load(name, s);
	return s;
}