#pragma once
#include <map>
#include <string>
#include "Asset.h"

class AssetContainer
{
public:
	
	AssetContainer(){};
	~AssetContainer(){};


	void Load(std::string name,Asset* asset);

	template<class T>
	T* GetAsset(std::string name);

	void Unload();
	void UnloadPreserved();

	std::string GetAssetType();

private:
	std::map<std::string, Asset*> assets;
};





template <class T>
T* AssetContainer::GetAsset(std::string name)
{
	auto it = assets.find(name);

	if (it != assets.end())
		return (T*)it->second;
	else
		return nullptr;
}


