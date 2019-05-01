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

Model* AssetLoader::LoadModel(std::string path, bool loadTextures,bool preserve)
{
	Model* m = assimpWrapper.LoadModel(path, loadTextures);
	containers[typeid(Model).name()].Load(m->name, m);	
	//Logger::LogError("Loaded model", m->name);
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


CubeMap* AssetLoader::LoadCubeMap(std::string pathToFolder,bool preserve,std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back)
{
	CubeMap* c = nullptr;
	//Push back order matters
	std::vector<std::string> faces;
	faces.push_back(right);
	faces.push_back(left);
	faces.push_back(top);
	faces.push_back(bottom);
	faces.push_back(back);
	faces.push_back(front);


	unsigned char* data[6];
	int width[6];
	int height[6];

	for (unsigned int i = 0; i < 6; i++)
	{
		std::string absolutePathToTexture = pathToFolder + "\\" + faces[i];
		data[i] = SOIL_load_image(absolutePathToTexture.c_str(),&width[i] ,&height[i], 0, 0);
		Logger::LogInfo("Loaded cubemap texture",absolutePathToTexture);

		if (!data[i])
			Logger::LogError("Something went wrong while loading CUBEMAP TEXTURE: {}, {}", faces[i], SOIL_last_result());
	}

	std::string folderName = FileUtils::GetLastFolderNameFromAbsolutePath(pathToFolder + "\\");
	c = graphucsAPI->CreateCubeMap(folderName, data,width,height);
	c->preserve = preserve;
	containers[typeid(CubeMap).name()].Load(folderName, c);

	return c;
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
