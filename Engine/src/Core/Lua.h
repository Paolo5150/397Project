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
	//Initialisation
	static void InitLua(lua_State*& L = lState); //Initialises the lua state
	static void RegisterCppFunctions(lua_State*& L = lState); //Registers the functions in LuaRegistry
	static void CloseLua(lua_State*& L = lState, bool clearAssets = false); //Closes the lua state

	//Execution
	static void RunLua(std::string fileName, bool closeState = false, bool clearAssets = false); //Opens a new lua state or (optionally) uses the static state, (optionally) clears the createdAssets array, executes the script with the fileName, and closes the lua_state

	static void ExecuteLuaScript(std::string fileName);
	static void ExecuteLuaScript(lua_State*& L, std::string fileName);

	//Utility
	static bool LuaType(lua_State*& L, int index, std::string type);

	//Asset Management
	static void AddCreatedAsset(InternalAsset* asset);
	static InternalAsset* GetCreatedAsset(unsigned int index);
	static void ClearCreatedAssets();

	//Stack Returns
	static std::string GetStringFromStack(std::string variable, lua_State*& L = lState); //Gets a string from the lua state, with the index stackIndex
	static int GetIntFromStack(std::string variable, lua_State*& L = lState); //Gets an int from the lua state, with the index stackIndex
	static float GetFloatFromStack(std::string variable, lua_State*& L = lState); //Gets an int from the lua state, with the index stackIndex
	

private:
	static lua_State* lState;
	static InternalAsset** createdAssets;
	static int createdAssetsLength;
};

