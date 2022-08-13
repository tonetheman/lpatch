#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "lua.hpp"

char * buffer;
long fsize;

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

int main(int argc, char** argv) {
    char * input_filename = 0;
    char * patch_filename = 0;

    for(int i=0;i<argc;i++) {
        if ((strcmp(argv[i],"--input")==0) || strcmp(argv[i],"-i")==0) {
            input_filename = argv[i+1];
        }
        if ((strcmp(argv[i],"--patch")==0) || (strcmp(argv[i],"-p")==0)) {
            patch_filename = argv[i+1];
        }
    }

    if ((input_filename==0) || (patch_filename==0)) {
        printf("--input <filename> --patch <filename>\n");
        printf("-i <filename> -p <filename>\n");
        printf("descrption\n");
        printf("lpatch will read the input file into memory in a buffer\n");
        printf("lpatch will read the patch file given on the cmd line\n");
        printf("lua5.4 is used with the following extra functions\n");
        printf("patch_getbyte(n) - will return the byte at this position\n");
        printf("patch_getfilesize() - return the filesize we read\n");
        printf("patch_hello() - check that anything is working at all\n");
        printf("patch_setbyte(index,value) - change the buffer[index] to have the value passed\n");
        printf("patch_writefile(filename) - write the buffer to disk\n");
        return EXIT_FAILURE;
    }

    printf("lpatch is running...\n");
    printf("lpatch is reading the input file...\n");
    // open the file
    FILE * inf = fopen(input_filename,"r");

    printf("lpatch is determining the size of the input file...\n");
    // get the file size
    fseek(inf, 0, SEEK_END);
    // global since lua can read access
    fsize = ftell(inf);
    fseek(inf, 0, SEEK_SET); 

    printf("lpatch is reading the input file into memory\n");
    // alloc the whole damn thing!
    buffer = (char*)malloc(fsize);
    // read it all into memory!
    fread(buffer, fsize,1,inf);

    printf("lpatch is closing the input file\n");
    // close up the mess
    fclose(inf);

    // load up lua
    lua_State *L = luaL_newstate();

    // load up standard libs
    luaL_openlibs(L);

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

    // load the hardcoded file patcher.lua
    // and then run it
    if (luaL_loadfile(L,"patcher.lua") || lua_pcall(L,0,0,0)) {
        printf("lpathc: got an error of sometype loading patcher.lua :(\n");
        printf("%s", lua_tostring(L, -1));
    }
    
    return EXIT_SUCCESS;
}
