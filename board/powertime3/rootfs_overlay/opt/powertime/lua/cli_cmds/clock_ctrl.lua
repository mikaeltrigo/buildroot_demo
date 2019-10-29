---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
-- ABSTRACT:
--   clock DAC control
--
-- HISTORY:
--   Date         Author  Description
--   2019-05-31   mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = { -- command names, will be check by the debug_cli
              "clk"
              --...
            }
--
local help = {
    desc = "Control the DAC that is control voltage of +0MHz generator",
    args = {
              {"rws", "w = 0  write , 1 = read,2= selext 10MHz local 3= select GPS 10MHz, 4 ext clock on GPS OSC_EN still enable"},
              {"cmd", "regisgter number "},
			  {"data", "data to write if rw=0"},
              --...
           },
    eg = {
            {"clk 0 1 0x0201 "     , "write to register 1"}
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
    local rwc  = assert(tonumber(args[1])  , "ERROR: invalid rwc " .. tostring(args[1]))
    assert(rwc >= 0 and rwc <= 4, "ERROR:  invalid addr number ")	
   
   
	if rwc == 0 then
		assert(args and #args > 2, "ERROR: too few argument arguments, needs data to write")
		local cmd = assert(tonumber(args[2]) , "ERROR: invalid cmd " .. tostring(args[2]))
		local datatx = assert(tonumber(args[3]) , "ERROR: invalid datatx " .. tostring(args[2]))
		errcnt, returndata = powertimeFunc.clk_ctrl_dac_wr(cmd,datatx)
	elseif rwc == 1 then
		assert(args and #args > 1, "ERROR: too few argument arguments, needs reg number to read")
		local cmd = assert(tonumber(args[2]) , "ERROR: invalid cmd " .. tostring(args[2]))
		--errcnt, returndata = powertimeFunc.clk_ctrl_dac_rd(cmd)
		--LOG_Info(string.format("   clk_ctrl_dac_rd: errcnt %d , return value = %04x ", errcnt,returndata))
	elseif rwc == 2 then
		errcnt = powertimeFunc.clk_source_ctrl(0)
		LOG_Info(string.format("   clk_source_ctrl select 10MHZ local function return  errcnt %d ", errcnt))
	elseif rwc == 3 then
		errcnt = powertimeFunc.clk_source_ctrl(1)
		LOG_Info(string.format("   clk_source_ctrl select 10MHZ GPS function return  errcnt %d ", errcnt))	
	elseif rwc == 4 then
		errcnt = powertimeFunc.clk_source_ctrl(2)
		LOG_Info(string.format("   clk_source_ctrl select 10MHZ  EXT clocl for debug return  errcnt %d ", errcnt))		
	end 

end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
