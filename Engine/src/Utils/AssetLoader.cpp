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

Model* AssetLoader::LoadModel(std::string path, bool preserve)
{
	Model* m = assimpWrapper.LoadModel(path);
	containers[typeid(Model).name()].Load(m->name, m);	
	m->preserve = preserve;	

	return m;
}


Texture2D* AssetLoader::LoadTexture(std::string path, bool preserve )
{
	int width;
	int height;
	int channels;
	Asset* t = nullptr;

	unsigned char* data = SOIL_load_image(path.c_str(), &width, &height, &channels, 0);

	if (data)
	{
		 std::string namerr = FileUtils::GetFileNameNoExtensionFromAbsolutePath(path);
		// Logger::LogError("Loaded texture", namerr);

		 t = graphucsAPI->CreateTexture2D(namerr, width, height, channels, data);
		 t->preserve = preserve;
		 containers[typeid(Texture2D).name()].Load(namerr, t);
		
	}
	else
		Logger::LogError("Error while loading", path, "Error", SOIL_last_result());
	Texture2D* tt = dynamic_cast<Texture2D*>(t);
	return tt;
}

Shader* AssetLoader::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, bool preserve )
{
	std::string vertexFileContent = FileUtils::ReadFileToString(vertexPath);
	std::string fragFileContent = FileUtils::ReadFileToString(fragmentPath);

	Shader* s = graphucsAPI->CreateShader(name, vertexFileContent, fragFileContent);
	s->preserve = preserve;
	containers[typeid(Shader).name()].Load(name, s);
	return s;
}

void AssetLoader::ReadHeightmapData(std::string path, unsigned char* &dataOut, int& widthOut, int& heightOut)
{
	if (FileUtils::IsFileThere(path))
		dataOut = SOIL_load_image(path.c_str(), &widthOut, &heightOut, 0, SOIL_LOAD_L);
	else
	{
		Logger::LogError("ERROR: Heightmap not available at", path);
	}
}
