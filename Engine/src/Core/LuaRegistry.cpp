#include "LuaRegistry.h"
#include "..\Utils\SaveGameManager.h"

int LuaRegistry::Lua_Create(lua_State* L)
{
	int numParams = lua_gettop(L); //Number of parameters on the stack

	if (numParams != 4 && numParams != 7 && numParams != 10) //Check we have enough parameters
	{
		Logger::LogError("Lua_Create: not enough parameters for Create function");
	}

	//Check all the parameters are correct
	if ((numParams == 4 && !Lua::LuaType(L, -4, "string") && !Lua::LuaType(L, -3, "number") && !Lua::LuaType(L, -2, "number") && !Lua::LuaType(L, -1, "number"))
		|| (numParams == 7 && !Lua::LuaType(L, -7, "string") && !Lua::LuaType(L, -6, "number") && !Lua::LuaType(L, -5, "number") && !Lua::LuaType(L, -4, "number") && !Lua::LuaType(L, -3, "number") && !Lua::LuaType(L, -2, "number") && !Lua::LuaType(L, -1, "number"))
		|| (numParams == 10 && !Lua::LuaType(L, -10, "string") && !Lua::LuaType(L, -9, "number") && !Lua::LuaType(L, -8, "number") && !Lua::LuaType(L, -7, "number") && !Lua::LuaType(L, -6, "number") && !Lua::LuaType(L, -5, "number") && !Lua::LuaType(L, -4, "number") && !Lua::LuaType(L, -3, "number") && !Lua::LuaType(L, -2, "number") && !Lua::LuaType(L, -1, "number")))
	{
		Logger::LogError("Lua_CreateObject: parameters are not valid!");
	}

	std::string assetType;
	InternalAsset* asset = nullptr;

	if (numParams == 10)
	{
		//Get the parameters from the stack
		float scaleZ = lua_tonumber(L, -1);
		float scaleY = lua_tonumber(L, -2);
		float scaleX = lua_tonumber(L, -3);
		float rotZ = lua_tonumber(L, -4);
		float rotY = lua_tonumber(L, -5);
		float rotX = lua_tonumber(L, -6);
		float posZ = lua_tonumber(L, -7);
		float posY = lua_tonumber(L, -8);
		float posX = lua_tonumber(L, -9);
		assetType = lua_tostring(L, -10);

		lua_pop(L, -1);
		lua_pop(L, -2);
		lua_pop(L, -3);
		lua_pop(L, -4);
		lua_pop(L, -5);
		lua_pop(L, -6);
		lua_pop(L, -7);
		lua_pop(L, -8);
		lua_pop(L, -9);
		lua_pop(L, -10);

		if (!(SaveGameManager::loadWhenPossible == true && SaveGameManager::IsSaveable(assetType)))
		{
			asset = GameAssetFactory::Instance().Create(assetType); //Create Asset

			if (posX == -9999)
			{
				posX = Terrain::Instance().GetCenter().x;
			}

			if (posZ == -9999)
			{
				posZ = Terrain::Instance().GetCenter().z;
			}

			if (posY == -9999)
			{
				posY = Terrain::Instance().GetHeightAt(posX, posZ);
			}

			((GameObject*)asset)->transform.SetPosition(posX, posY, posZ);

			((GameObject*)asset)->transform.SetRotation(rotX, rotY, rotZ);

			((GameObject*)asset)->transform.SetScale(scaleX, scaleY, scaleZ);
		}
	}
	else if (numParams == 7)
	{
		//Get the parameters from the stack
		float rotZ = lua_tonumber(L, -1);
		float rotY = lua_tonumber(L, -2);
		float rotX = lua_tonumber(L, -3);
		float posZ = lua_tonumber(L, -4);
		float posY = lua_tonumber(L, -5);
		float posX = lua_tonumber(L, -6);
		assetType = lua_tostring(L, -7);

		lua_pop(L, -1);
		lua_pop(L, -2);
		lua_pop(L, -3);
		lua_pop(L, -4);
		lua_pop(L, -5);
		lua_pop(L, -6);
		lua_pop(L, -7);

		if (!(SaveGameManager::loadWhenPossible == true && SaveGameManager::IsSaveable(assetType)))
		{
			asset = GameAssetFactory::Instance().Create(assetType); //Create Asset


			if (posX == -9999)
			{
				posX = Terrain::Instance().GetCenter().x;
			}

			if (posZ == -9999)
			{
				posZ = Terrain::Instance().GetCenter().z;
			}

			if (posY == -9999)
			{
				posY = Terrain::Instance().GetHeightAt(posX, posZ);
			}

			((GameObject*)asset)->transform.SetPosition(posX, posY, posZ);

			((GameObject*)asset)->transform.SetRotation(rotX, rotY, rotZ);
		}
	}
	else if (numParams == 4)
	{
		//Get the parameters from the stack
		float posZ = lua_tonumber(L, -1);
		float posY = lua_tonumber(L, -2);
		float posX = lua_tonumber(L, -3);
		assetType = lua_tostring(L, -4);

		lua_pop(L, -1);
		lua_pop(L, -2);
		lua_pop(L, -3);
		lua_pop(L, -4);

		if (!(SaveGameManager::loadWhenPossible == true && SaveGameManager::IsSaveable(assetType)))
		{
			asset = GameAssetFactory::Instance().Create(assetType); //Create Asset

			if (posX == -9999)
			{
				posX = Terrain::Instance().GetCenter().x;
			}

			if (posZ == -9999)
			{
				posZ = Terrain::Instance().GetCenter().z;
			}

			if (posY == -9999)
			{
				posY = Terrain::Instance().GetHeightAt(posX, posZ);
			}

			((GameObject*)asset)->transform.SetPosition(posX, posY, posZ);
		}
	}
	else
	{
		Logger::LogError("Lua_Create: Not enough parameters to create a ", assetType, "!");
		//throw "Lua_CreateObject: Not enough parameters to create requested type!";
	}

	if (asset != nullptr)
	{
		Lua::AddCreatedAsset(asset);
	}

	return 0; //Return number of values
}