
#include <cstdio>
#include "lpatch_funcs.h"

extern char * buffer;
extern long fsize;

static int l_getbyte(lua_State * L) {
    // get the number the user sent us
    // in this case the offset
    int d = (int)lua_tonumber(L, 1);
    // tell them the byte at that position
    lua_pushnumber(L,buffer[d]);
    return 1; // we returned a single value
}

static int l_getfilesize(lua_State* L) {
    lua_pushnumber(L,(float)fsize);
    return 1;
}

static int l_tonyhello(lua_State* L) {
    printf("hello from in a c function\n");
    return 0;
}

static int l_setbyte(lua_State* L) {
    // get the number the user sent us
    // in this case the offset
    int index = (int)lua_tonumber(L, 1);
    // get the number the user sent us
    // in this case the offset
    unsigned char value = (unsigned char)lua_tonumber(L, 2);    
    buffer[index] = value;

    return 0;
}

static int l_writefile(lua_State* L) {
    const char * filename = lua_tostring(L,1);

    // take the buffer we have and write it
    FILE * outf = fopen(filename,"w");
    fwrite(buffer, fsize, 1, outf);
    fclose(outf);

    return 0;
}


void lpatch_add_lua_funcs(lua_State* L) {
    // adding our stuff
    lua_pushcfunction(L,l_getbyte);
    lua_setglobal(L, "patch_getbyte");
    lua_pushcfunction(L,l_getfilesize);
    lua_setglobal(L, "patch_getfilesize");
    lua_pushcfunction(L, l_tonyhello);
    lua_setglobal(L, "patch_hello");
    lua_pushcfunction(L,l_setbyte);
    lua_setglobal(L, "patch_setbyte");
    lua_pushcfunction(L,l_writefile);
    lua_setglobal(L, "patch_writefile");

}