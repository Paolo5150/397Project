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
	Texture2D* LoadTexture(std::string name, std::string path);
	
	void Unload();

	template <class T>
	T* GetAsset(std::string name);

private:
	static AssetLoader* instance;

	AssetLoader(GraphicsAPI* gAPI);
	~AssetLoader();
	GraphicsAPI* graphucsAPI;
	std::map<std::string, AssetContainer> containers;



};

template <class T>
T* AssetLoader::GetAsset(std::string name)
{
	std::string t = typeid(T).name();

	return (T*)containers[t].GetAsset<T>(name);
	/*if (typeid(T).name() == allShaders.GetAssetType())
		return (T*)allShaders.GetAsset(name);
	else 	if (typeid(T).name() == allTextures.GetAssetType())
		return (T*)allTextures.GetAsset(name);*/
}

