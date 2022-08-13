
# lpatch

a weird patcher of files...

to run
```
lpatch 
--input | -i filename
--patch | -p filename
```

to build

first build lua
```
cd lua-5.4.4
make
```

then come back to the main directory and make the patcher binary
```
cd ..
make
```

will create lpatch in current directory.

## description
needed a way to patch a file byte by byte. there are tons of solutions already really but I like lua.

lpatch will read the input file completely into memory (so big files can be an issue). Then it will read the lua file you passed on the command line and execute it. lpatch also adds a few functions to give you access to the memory buffer that it read in. Also a way to write the buffer to disk.