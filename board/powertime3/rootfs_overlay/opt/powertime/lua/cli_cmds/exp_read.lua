---------------------------------------------------------------------------------------------------
-- LUA:  debug cli command
--
-- ABSTRACT:
--   <description>
--
-- HISTORY:
--   Date         Author  Description
--   2019-05-09   mt      created
--
---------------------------------------------------------------------------------------------------
--
local cmd = { -- command names, will be check by the debug_cli
              "expr",
              --...
            }
--
local help = {
    desc = "readf expander",
    args = {
              {"id", "0: expander 0 with enables , 1: expander 1( clavier) "},
              {"regadress", "register adress of expander to read"}
           },
    eg = {
            {"expwr 0 0x12 "     , "read gpioA and B of id 0"}
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
	assert(args and #args > 1, "ERROR: too few argument arguments")
    local id  = assert(tonumber(args[1])  , "ERROR: invalid axis " .. tostring(args[1]))
    assert(id >= 0 and id < 2, "ERROR:  invalid addr number ")
    local regadress = assert(tonumber(args[2]) , "ERROR: invalid mode " .. tostring(args[2]))
	errcnt,returndata1,returndata2 = powertimeFunc.expander_readvalue(id,regadress)
	LOG_Info(string.format("   expander_readvalue: errcnt %d gpioA=  %02x , gpiob =  %02x", errcnt,returndata1,returndata2))
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
