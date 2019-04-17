#pragma once
#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include "Logger.h"
#include "LuaRegistry.h"
#include "..\Utils\Asset.h"
#include "..\GameObject\GameObject.h"

#include <iostream>

/**
* @class Lua
* @brief Manages a static lua state, and executes lua scripts and stored objects created in the lua script
*
*
* Long description goes here
*
* @author Dylan Green
* @version 01
* @date 10/04/2019
*
*
* @bug No known bugs.
*/
static class Lua
{
public:
	//Initialisation
	/**
	* @brief Initialises a lua state if it is not null and opens the lua libraries. Uses the built-in lua state if none is specified
	*
	* @param L lua state to initialise
	*/
	static void InitLua(lua_State*& L = lState); //Initialises the lua state

	/**
	* @brief	Registers all of the function wrappers in the lua registry to the specified lua state
	*
	* @param	L	the lua state to register the functions to
	*/
	static void RegisterCppFunctions(lua_State*& L = lState); //Registers the functions in LuaRegistry

	/**
	* @brief	Closes the specified lua state, and optionally clears all the created assets
	*
	* @param	L				the lua state to close
	* @param	clearAssets		whether to clear all the created assets so far
	*/
	static void CloseLua(lua_State*& L = lState, bool clearAssets = false); //Closes the lua state

	//Execution
	/**
	* @brief	Initialises the built-in lua state, optionally clears the created assets, executes a lua script, and optionally closes the built-in lua state
	*
	* @param	fileName		the file name of the lua script to run
	* @param	closeState		whether to close the built-in lua state at the end of the function
	* @param	clearAssets		whether to clear all the created assets so far
	*/
	static void RunLua(std::string fileName, bool closeState = false, bool clearAssets = false); //Opens a new lua state or (optionally) uses the static state, (optionally) clears the createdAssets array, executes the script with the fileName, and closes the lua_state

	/**
	* @brief	Execusts a lua script from a given file using the built-in lua state
	*
	* @param	fileName	the file name of the lua script to run
	*/
	static void ExecuteLuaScript(std::string fileName);

	/**
	* @brief	Execusts a lua script from a given file using the given lua state
	*
	* @param	
	* @param	fileName	the file name of the lua script to run
	*/
	static void ExecuteLuaScript(lua_State*& L, std::string fileName);

	//Utility
	static bool LuaType(lua_State*& L, int index, std::string type);

	//Asset Management
	static void AddCreatedAsset(InternalAsset* asset);
	static InternalAsset* GetCreatedAsset(unsigned int index);
	//static InternalAsset* GetCreatedAsset(std::string name);
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

