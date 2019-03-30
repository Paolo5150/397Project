#include "AssetContainer.h"

void AssetContainer::Unload()
{
	auto it = assets.begin();

	for (; it != assets.end();)
	{
		if (!it->second->preserve)
		{
			delete it->second;
			it = assets.erase(it);

		}
		else
			it++;
	}


}

void AssetContainer::Load(std::string name, Asset* asset)
{
	assets[name] = asset;
}

void AssetContainer::UnloadPreserved()
{
	auto it = assets.begin();

	for (; it != assets.end(); it++)
	{
		if (it->second->preserve)
			delete it->second;
	}
}
