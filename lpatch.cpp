#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "lua.hpp"
#include "lpatch_funcs.h"

// these are externed in lpatch_funcs
char * buffer;
long fsize;

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

    // load up global lua funcs specific to patching
    lpatch_add_lua_funcs(L);

    // load the hardcoded file patcher.lua
    // and then run it
    if (luaL_loadfile(L,"patcher.lua") || lua_pcall(L,0,0,0)) {
        printf("lpathc: got an error of sometype loading patcher.lua :(\n");
        printf("%s", lua_tostring(L, -1));
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
