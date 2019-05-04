#include "LuaRegistry.h"

int LuaRegistry::Lua_Create(lua_State* L)
{
	int numParams = lua_gettop(L); //Number of parameters on the stack

	if (numParams < 1 || numParams > 2) //Check we have enough parameters
	{
		Logger::LogError("Lua_Create: not enough parameters for Create function");
	}

	if (!Lua::LuaType(L, -1, "string") || (numParams >= 2 && !Lua::LuaType(L, -2, "string"))) //Check all the parameters are strings
	{
		Logger::LogError("Lua_Create: parameters are not valid!");
	}

	std::string name;
	std::string assetType;
	InternalAsset* asset;

	if (numParams == 2)
	{
		name = lua_tostring(L, -1); //Get the parameters from the stack
		assetType = lua_tostring(L, -2);
		lua_pop(L, -1);
		lua_pop(L, -2);
		asset = GameAssetFactory::Instance().Create(assetType, name); //Create Asset
	}
	else
	{
		assetType = lua_tostring(L, -1); //Get the parameter from the stack
		lua_pop(L, -1);
		if (assetType != "Model" && assetType != "GameObject")
		{
			asset = GameAssetFactory::Instance().Create(assetType); //Create Asset
		}
		else
		{
			Logger::LogError("Lua_Create: Not enough parameters to create a ", assetType, "!");
			throw "Lua_Create: Not enough parameters to create requested type!";
		}
	}

	Lua::AddCreatedAsset(asset);

	return 0; //Return number of values
}

int LuaRegistry::Lua_CreateObject(lua_State* L)
{
	int numParams = lua_gettop(L); //Number of parameters on the stack

	if (numParams != 5) //Check we have enough parameters
	{
		Logger::LogError("Lua_Create: not enough parameters for CreateObject function");
	}

	if (!Lua::LuaType(L, -5, "string") && !Lua::LuaType(L, -4, "number") && !Lua::LuaType(L, -3, "number") && !Lua::LuaType(L, -2, "number") && !Lua::LuaType(L, -1, "number")) //Check all the parameters are correct
	{
		Logger::LogError("Lua_CreateObject: parameters are not valid!");
	}

	std::string name;
	std::string assetType;
	InternalAsset* asset;

	if (numParams == 5)
	{
		float scale = lua_tonumber(L, -1);
		float z = lua_tonumber(L, -2);
		float y = lua_tonumber(L, -3);
		float x = lua_tonumber(L, -4);
		assetType = lua_tostring(L, -5);
		lua_pop(L, -1);
		lua_pop(L, -2);
		lua_pop(L, -3);
		lua_pop(L, -4);
		lua_pop(L, -5);
		asset = GameAssetFactory::Instance().Create(assetType); //Create Asset
		
		((GameObject*)asset)->transform.SetPosition(x, y, z);

		((GameObject*)asset)->transform.SetScale(scale, scale, scale);
	}
	else
	{
		Logger::LogError("Lua_Create: Not enough parameters to create a ", assetType, "!");
		throw "Lua_Create: Not enough parameters to create requested type!";
	}

	Lua::AddCreatedAsset(asset);

	return 0; //Return number of values
}