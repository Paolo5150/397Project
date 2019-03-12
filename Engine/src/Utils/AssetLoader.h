#pragma once
#include "..\Graphics\GraphicsAPI.h"
#include <map>
#include <list>
#include "AssetContainer.h"

class AssetLoader
{
public:
	static AssetLoader& Instance();
	static void Initialize(GraphicsAPI* gAPI);
	
	Shader* LoadShader(std::string name, std::string vertexPath, std::string fragmentPath);

	template <class T>
	void Unload();

	template <class T>
	T* GetAsset(std::string name);
private:
	static AssetLoader* instance;

	AssetLoader(GraphicsAPI* gAPI);
	~AssetLoader();
	GraphicsAPI* graphucsAPI;
	AssetContainer<Shader> allShaders;

};

template <class T>
T* AssetLoader::GetAsset(std::string name)
{
	if (typeid(T).name() == allShaders.GetAssetType())
		return allShaders.GetAsset(name);
}

template <class T>
void AssetLoader::Unload()
{
	if (typeid(T).name() == allShaders.GetAssetType())
		allShaders.Unload();
}

