#ifndef _LPATCH_FUNCS_H_
#define _LPATCH_FUNCS_H_

#include "lua.hpp"


static int l_getbyte(lua_State * L);
static int l_getfilesize(lua_State* L);
static int l_tonyhello(lua_State* L);
static int l_setbyte(lua_State* L);
static int l_writefile(lua_State* L);
void lpatch_add_lua_funcs(lua_State* L);


#endif