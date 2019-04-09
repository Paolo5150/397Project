#pragma once
#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include "Logger.h"
#include "LuaRegistry.h"
#include "..\Utils\Asset.h"

#include <iostream>

static class Lua
{
public:
	static void InitLua(lua_State*& L = lState); //Initialises the lua state
	static void RegisterCppFunctions(lua_State*& L = lState); //Registers the functions in LuaRegistry
	static void CloseLua(lua_State*& L = lState); //Closes the lua state

	static void RunLua(std::string fileName, bool useStatic = true, bool clearAssets = false); //Opens a new lua state or (optionally) uses the static state, (optionally) clears the createdAssets array, executes the script with the fileName, and closes the lua_state

	static void ExecuteLuaScript(std::string fileName);
	static void ExecuteLuaScript(lua_State*& L, std::string fileName);

	static bool LuaType(lua_State*& L, int index, std::string type);

	static void ClearCreatedAssets();
	static void AddCreatedAsset(InternalAsset* asset);

	static std::string GetStringFromStack(lua_State*& L, int stackIndex); //Gets a string from the lua state, with the index stackIndex
	static int GetIntFromStack(lua_State*& L, int stackIndex); //Gets an int from the lua state, with the index stackIndex
	static float GetFloatFromStack(lua_State*& L, int stackIndex); //Gets an int from the lua state, with the index stackIndex

	static InternalAsset* GetCreatedAsset(unsigned int index);

private:
	static lua_State* lState;
	static InternalAsset** createdAssets;
	static int createdAssetsLength;


	int Lua_Create(lua_State* L = lState);
};

