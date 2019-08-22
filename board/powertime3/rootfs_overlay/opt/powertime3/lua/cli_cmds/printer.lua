---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
-- ABSTRACT:
--   Printer control
--
-- HISTORY:
--   Date         Author  Description
--   2019-05-31   mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = { -- command names, will be check by the debug_cli
              "print"
              --...
            }
--
local help = {
    desc = "Printer contrler",
    args = {
              {"enb", "0:diable 1: enabled"},
              {"cts", "0: RTS disabled 1: RTS Enabled "}
              --...
           },
    eg = {
            {"print 1 1  "     , "Printer enabled and ready to send"}
              --...
         }
}
--
-- require "mod1"
---------------------------------------------------------------------------------------------------
-- command execution method...
local function exec(args)
    local data = {}
	local returndata
	assert(args and #args > 1, "ERROR: too few argument arguments")
    local enb  = assert(tonumber(args[1])  , "ERROR: invalid rwc " .. tostring(args[1]))
    assert(enb >= 0 and enb <= 1, "ERROR:  invalid addr number ")	
    local rts  = assert(tonumber(args[1])  , "ERROR: invalid rwc " .. tostring(args[1]))
    assert(rts >= 0 and rts <= 1, "ERROR:  invalid addr number ")	 
   errcnt = powertimeFunc.print_ctrl(enb,rts)


end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
