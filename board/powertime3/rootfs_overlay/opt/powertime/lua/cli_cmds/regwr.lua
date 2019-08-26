---------------------------------------------------------------------------------------------------
-- LUA: AMS debug cli command
--
--   regwr.lua
--   =========
--   command to write an FPGA register
--
--
-- HISTORY:
--   Date         Author  Description
--   2019-02-12    mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = {"reg_wr", "regwr"}
local help = {
    desc = "FPGA register write access",
    args = {
              {"addr", "register address"},
              {"dat", "data to be written"},
              {"<dat1 <dat2 <...>>>", "optional additional data"}
           },
    eg = {
            {"regwr 0x014 0xCAFE"       , "writes 0xCAFE to register 0x013"},
            {"regwr 0x002 0x0001 0x0002", "writes 0x0001 to register 0x001 and 0x0002 to the next register"}
         }
}
--
require "utility"
---------------------------------------------------------------------------------------------------
-- command execution method...
local function exec(args)
    local addr
    local data = {}
    assert(args and #args > 1, "ERROR too few arguments!")
    for i=1,#args do
        local arg = tonumber(args[i])
        if arg == nil then
            error("ERROR invalid argument (" .. i .. "): " .. tostring(args[i]))
        elseif i == 1 then
            addr = arg
        else
            data[i-1] = arg
        end
    end

    local res = FpgaWriteReg(addr,data)
    if res ~= 0 then
        return res
    end

end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec, group = "FPGA"}
