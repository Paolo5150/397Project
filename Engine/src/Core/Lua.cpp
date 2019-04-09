#include "Lua.h"

int Lua::createdAssetsLength = 0;
InternalAsset** Lua::createdAssets = NULL;

//Opens the lua state and lua libraries, exits with code 1 if init fails
void Lua::InitLua(lua_State*& L)
{
	L = lua_open(); //Open lua_State
	luabind::open(L);

	if (L == NULL) //If state failed to open
	{
		Logger::LogError("Lua: Lua_state init fail");
	}

	luaL_openlibs(L); //Open lua libraries
	RegisterCppFunctions(L);
}

void Lua::CloseLua(lua_State*& L)
{
	lua_close(L); //Close lua_State
}

void Lua::RunLua(std::string fileName, bool clearAssets)
{
	lua_State* L;
	InitLua(L);
	if (clearAssets == true)
	{
		ClearCreatedAssets();
	}
	ExecuteLuaScript(L, fileName);
	CloseLua(L);
}

//Executes the script in a lua file, exits with code 2 if opening script fails
void Lua::ExecuteLuaScript(lua_State*& L, std::string fileName)
{
	if (luaL_dofile(L, fileName.c_str())) //Attempt to open and execute file, if it returns 1 then log an error
	{
		Logger::LogError("Lua: Failed to open script");
		Logger::LogError("Lua: ", lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	//int error = luaL_loadfile(L, fileName.c_str());

	//if (error) //Attempt to open and execute file, if it returns 1 then log an error
	//{
	//	Logger::LogError("Lua: Failed to open script");
	//	Logger::LogError("Lua: ", lua_tostring(L, -1));
	//	lua_pop(L, 1);
	//}
	//else
	//{
	//	luabind::object compiledScript(luabind::from_stack(L, -1));
	//	luabind::call_function<void>(compiledScript); //Call the script.

	//	lua_pop(L, 1);
	//}
}

//Returns true if the index variable is of type "type"
//Valid types are: nil | bool(ean) | num(ber) | string | table | func(tion) | cfunc(tion) | userdata
bool Lua::LuaType(lua_State*& L, int index, std::string type)
{
	//Check what type the user wants to check, if the type is available and the value is that type, return true, else return false
	if (type == "nil")
	{
		return lua_isnil(L, index);
	}
	else if (type == "bool" || type == "boolean")
	{
		return lua_isboolean(L, index);
	}
	else if (type == "num" || type == "number")
	{
		return lua_isnumber(L, index);
	}
	else if (type == "string")
	{
		return lua_isstring(L, index);
	}
	else if (type == "table")
	{
		return lua_istable(L, index);
	}
	else if (type == "func" || type == "function")
	{
		return lua_isfunction(L, index);
	}
	else if (type == "cfunc" || type == "cfunction")
	{
		return lua_iscfunction(L, index);
	}
	else if (type == "userdata")
	{
		return lua_isuserdata(L, index);
	}
	else
	{
		Logger::LogError("Lua: Invalid lua type!");
		return false;
	}
}

void Lua::ClearCreatedAssets()
{
	if (createdAssets != NULL)
	{
		delete[] createdAssets;
		createdAssetsLength = 0;
	}
}

void Lua::AddCreatedAsset(InternalAsset* asset)
{
	if (createdAssets == NULL)
	{
		createdAssets = new InternalAsset*[1];
	}

	createdAssets[createdAssetsLength] = asset;
	createdAssetsLength++;
}

InternalAsset* Lua::GetCreatedAsset(unsigned int index)
{
	if (index < createdAssetsLength)
	{
		return createdAssets[index];
	}
	else
	{
		return nullptr;
	}
}

void Lua::RegisterCppFunctions(lua_State*& L)
{
	//lua_register(L, "luaName", function);
	//lua_CFunction fp = &Lua_Create;
	lua_register(L, "CreateAsset", LuaRegistry::Lua_Create);
	//luabind::def("CreateAsset", &Lua_Create);
}