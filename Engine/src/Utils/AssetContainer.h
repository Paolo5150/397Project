#pragma once
#include <map>
#include <string>

template <class T>
class AssetContainer
{
public:
	AssetContainer();
	~AssetContainer();

	void Load(std::string name,T* asset);

	T* GetAsset(std::string name);

	void Unload();

	std::string GetAssetType();

private:
	std::map<std::string, T*> assets;
};

template <class T>
AssetContainer<T>::AssetContainer()
{

}

template <class T>
AssetContainer<T>::~AssetContainer()
{}

template <class T>
std::string AssetContainer<T>::GetAssetType()
{
	return typeid(T).name();
}

template <class T>
void AssetContainer<T>::Load(std::string name, T* asset)
{
	assets[name] = asset;
}

template <class T>
T* AssetContainer<T>::GetAsset(std::string name)
{
	auto it = assets.find(name);

	if (it != assets.end())
		return it->second;
	else
		return nullptr;
}

template <class T>
void AssetContainer<T>::Unload()
{
	auto it = assets.begin();

	for (; it != assets.end(); it++)
	{
		delete it->second;
	}


}