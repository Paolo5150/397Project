#pragma once
#include "..\Graphics\GraphicsAPI.h"
#include <map>
#include <list>
#include "AssetContainer.h"
#include "..\Graphics\Model.h"
#include "AssimpWrapper.h"
#include "..\Graphics\CubeMap.h"

/**
* @class AssetLoader
* @brief Loads external assets and makes them available to scenes in the game
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2018
*
*
* @bug No known bugs.
*/
class AssetLoader
{
public:
	friend class Core;
	/**
	* @brief						Return the asset loader instance
	*
	* @pre							The asset loader must exist
	* @post							The asset loader instance is returned
	*/
	static AssetLoader& Instance();

	/**
	* @brief						Initialize the asset loader
	*
	* @pre							The asset loader must exist
	* @post							The asset loader is initialized and ready for use
	* @param gAPI					The current graphics API
	*/
	static void Initialize(GraphicsAPI* gAPI);
	
	/**
	* @brief						Load a shader
	*
	* @pre							The asset loader must exist
	* @post							The shader is loaded 
	* @param name					The name that will bi given to the shader 
	* @param vertexPath				The absolute path to the vertex shader source file
	* @param fragmentPath			The absolute path to the fragment shader source file
	* @param preserve				Whether the asset will be preserved between scenes
	*/
	Shader* LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, bool preserve = false);

	/**
	* @brief						Load an image as texture
	*
	* @pre							The asset loader must exist
	* @post							The image is loaded and stored as Texture2D
	* @param path					The absolute path to the image
	* @param preserve				Whether the asset will be preserved between scenesh
	*/
	Texture2D* LoadTexture(std::string path,bool preserve = false);

	/**
	* @brief						Load textures to create a cubamap
	*
	* @pre							The asset loader must exist
	* @post							The textures are loaded and sotred as cubemap
	* @param pathToFolder			The absolute path to the folder where the textures are
	* @param preserve				Whether the asset will be preserved between scenes
	* @param top					The texture name that will be on the top of the cubemap
	* @param bottom					The texture name that will be on the bottom of the cubemap
	* @param left					The texture name that will be on the left of the cubemap
	* @param right					The texture name that will be on the right of the cubemap
	* @param front					The texture name that will be on the front of the cubemap
	* @param back					The texture name that will be on the back of the cubemap
	*/
	CubeMap* LoadCubeMap(std::string pathToFolder, bool preserve = false,
		std::string top = "top.jpg", std::string bottom = "bottom.jpg", 
		std::string left = "left.jpg", std::string right = "right.jpg",
		std::string front = "front.jpg", std::string back = "back.jpg");

	/**
	* @brief						Reads heightmap data without storing it
	*
	* @pre							The asset loader must exist, the path is valid
	* @post							The height map data is read and returned
	* @param path					The absolute path to the heightmap image
	* @param dataOut				The output data
	* @param widthOut				The width of the heightmap returned
	* @param heightOut				The height of the heightmap returned
	*/
	void ReadHeightmapData(std::string path, unsigned char* &dataOut, int& widthOut, int& heightOut);
	/**
	* @brief						Load a model
	*
	* @pre							The asset loader must exist
	* @post							The model is loaded
	* @param path					The absolute path to the model file
	* @param preserve				Whether the asset will be preserved between scenes
	*/
	Model* LoadModel(std::string path, bool loadTextures = true,bool preserve = false);
	
	/**
	* @brief						Unload a specific set of asset type
	*
	* @pre							The asset loader must exist
	* @post							The assets of the specified type are unloaded
	*/
	template<class T>
	void Unload();

	/**
	* @brief						Returns an asset by type and name
	*
	* @pre							The asset loader must exist, the asset is in a container
	* @post							The asset is returned
	* @param	name				The name of the asset
	* @return						The asaset casted to the specified type
	*/
	template <class T>
	T* GetAsset(std::string name);

private:
	/**
	* @brief						The asset loader instance
	*/
	static AssetLoader* instance;

	/**
	* @brief						Create the asset loader instance
	*/
	AssetLoader(GraphicsAPI* gAPI);

	/**
	* @brief						Destroy the asset loader instance, unload all assets
	*/
	~AssetLoader();

	/**
	* @brief						The ccurrent graphics API
	*/
	GraphicsAPI* graphucsAPI;

	/**
	* @brief						All the containers of assets
	*/
	std::map<std::string, AssetContainer> containers;

	/**
	* @brief						Helper class used to load 3D models
	*/
	AssimpWrapper assimpWrapper;

	/**
	* @brief						Unload a specific set of asset type flagged preserve
	*
	* @pre							The asset loader must exist
	* @post							The assets of the specified type are unloaded
	*/
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

