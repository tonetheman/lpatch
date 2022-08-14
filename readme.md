
# lpatch

a weird patcher of files...

to run
```
lpatch 
--input | -i filename
--patch | -p filename
```

## description
needed a way to patch a file byte by byte. there are tons of solutions already really but I like lua.

lpatch will read the input file completely into memory (so big files can be an issue). Then it will read the lua file you passed on the command line and execute it. lpatch also adds a few functions to give you access to the memory buffer that it read in. Also a way to write the buffer to disk.

## to build

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

## examples of patch files

Here is a simple example that will try to patch byte 100. First it will read the value and save it in a local variable named b. Then as a sanity check it will make sure it matches a certain number.

Finally it will patch byte 100 with a value of 43. Finally it will write the buffer in memory back to disk with a filename of testing.bin

```
local b = patch_getbyte(100)
if (b==200) then
    patch_setbyte(100, 43)
    patch_writefile("testing.bin)
else
    print("byte 100 did not match what was expected!")
end
print("finished)
```

I am using lua 5-4.4.4 and you have access to the standard libraries and the extra functions that are added by lpatch.


