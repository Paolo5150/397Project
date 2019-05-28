#pragma once
#include <map>
#include <string>
#include "Asset.h"

/**
* @class AssetContainer
* @brief Container class for Asset objects
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2019
*
* @bug No known bugs.
*/
class AssetContainer
{
public:
	/**
	* @brief		Creates a container for external assets
	*
	* @post			The container object is created
	*/
	AssetContainer(){};

	/**
	* @brief		Destroy the container
	* @pre			The container exists
	* @post			The container object is created
	*/
	~AssetContainer(){};

	/**
	* @brief		Load an asset into the container
	* @pre			The container exists, the asset is no null
	* @post			The asset is loaded into the container
	*/
	void Load(std::string name,Asset* asset);

	/**
	* @brief		Get asset of specific type
	* @pre			The container exists, the asset is in the container
	* @post			The asset is returned
	* @param name	The asset's name
	* @return		The asset requested
	*/
	template<class T>
	T* GetAsset(std::string name);

	/**
	* @brief		unload all assets flagged not preserved in the container
	* @pre			The container exists
	* @post			The non preserved assets are unloaded
	*/
	void Unload();

	/**
	* @brief		Unload all assets flagged preserved in the container
	* @pre			The container exists
	* @post			The preserved assets are unloaded
	*/
	void UnloadPreserved();



private:
	/*
	* @breif The list of assets
	*/
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


