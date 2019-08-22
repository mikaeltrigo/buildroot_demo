---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
-- ABSTRACT:
--   <description>
--
-- HISTORY:
--   Date         Author  Description
--   2019-02-12   mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = { -- command names, will be check by the debug_cli
              "cmd", 
              "CMD"
              --...
            }
--
local help = {
    desc = "Short description of this command",
    args = {
              {"ARG1_NAME", "DESCRIPTION"},
              {"ARG2_NAME", "DESCRIPTION"}
              --...
           },
    eg = {
            {"cmd ARG1"     , "DESCRIPTION"},
            {"cmd ARG1 ARG2", "DESCRIPTION"}
              --...
         }
}
--
-- require "mod1"
---------------------------------------------------------------------------------------------------
-- command execution method...
local function exec(args)
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
