#include "AssetContainer.h"

void AssetContainer::Unload()
{
	auto it = assets.begin();

	for (; it != assets.end(); it++)
	{
		delete it->second;
	}


}

void AssetContainer::Load(std::string name, Asset* asset)
{
	assets[name] = asset;
}