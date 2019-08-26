---------------------------------------------------------------------------------------------------
-- LUA: AMS debug cli command
--
-- ABSTRACT:
--   command to test te battery charger access over i2c
--
--
-- HISTORY:
--   Date         Author  Description
--   2019-04-09    mt      created
--
---------------------------------------------------------------------------------------------------
--

local cmd = { -- command names, will be check by the debug_cli
              "ba", 
              --...
            }
--
local help = {
    desc = "command to test te battery charger access over i2c",
    args = {
              {"adrr", "adress of the register"},
              {"rw", "0 write 1 read"},
			   {"txdata", "data to wrote"}
           },
    eg = {
            {"ba 0x2 1"       , "read register 1 of the battery charger"}
         }
}
--
require "utility"
---------------------------------------------------------------------------------------------------
-- command execution method...
local function exec(args)
    local returndata,returndata1
    local errcnt
    local data = {}
	assert(args and #args > 1, "ERROR: too few argument arguments")
    local addr  = assert(tonumber(args[1])  , "ERROR: invalid axis " .. tostring(args[1]))
    assert(addr >= 0 and addr < 24, "ERROR:  invalid addr number ")
    local rw = assert(tonumber(args[2]) , "ERROR: invalid mode " .. tostring(args[2]))
    assert(rw >= 0 and rw < 2, "ERROR:  invalid rw  number ")
	if rw == 1 then
		errcnt,returndata = powertimeFunc.battery_read_reg(addr)
		LOG_Info(string.format("   battery_read_reg: returndata 0x%02x ", returndata))
	else
		local txdata = assert(tonumber(args[3]) , "ERROR: invalid mode " .. tostring(args[3]))
		LOG_Info(string.format("   writting  0x%02x to register 0x%02x ", txdata,addr ))
		errcnt,returndata = powertimeFunc.battery_write_reg(addr,txdata)
	end 
	
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
