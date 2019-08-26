---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
-- ABSTRACT:
--   Monitoring
--
-- HISTORY:
--   Date         Author  Description
--   2019-05-31   mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = { -- command names, will be check by the debug_cli
              "vmon"
              --...
            }
--
local help = {
    desc = "Voltage monitoring",
    args = {
              {"cltr", "0:12V, 1:5V,2_3.3V"}
              --...
           },
    eg = {
            {"vmon 0 "     , "readback 12V value"}
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
	assert(args and #args > 0, "ERROR: too few argument arguments")
    local ctrl  = assert(tonumber(args[1])  , "ERROR: invalid rwc " .. tostring(args[1]))
    assert(ctrl >= 0 and ctrl <= 2, "ERROR:  invalid addr number ")	
    errcnt = powertimeFunc.mux_in_monitoring_ctrl(ctrl)


end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
