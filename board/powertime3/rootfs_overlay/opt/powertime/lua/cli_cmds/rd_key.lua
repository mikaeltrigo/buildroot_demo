---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
-- ABSTRACT:
--  read keyboard
--
-- HISTORY:
--   Date         Author  Description
--   2019-05-29   mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = { -- command names, will be check by the debug_cli
              "rkey"
              --...
            }
--
local help = {
    desc = "read keyboard and see if a buttin is pressed",
    args = {
             -- {"ARG1_NAME", "DESCRIPTION"},
              --{"ARG2_NAME", "DESCRIPTION"}
              --...
           },
    eg = {
            {"rdarg "     , "return if a key is found and which one"}
              --...
         }
}
--
-- require "mod1"
---------------------------------------------------------------------------------------------------
-- command execution method...
local function exec(args)
    local data = {}
	local returndata1,returndata2
	errcnt,returndata1,returndata2 = powertimeFunc.read_keyboard()
	if returndata1 then
		LOG_Info(string.format("   A KEY HAS BEEN pressed : key pressed: %02x ", returndata2))
	else
		LOG_Info(string.format("   NO keyboard event: last  key pressed: %02x ", returndata2))
	end 
	errcnt,returndata1 = powertimeFunc.get_autokeydetect()
	if returndata1 == false then
		LOG_Info(string.format("   ATTENTION AUTO DETECT KEY is  disabled"))
	end 
	
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
