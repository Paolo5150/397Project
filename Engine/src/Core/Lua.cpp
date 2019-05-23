#include "Lua.h"

lua_State* Lua::lState = NULL;
int Lua::createdAssetsLength = 0;
InternalAsset** Lua::createdAssets = NULL;

//Opens the lua state and lua libraries
void Lua::InitLua(lua_State*& L)
{
	L = lua_open(); //Open lua_State

	if (L == NULL) //If state failed to open
	{
		Logger::LogError("Lua: Lua_state init fail");
	}

	luaL_openlibs(L); //Open lua libraries
	RegisterCppFunctions(L);
}

void Lua::RegisterCppFunctions(lua_State*& L)
{
	//lua_register(L, "CreateAsset", LuaRegistry::Lua_Create);
	lua_register(L, "Create", LuaRegistry::Lua_Create);
}

void Lua::CloseLua(lua_State*& L, bool clearAssets)
{
	lua_close(L); //Close lua_State
	L = NULL;

	if (clearAssets == true)
	{
		ClearCreatedAssets();
	}
}

void Lua::RunLua(std::string fileName, bool closeState, bool clearAssets)
{
	if (lState == NULL)
	{
		InitLua(lState);
	}

	if (clearAssets == true)
	{
		ClearCreatedAssets();
	}
	ExecuteLuaScript(fileName);

	if (closeState)
	{
		CloseLua(lState);
	}
}

//Executes the script in a lua file
void Lua::ExecuteLuaScript(std::string fileName)
{
	if (luaL_dofile(lState, fileName.c_str())) //Attempt to open and execute file, if it returns 1 then log an error
	{
		Logger::LogError("Lua: Failed to open script");
		Logger::LogError("Lua: ", lua_tostring(lState, -1));
		lua_pop(lState, 1);
	}
}

//Executes the script in a lua file
void Lua::ExecuteLuaScript(lua_State*& L, std::string fileName)
{
	if (luaL_dofile(L, fileName.c_str())) //Attempt to open and execute file, if it returns 1 then log an error
	{
		Logger::LogError("Lua: Failed to open script");
		Logger::LogError("Lua: ", lua_tostring(L, -1));
		lua_pop(L, 1);
	}
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

void Lua::AddCreatedAsset(InternalAsset* asset)
{
	if (createdAssets == NULL) //Create a new array if the array is null
	{
		createdAssets = new InternalAsset*[1];
		//Don't increase the length here, it will be increased once the item is added
	}

	InternalAsset** tempArray = new InternalAsset*[createdAssetsLength]; //Create a temp array to copy the createdasset array to
	for (int i = 0; i < createdAssetsLength; i++) //Copy all of the created assets to the temp array
	{
		tempArray[i] = createdAssets[i];
	}
	delete[] createdAssets;
	createdAssets = new InternalAsset*[createdAssetsLength + 1]; //Create a new array, one element bigger than the previous array
	for (int i = 0; i < createdAssetsLength; i++) //Copy all the elements back in
	{
		createdAssets[i] = tempArray[i];
	}
	delete[] tempArray; //Delete the temp array

	createdAssets[createdAssetsLength] = asset; //Add the asset
	createdAssetsLength++; //Increase the length count by one
}

void Lua::RemoveCreatedAsset(unsigned int index)
{
	if (index < GetCreatedAssetLength())
	{
		InternalAsset** tempArray = new InternalAsset*[createdAssetsLength]; //Create a temp array to copy the createdasset array to
		for (int i = 0; i < createdAssetsLength; i++) //Copy all of the created assets to the temp array
		{
			tempArray[i] = createdAssets[i];
		}
		delete[] createdAssets;
		createdAssets = new InternalAsset*[createdAssetsLength - 1]; //Create a new array, one element smaller than the previous array
		int addedIndex = 0;
		for (int i = 0; i < createdAssetsLength; i++) //Copy all the elements back in, minus the removed one
		{
			if (i != index)
			{
				createdAssets[addedIndex] = tempArray[i];
				addedIndex++;
			}
		}
		delete[] tempArray; //Delete the temp array

		createdAssetsLength--; //Decrease the length count by one
	}
	else
	{
		Logger::LogWarning("Lua::RemoveCreatedAsset: Index out of bounds!");
	}
}

int Lua::GetCreatedAssetLength()
{
	return createdAssetsLength;
}

InternalAsset* Lua::GetCreatedAsset(unsigned int index)
{
	if (index < createdAssetsLength)
	{
		return createdAssets[index];
	}
	else
	{
		Logger::LogError("Invalid createdAssets array index!");
		return nullptr;
	}
}

void Lua::ClearCreatedAssets()
{
	if (createdAssets != NULL)
	{
		delete[] createdAssets;
		createdAssets = NULL;
		createdAssetsLength = 0;
	}
}

void Lua::StackDump(lua_State *L)
{
	for (int i = 1; i <= lua_gettop(L); i++)
	{
		int type = lua_type(L, i);
		switch (type)
		{
			case LUA_TSTRING:
				Logger::LogInfo(lua_tostring(L, i));
				break;
			case LUA_TBOOLEAN:
				Logger::LogInfo(lua_toboolean(L, i) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				Logger::LogInfo(lua_tonumber(L, i));
				break;
			default:
				Logger::LogInfo(lua_typename(L, type));
				break;
		}
	}
	Logger::LogInfo("\n");
}

void Lua::StackDump(lua_State *L, int index)
{
	int type = lua_type(L, index);
	switch (type)
	{
		case LUA_TSTRING:
			Logger::LogInfo(lua_tostring(L, index));
			break;
		case LUA_TBOOLEAN:
			Logger::LogInfo(lua_toboolean(L, index) ? "true" : "false");
			break;
		case LUA_TNUMBER:
			Logger::LogInfo(lua_tonumber(L, index));
			break;
		default:
			Logger::LogInfo(lua_typename(L, type));
			break;
	}
}

std::string Lua::GetStringFromStack(std::string variable, lua_State*& L)
{
	lua_settop(L, 0);
	lua_getglobal(L, variable.c_str());

	if (LuaType(L, 1, "string"))
	{
		std::string stack = (std::string)lua_tostring(L, 1);
		lua_pop(L, 1);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not a string!");
		throw "Lua stack index is not a string!";
		return "";
	}
}

std::string Lua::GetStringFromStack(int index, lua_State*& L)
{
	if (LuaType(L, index, "string"))
	{
		std::string stack = (std::string)lua_tostring(L, index);
		lua_pop(L, index);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not a string!");
		throw "Lua stack index is not a string!";
		return "";
	}
}

int Lua::GetIntFromStack(std::string variable, lua_State*& L)
{
	lua_settop(L, 0);
	lua_getglobal(L, variable.c_str());

	if (LuaType(L, 1, "number"))
	{
		int stack = (int)lua_tonumber(L, 1);
		lua_pop(L, 1);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not an int!");
		throw "Lua stack index is not a int!";
		return -1;
	}
}

int Lua::GetIntFromStack(int index, lua_State*& L)
{
	if (LuaType(L, index, "number"))
	{
		int stack = (int)lua_tonumber(L, index);
		lua_pop(L, index);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not a int!");
		throw "Lua stack index is not a int!";
		return -1;
	}
}

float Lua::GetFloatFromStack(std::string variable, lua_State*& L)
{
	lua_settop(L, 0);
	lua_getglobal(L, variable.c_str());

	if (LuaType(L, 1, "number"))
	{
		float stack = (float)lua_tonumber(L, 1);
		lua_pop(L, 1);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not a float!");
		throw "Lua stack index is not a float!";
		return -1;
	}
}

float Lua::GetFloatFromStack(int index, lua_State*& L)
{
	if (LuaType(L, index, "number"))
	{
		float stack = (float)lua_tonumber(L, index);
		lua_pop(L, index);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not a float!");
		throw "Lua stack index is not a float!";
		return -1;
	}
}

bool Lua::GetBoolFromStack(std::string variable, lua_State*& L)
{
	lua_settop(L, 0);
	lua_getglobal(L, variable.c_str());

	if (LuaType(L, 1, "bool"))
	{
		bool stack = (bool)lua_toboolean(L, 1);
		lua_pop(L, 1);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not a bool!");
		throw "Lua stack index is not a bool!";
		return false;
	}
}

bool Lua::GetBoolFromStack(int index, lua_State*& L)
{
	if (LuaType(L, index, "bool"))
	{
		bool stack = (bool)lua_toboolean(L, index);
		lua_pop(L, index);
		return stack;
	}
	else
	{
		Logger::LogError("Lua stack index is not a bool!");
		throw "Lua stack index is not a bool!";
		return false;
	}
}