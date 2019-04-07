#pragma once
#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include "..\Core\Logger.h"
#include "..\Utils\Asset.h"
#include "..\Utils\GameAssetFactory.h"

#include <iostream>

static class Lua
{
public:
	static void InitLua(lua_State*& L);
	static void CloseLua(lua_State*& L);
	static void RunLua(std::string fileName);
	static void ExecuteLuaScript(lua_State*& L, std::string fileName);
	static bool LuaType(lua_State*& L, int index, std::string type);
	static void ClearCreatedAssets();
	static void AddCreatedAsset(InternalAsset* asset);
	static InternalAsset* GetCreatedAsset(unsigned int index);
	static InternalAsset* PopCreatedAsset(unsigned int index);

private:
	static InternalAsset** createdAssets;
	static int createdAssetsLength;

	static void RegisterCppFunctions(lua_State*& L);

	int Lua_Create(lua_State*& L);
};

