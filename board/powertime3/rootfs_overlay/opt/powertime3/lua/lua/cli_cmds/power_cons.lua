---------------------------------------------------------------------------------------------------
-- LUA: AMS debug cli command
--
-- ABSTRACT:
--   command to test power consumpuition
--
--
-- HISTORY:
--   Date         Author  Description
--   2019-05-29    mt      created
--
---------------------------------------------------------------------------------------------------
--

local cmd = { -- command names, will be check by the debug_cli
              "pc", 
              --...
            }
--
local help = {
    desc = "command t enable disable interface to measure consumpion",
    args = {
              {"cmd", "0 : all off"}
           },
    eg = {
            {"pc 0 "       , "disable all interface"}
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
    local cmd  = assert(tonumber(args[1])  , "ERROR: invalid axis " .. tostring(args[1]))
    assert(cmd >= 0 and cmd < 24, "ERROR:  invalid addr number ")

	if cmd == 0 then
	
		LOG_Info(string.format("   Disable keyboard autoread"))
		errcnt = powertimeFunc.keyboardautoread(0)
		LOG_Info(string.format("   POE OFF "))
		errcnt = powertimeFunc.ext_poe_ctrl(0)
		LOG_Info(string.format("   USB MASS STORAGE  OTG_EN OFF "))
		errcnt = powertimeFunc.ext_usbmasstroage_ctrl(0)
		LOG_Info(string.format("   USB POWER CHARGER OFF USB_PWR_EN_n "))
		errcnt = powertimeFunc.ext_usbcharge_ctrl(0)
		LOG_Info(string.format("   EXTERNAL PHY OFF PHY_EN "))
		errcnt = powertimeFunc.ext_phy_ctrl(0)
		LOG_Info(string.format("   PRITNER OFF "))
		errcnt = powertimeFunc.print_ctrl(0,0)
		LOG_Info(string.format("   MUC IN SERIAL CONTROL DISABLE (MUX_CTRL.ENA = 0  "))
		errcnt = powertimeFunc.mux_in_serial_ctrl(0,0)
		LOG_Info(string.format("  CHRONO SW ENABLE OFF  "))
		errcnt = powertimeFunc.chron_sw_ctrl(0)
		LOG_Info(string.format("  CHRONO INPUT OFF  CHRONO_IN_EN "))
		errcnt = powertimeFunc.chron_in_ctrl(0)
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
