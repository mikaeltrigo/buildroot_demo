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
              { "rw", "0 write 1 read , 2 read adc"},
              {"adrr", "adress of the register"},
			   {"txdata", "data to wrote"}
           },
    eg = {
            {"ba 1 0x2 "       , "read register 1 of the battery charger"}
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
	assert(args and #args >= 1, "ERROR: too few argument arguments")
    local rw = assert(tonumber(args[1]) , "ERROR: invalid mode " .. tostring(args[2]))
    assert(rw >= 0 and rw < 4, "ERROR:  invalid rw  number ")	

	if rw == 1 then
	    local addr  = assert(tonumber(args[2])  , "ERROR: invalid axis " .. tostring(args[1]))
		assert(addr >= 0 and addr < 24, "ERROR:  invalid addr number ")
		errcnt,returndata = powertimeFunc.battery_read_reg(addr)
		LOG_Info(string.format("   battery_read_reg: returndata 0x%02x ", returndata))
	elseif rw == 0 then
	    local addr  = assert(tonumber(args[2])  , "ERROR: invalid axis " .. tostring(args[1]))
		assert(addr >= 0 and addr < 24, "ERROR:  invalid addr number ")
		local txdata = assert(tonumber(args[3]) , "ERROR: invalid mode " .. tostring(args[3]))
		LOG_Info(string.format("   writting  0x%02x to register 0x%02x ", txdata,addr ))
		errcnt,returndata = powertimeFunc.battery_write_reg(addr,txdata)	
	else
		errcnt,returndata = powertimeFunc.battery_read_adc()
		LOG_Info(string.format("   battery_read_adc: returndata 0%d ", returndata))
	
	end 
	
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
