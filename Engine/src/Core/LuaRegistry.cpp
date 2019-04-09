#include "LuaRegistry.h"

int LuaRegistry::Lua_Create(lua_State* L)
{
	int numParams = lua_gettop(L); //Number of parameters on the stack

	if (numParams < 1 || numParams > 2) //Check we have enough parameters
	{
		Logger::LogError("Lua_Create: not enough parameters for Create function");
	}

	if (!Lua::LuaType(L, -1, "string") || (numParams == 2 && !Lua::LuaType(L, -2, "string"))) //Check all the parameters are strings
	{
		Logger::LogError("Lua_Create: parameters must all be strings!");
	}

	std::string name;
	std::string assetType;
	InternalAsset* asset;

	if (numParams == 2)
	{
		name = lua_tostring(L, -1); //Get the parameters from the stack
		assetType = lua_tostring(L, -2);
		asset = GameAssetFactory::Instance().Create(assetType, name); //Create Asset
	}
	else
	{
		assetType = lua_tostring(L, -1); //Get the parameters from the stack
		asset = GameAssetFactory::Instance().Create(assetType); //Create Asset
	}

	Lua::AddCreatedAsset(asset);

	return 0; //Return number of values
}