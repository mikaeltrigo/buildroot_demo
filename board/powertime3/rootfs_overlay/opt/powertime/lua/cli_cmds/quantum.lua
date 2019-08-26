---------------------------------------------------------------------------------------------------
-- LUA:  debug quantum
--
--   quantum.lua
--   =========
--   
--
-- HISTORY:
--   Date         Author  Description
--   2019-02-12    mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = {"quantum", "qt"}
--
local help = {
    desc = "Quantum access for Debug>",
    args = {
              {"test",  "test to apply : 1 : info 2: start rolling time"},
              {"<cnt>", "optional number of registers to be read"},
           },
    ret = {
              {"resStr", "printable string containing the read data"},
              {"rdat"  , "read data array"}
          },
    eg = {
            {"qt 1", "status of quantum"}
         }
}
--
require "utility"
local function exec(args)
    assert(args and #args == 1 or #args == 2, "ERROR: invalid number of arguments")
    --
  local errCnt = 0 
    local test = assert(tonumber(args[1]), "ERROR: invalid address " .. tostring(args[1]))
	local readArray = {}
	local readArray2 = {}
	if test == 1 then
		errCnt,readArray = FpgaReadRegqt(c_FPGA_version[1],1)
		LOG_Info(string.format("-----  Quantum FPGA version =  %08X []", readArray[1]))
		errCnt,readArray = FpgaReadRegqt(c_CurrentDayTimeh[1],1)
		LOG_Info(string.format("----- c_CurrentDayTimeh:  =  %08X []", readArray[1]))
		errCnt,readArray = FpgaReadRegqt(c_CurrentDayTimel[1],1)
		LOG_Info(string.format("----- c_CurrentDayTimel:  =  %08X []", readArray[1]))
		errCnt,readArray = FpgaReadRegqt(c_InputsState[1],1)
		LOG_Info(string.format("----- c_InputsState:  =  %08X []", readArray[1]))
		errCnt,readArray = FpgaReadRegqt(c_AdInputsStatel[1],1)
		LOG_Info(string.format("----- c_AdInputsStatel:  =  %08X []", readArray[1]))
		errCnt,readArray = FpgaReadRegqt(c_AdInputsStatem[1],1)
		LOG_Info(string.format("----- c_AdInputsStatem:  =  %08X []", readArray[1]))
		errCnt,readArray = FpgaReadRegqt(c_AdInputsStateh[1],1)
		LOG_Info(string.format("----- c_AdInputsStateh:  =  %08X []", readArray[1]))
		
	elseif test == 2 then
		local addr = c_IntervalRollingTime1[1]
		for j=1,16 do
			errCnt,readArray = FpgaReadRegqt(addr,1)
			LOG_Info(string.format("----- c_IntervalRollingTime%d:  =  %08X []", j,readArray[1]))
			addr = addr + 4
		end	
		local addrh = c_RollingTime1h[1]
		local addrl = c_RollingTime1l[1]
		for j=1,16 do
			errCnt,readArray = FpgaReadRegqt(addrl,1)
			errCnt,readArray2 = FpgaReadRegqt(addrh,1)
			LOG_Info(string.format("----- c_RollingTime%dl:  =  %08X []  c_RollingTime%dh:  =  %08X []", j,readArray[1],j,readArray2[1]))
			addrl = addrl + 8	
			addrh = addrh + 8
		end	
		
    elseif test == 3 then
		
	    errCnt = FpgaWriteRegqt(c_IntervalRollingTime2[1],{0x00000064})
		errCnt,readArray = FpgaReadRegqt(c_IntervalRollingTime2[1],1)
		LOG_Info(string.format("----- c_IntervalRollingTime2 set to   %08X []", readArray[1]))
	    
		errCnt = FpgaWriteRegqt(c_ConfigRollingTime2l[1],{0x0000024A})
		errCnt,readArray = FpgaReadRegqt(c_ConfigRollingTime2l[1],1)
		LOG_Info(string.format("-----c_ConfigRollingTime2l set to   %08X []", readArray[1]))	
		errCnt = FpgaWriteRegqt(c_ConfigRollingTime2l[1],{0x0000024A})
		errCnt,readArray = FpgaReadRegqt(c_ConfigRollingTime2l[1],1)
		LOG_Info(string.format("-----c_ConfigRollingTime2l set to   %08X []", readArray[1]))	
		
    elseif test == 4 then
	

		errCnt,readArray = FpgaReadRegqt(c_RollingTimeEvent[1],1)
		LOG_Info(string.format("----- c_RollingTimeEvent:  =  %08X []", readArray[1]))
	    errCnt = FpgaWriteRegqt(c_RollingTimeEvent_Ack[1],{0x00000002})
		LOG_Info(string.format("----- c_RollingTimeEvent_Ack set to 0x00000002 "))
		errCnt,readArray = FpgaReadRegqt(c_RollingTime2l[1],1)
		LOG_Info(string.format("----- c_RollingTime2l =  %08X []", readArray[1]))
		errCnt,readArray = FpgaReadRegqt(c_RollingTime2h[1],1)
		LOG_Info(string.format("----- c_RollingTime2h =  %08X []", readArray[1]))

		
    end
	
	
	
	
    return res, rdat
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec, group = "FPGA"}
