
# lpatch

a weird patcher of files...

to run
```
lpatch --input|-i filename
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

it will read the input file you tell it on the command line and then read the file patcher.lua from the disk and run it
