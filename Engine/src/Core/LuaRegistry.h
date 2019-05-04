#pragma once
#include <lua.hpp>
#include <string>
#include "Logger.h"
#include "Lua.h"
#include "..\Utils\Asset.h"
#include "..\Utils\GameAssetFactory.h"
#include "..\Components\AIBase.h"

/**
* @class Lua
* @brief Contains all of the c++ function wrappers for use in lua scripts
*
* @see Lua#RegisterCppFunctions
*
* @author Dylan Green
* @version 01
* @date 11/04/2019
*
*
* @bug No known bugs.
*/
static class LuaRegistry
{
public:
//---- Public Member Functions ----//
	/**
	* @brief		Wrapper for GameAssetFactory.Create()
	*
	* @param		L lua state for lua cfunction
	*
	* @see			GameAssetFactory#Create
	*/
	static int Lua_Create(lua_State* L);

	static int Lua_CreateObject(lua_State* L);
};