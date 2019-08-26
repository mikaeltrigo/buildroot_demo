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
              {"cmd",  "command"},
              {"<0>",  "all of expect OSC_EN 10MHZ"},
              {"<1>", "OSC enable"},
              {"<2>", "Backlight PWM enable 100/100"},
              {"<3>", "Backlight PWM enable 50/100"},
              {"<4>", "USB MASS STORAGE  OTG_EN "},			  
              {"<5>", "EXTERNAL PHY ON  PHY_EN"},	
              {"<6>", "MUX IN SERIAL CONTROL enable to RS232"},		
              {"<7>", "MUX IN SERIAL CONTROL enable to R422f"},	
              {"<8>", "Printer ON"},	
              {"<10>", "all off"},				  
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
		LOG_Info(string.format("   MUX IN SERIAL CONTROL DISABLE (MUX_CTRL.ENA = 0  "))
		errcnt = powertimeFunc.mux_in_serial_ctrl(0,0)
		LOG_Info(string.format("  CHRONO SW ENABLE OFF  "))
		errcnt = powertimeFunc.chron_sw_ctrl(0)
		LOG_Info(string.format("  CHRONO INPUT OFF  CHRONO_IN_EN "))
		errcnt = powertimeFunc.chron_in_ctrl(0)
		LOG_Info(string.format("  LOCAL 10MHZ : OSC_EN enable "))
		errcnt = powertimeFunc.clk_source_ctrl(0) -- 0 : local 10 MHZ, 1 GPS 10 MHz ( disable also OSC_EN)
		LOG_Info(string.format("  	Backlight PWM disable"))
		errcnt = powertimeFunc.lcdcontrol(0,0)
	elseif cmd == 1 then
		LOG_Info(string.format("  LOCAL 10MHZ : OSC_EN enable "))
		errcnt = powertimeFunc.clk_source_ctrl(0)  -- 0 : local 10 MHZ, 1 GPS 10 MHz ( disable also OSC_EN)
	elseif cmd == 2 then
		LOG_Info(string.format("  	Backlight PWM enable 100/100"))
		errcnt = powertimeFunc.lcdcontrol(100,0)
	elseif cmd == 3 then
		LOG_Info(string.format("  	Backlight PWM enable 50/100"))
		errcnt = powertimeFunc.lcdcontrol(50,0)
	elseif cmd == 4 then
		LOG_Info(string.format("   USB MASS STORAGE  OTG_EN ON "))
		errcnt = powertimeFunc.ext_usbmasstroage_ctrl(1)
	elseif cmd == 5 then
		LOG_Info(string.format("   EXTERNAL PHY ON  PHY_EN "))
		errcnt = powertimeFunc.ext_phy_ctrl(1)
	elseif cmd == 6 then
		LOG_Info(string.format("   MUX IN SERIAL CONTROL enable to RS232  "))
		errcnt = powertimeFunc.mux_in_serial_ctrl(1,0)
	elseif cmd == 7 then	
		LOG_Info(string.format("   MUX IN SERIAL CONTROL enable to RS422  "))
		errcnt = powertimeFunc.mux_in_serial_ctrl(1,1)
	elseif cmd == 8 then	
		LOG_Info(string.format("   PRITNER ON "))
		errcnt = powertimeFunc.print_ctrl(1,1)
	elseif cmd ==  9 then
		local txdata = assert(tonumber(args[3]) , "ERROR: invalid mode " .. tostring(args[3]))
		LOG_Info(string.format("   writting  0x%02x to register 0x%02x ", txdata,addr ))
		errcnt,returndata = powertimeFunc.battery_write_reg(addr,txdata)
		
	elseif cmd ==  10 then
	
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
		LOG_Info(string.format("   MUX IN SERIAL CONTROL DISABLE (MUX_CTRL.ENA = 0  "))
		
		errcnt = powertimeFunc.mux_in_serial_ctrl(0,0)
		LOG_Info(string.format("  CHRONO SW ENABLE OFF  "))
		errcnt = powertimeFunc.chron_sw_ctrl(0)
		LOG_Info(string.format("  CHRONO INPUT OFF  CHRONO_IN_EN "))
		errcnt = powertimeFunc.chron_in_ctrl(0)
		LOG_Info(string.format("  GPS 10MHZ : OSC_EN disable "))
		errcnt = powertimeFunc.clk_source_ctrl(1)-- 0 : local 10 MHZ, 1 GPS 10 MHz ( disable also OSC_EN)
		LOG_Info(string.format("  	Backlight PWM disable"))
		errcnt = powertimeFunc.lcdcontrol(0,0)
	end 
	
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
