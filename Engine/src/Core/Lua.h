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
//---- Public Member Functions ----//
	//-- Initialisation --//
	/**
	* @brief Initialises a lua state if it is not null and opens the lua libraries. Uses the built-in lua state if none is specified
	*
	* @param L lua state to initialise
	*/
	static void InitLua(lua_State*& L = lState); //Initialises the lua state

	/**
	* @brief		Registers all of the function wrappers in the lua registry to the specified lua state. Uses the built-in lua state if none is specified
	*
	* @param		L	the lua state to register the functions to
	*/
	static void RegisterCppFunctions(lua_State*& L = lState); //Registers the functions in LuaRegistry

	/**
	* @brief		Closes the specified lua state, and optionally clears all the created assets. Uses the built-in lua state if none is specified
	*
	* @param		L				the lua state to close
	* @param		clearAssets		whether to clear all the created assets so far
	*/
	static void CloseLua(lua_State*& L = lState, bool clearAssets = false); //Closes the lua state

	//-- Execution --//
	/**
	* @brief		Initialises the built-in lua state, optionally clears the created assets, executes a lua script, and optionally closes the built-in lua state
	*
	* @param		fileName		the file name of the lua script to run
	* @param		closeState		whether to close the built-in lua state at the end of the function
	* @param		clearAssets		whether to clear all the created assets so far
	*/
	static void RunLua(std::string fileName, bool closeState = false, bool clearAssets = false); //Opens a new lua state or (optionally) uses the static state, (optionally) clears the createdAssets array, executes the script with the fileName, and closes the lua_state

	/**
	* @brief		Execusts a lua script from a given file using the built-in lua state
	*
	* @param		fileName	the file name of the lua script to run
	*/
	static void ExecuteLuaScript(std::string fileName);

	/**
	* @brief		Execusts a lua script from a given file using the given lua state
	*
	* @param		L			the lua state to execute the script on
	* @param		fileName	the file name of the lua script to run
	*/
	static void ExecuteLuaScript(lua_State*& L, std::string fileName);

	//-- Utility --//
	/**
	* @brief		Returns whether the lua stack item at the given index is of the specified type
	*
	* @param		L		the lua state to look for items in
	* @param		index	the index of the item to check the type of
	* @param		type	the data type to check (nil, bool|boolean, num|number, string, table, func|function, cfunc|cfunction, userdata)
	*/
	static bool LuaType(lua_State*& L, int index, std::string type);

	//-- Asset Management --//
	/**
	* @brief		Adds an asset to the array of created assets
	*
	* @param		asset	the asset to add to the array
	*/
	static void AddCreatedAsset(InternalAsset* asset);

	/**
	* @brief		Gets the length of the array of created assets
	*
	* @return		Length of the array of created assets
	*/
	static int GetCreatedAssetLength();

	/**
	* @brief		Gets an asset from the array of created assets, returns nullptr if the index is not valid
	*
	* @param		index	the index of the asset to retreive
	*/
	static InternalAsset* GetCreatedAsset(unsigned int index);

	/**
	* @brief		Clears all the created assets from the array
	*/
	static void ClearCreatedAssets();

	/**
	* @brief		Dumps the contents of the lua_state's stack to the logger
	*/
	static void StackDump(lua_State *L);

	/**
	* @brief		Dumps the contents of the lua_state'stack at the specified index to the logger
	*/
	static void StackDump(lua_State *L, int index);

	//-- Stack Returns --//
	/**
	* @brief		Gets a string variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		variable	the variable name to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		string		the stack variable
	* @throws		Exception if variable is not a string
	*/
	static std::string GetStringFromStack(std::string variable, lua_State*& L = lState); //Gets a string from the lua state

	/**
	* @brief		Gets a bool variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		index		the index of the variable to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		string		the stack variable
	* @throws		Exception if variable is not a string
	*/
	static std::string GetStringFromStack(int index, lua_State*& L = lState); //Gets a string from the lua state
	
	/**
	* @brief		Gets an int variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		variable	the variable name to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		int			the stack variable
	* @throws		Exception if variable is not a int
	*/
	static int GetIntFromStack(std::string variable, lua_State*& L = lState); //Gets an int from the lua state

	/**
	* @brief		Gets a bool variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		index		the index of the variable to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		int			the stack variable
	* @throws		Exception if variable is not a int
	*/
	static int GetIntFromStack(int index, lua_State*& L = lState); //Gets an int from the lua state

	/**
	* @brief		Gets a float variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		variable	the variable name to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		float		the stack variable
	* @throws		Exception if variable is not a float
	*/
	static float GetFloatFromStack(std::string variable, lua_State*& L = lState); //Gets a float from the lua state

	/**
	* @brief		Gets a float variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		index		the index of the variable to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		float		the stack variable
	* @throws		Exception if variable is not a float
	*/
	static float GetFloatFromStack(int index, lua_State*& L = lState); //Gets a float from the lua state
	
	/**
	* @brief		Gets a bool variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		variable	the variable name to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		bool		the stack variable
	* @throws		Exception if variable is not a bool
	*/
	static bool GetBoolFromStack(std::string variable, lua_State*& L = lState); //Gets a bool from the lua state

	/**
	* @brief		Gets a bool variable from the given lua state. Uses the built-in lua state if none is specified
	*
	* @param		index		the index of the variable to get from the stack
	* @param		L			the lua state to get the variable from
	*
	* @return		bool		the stack variable
	* @throws		Exception if variable is not a bool
	*/
	static bool GetBoolFromStack(int index, lua_State*& L = lState); //Gets a bool from the lua state

private:
	static lua_State* lState; //built-in lua state
	static InternalAsset** createdAssets; //array of assets created by lua scripts
	static int createdAssetsLength; //size of the createdAssets array
};

