---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
-- ABSTRACT:
--   Chrono in out  control
--
-- HISTORY:
--   Date         Author  Description
--   2019-05-31   mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = { -- command names, will be check by the debug_cli
              "chrono",
              "chr"
            }
--
local help = {
    desc = "Control CHRONO IN/OUT",
    args = {
              {"in", "0: disable chrono in 1: enable chrono in"},
              {"sw", "0: disable CHRONO_SW_EN  1: enable CHRONO_SW_EN "},
              {"muxserialin", "0: disable  1: rs232  2: rx422 3: pulse ( force sw to 1 , must be to work with pulse) "}
           },
    eg = {
            {"chr 1 1  "     , "enables in sw"}
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
	assert(args and #args >2, "ERROR: too few argument arguments")
    local inenb  = assert(tonumber(args[1])  , "ERROR: invalid rwc " .. tostring(args[1]))
    assert(inenb >= 0 and inenb <= 1, "ERROR:  invalid inenb number ")	
    local swenb  = assert(tonumber(args[2])  , "ERROR: invalid rwc " .. tostring(args[1]))
    assert(swenb >= 0 and swenb <= 1, "ERROR:  invalid swenb number ")	
    local muxserialin  = assert(tonumber(args[3])  , "ERROR: invalid rwc " .. tostring(args[1]))
    assert(muxserialin >= 0 and muxserialin <= 3, "ERROR:  invalid swenb number ")		
    errcnt = powertimeFunc.chron_in_ctrl(inenb)
	errcnt = powertimeFunc.chron_sw_ctrl(swenb)
	if  muxserialin == 0 then
		errcnt = powertimeFunc.mux_in_serial_ctrl(0,0)
		print ("PowerTime Chrono disabled ")
	else
		errcnt = powertimeFunc.mux_in_serial_ctrl(1,muxserialin-1)
		if  muxserialin == 1 then
			print ("PowerTime Chrono rs232/PPS enabled ")
		elseif  muxserialin == 2 then
			print ("PowerTime Chrono rs422 enabled ")
		elseif  muxserialin == 3 then
			print ("PowerTime Chrono pulseAB through rj45 enabled ")
		end 
		
	end
	
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
