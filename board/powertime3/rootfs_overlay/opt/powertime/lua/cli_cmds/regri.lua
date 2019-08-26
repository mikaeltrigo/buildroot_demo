---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
--   regri.lua
--   =========
--   command to read an FPGA register
--
-- HISTORY:
--   Date         Author  Description
--   2019-02-12    mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = {"reg_ri", "regri"}
--
local help = {
    desc = "FPGA register read access: regri addr <cnt>",
    args = {
              {"addr",  "register address"},
              {"<cnt>", "optional number of registers to be read"},
           },
    ret = {
              {"resStr", "printable string containing the read data"},
              {"rdat"  , "read data array"}
          },
    eg = {
            {"regri 0x014 2", "read register 0x014 and 0x016"}
         }
}
--
require "utility"
local function exec(args)
    assert(args and #args == 1 or #args == 2, "ERROR: invalid number of arguments")
    --
    local addr = assert(tonumber(args[1]), "ERROR: invalid address " .. tostring(args[1]))
    local cnt  = 1
    if #args == 2 then
        cnt = assert(tonumber(args[2]), "ERROR: invalid amount " .. tostring(args[2]))
    end 
    local res,rdat = FpgaReadReg(addr,cnt)
    if res ~= 0 then
        res = "ERROR: FPGA access has failed, reading register " .. string.format("0x%04X",addr)
    else
        res = {}
        for i=1,#rdat do
            res[i] = string.format("[0x%04X] = 0x%08X, %10s",addr,rdat[i],tostring(rdat[i]))
            addr = addr + 4
        end
    end
    return res, rdat
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec, group = "FPGA"}
