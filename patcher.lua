
--[[
    this is an example patcher.lua file

    this is a big ass comment by the way in lua

    lua 5.4 in the house
]]

-- yup you can even define functions
function dbg(...)
    io.write("dbg---:")
    for i,v in ipairs({...}) do
        print(i,v)
    end
end

-- patch_getbyte will return a byte value from the input file buffer
local val = patch_getbyte(200)
dbg("val inside of lua",val)

-- patch_getfilesize will return the filesize of the input buffer
local filesize = patch_getfilesize()
dbg("filesize we are patching",filesize)

-- patch_hello - just making sure things work
dbg("check we can talk to c")
patch_hello()

dbg("----------------")
-- patch_setbyte(index,value) = will set the value of the byte at position index
-- this will only change the buffer in memory
patch_setbyte(0,2)

-- patch_writefile will write the file back to disk, the original input file is
-- left untouched
patch_writefile("testing")
dbg("patcher.lua finished")

