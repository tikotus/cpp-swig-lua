#include <lua.hpp>
#include <stdlib.h>
#include "interface.h"

extern "C" int luaopen_interface(lua_State* L);

int main(void) {

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  // Setup interface
  {
    lua_pushcfunction(L, luaopen_interface);
  	lua_pushliteral(L, LUA_TABLIBNAME);
  	lua_call(L, 1, 0);
  }

  // Load main lua file
  {
  	FILE* mainLua = fopen("scripts/main.lua", "rb");
  	fseek(mainLua, 0, SEEK_END);
  	long fileSize = ftell(mainLua);
  	fseek(mainLua, 0, SEEK_SET);
  	char* source = (char*)calloc(fileSize + 1, sizeof(char));
  	fread(source, fileSize, 1, mainLua);
  	fclose(mainLua);

    if (luaL_loadstring(L, source)) {
  		printf("Lua error: %s\n", lua_tostring(L, -1));
  		return 0;
  	}
  	if (lua_pcall(L, 0, 0, 0) != 0) {
  		printf("Lua error: %s\n", lua_tostring(L, -1));
  		return 0;
  	}
  }

  // Call a lua function
  {
    printf("Value of foo: %d\n", foo);
    printf("Call lua function\n");
    lua_getglobal(L, "main");
    if (lua_pcall(L, 0, 0, 0)) {
      printf("Lua error: %s\n", lua_tostring(L, -1));
  		lua_pop(L, 1);
    }
    printf("Value of foo: %d\n", foo);
  }

  return 0;
}
