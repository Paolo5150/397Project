#pragma once
#include <lua.hpp>
#include <string>
#include "Logger.h"
#include "Lua.h"
#include "..\Utils\Asset.h"
#include "..\Utils\GameAssetFactory.h"

static class LuaRegistry
{
public:
	static int LuaRegistry::Lua_Create(lua_State* L);
};

