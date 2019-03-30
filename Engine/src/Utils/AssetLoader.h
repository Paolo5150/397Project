#pragma once
#include "..\Graphics\GraphicsAPI.h"
#include <map>
#include <list>
#include "AssetContainer.h"
#include "..\Graphics\Model.h"
#include "AssimpWrapper.h"

class AssetLoader
{
public:
	friend class Core;

	static AssetLoader& Instance();
	static void Initialize(GraphicsAPI* gAPI);
	
	Shader* LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, bool preserve = false);
	Texture2D* LoadTexture(std::string path,bool preserve = false);
	Model* LoadModel(std::string path, bool preserve = false);
	
	template<class T>
	void Unload();

	template <class T>
	T* GetAsset(std::string name);

private:
	static AssetLoader* instance;

	AssetLoader(GraphicsAPI* gAPI);
	~AssetLoader();
	GraphicsAPI* graphucsAPI;
	std::map<std::string, AssetContainer> containers;
	AssimpWrapper assimpWrapper;
	template<class T>
	void UnloadPreserved();


};

template<class T>
void AssetLoader::Unload()
{
	std::string t = typeid(T).name();

	auto it = containers.find(t);
	if (it != containers.end())
	{
		it->second.Unload();
	}
}

template<class T>
void AssetLoader::UnloadPreserved()
{
	std::string t = typeid(T).name();

	auto it = containers.find(t);
	if (it != containers.end())
	{
		it->second.UnloadPreserved();
	}
}

template <class T>
T* AssetLoader::GetAsset(std::string name)
{
	std::string t = typeid(T).name();
	return (T*)containers[t].GetAsset<T>(name);

}

