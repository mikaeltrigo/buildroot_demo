---------------------------------------------------------------------------------------------------
-- LUA: AMS debug cli command
--
-- ABSTRACT:
--   command to write an FPGA register
--
--
-- HISTORY:
--   Date         Author  Description
--   2019-02-12    mt      created
--
---------------------------------------------------------------------------------------------------
--

local cmd = { -- command names, will be check by the debug_cli
              "test", 
              --...
            }
--
local help = {
    desc = "test function during dec",
    args = {
              {"num", "which funciton to call"}
           },
    eg = {
            {"test 1 0xCAFE"       , "ToDo"}
         }
}
--
require "utility"
---------------------------------------------------------------------------------------------------
-- command execution method...
local function exec(args)
    local addr
    local returndata,returndata1
    local errcnt
    local data = {}
    local arg = tonumber(args[1])
    local arg2 = tonumber(args[2])

end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
