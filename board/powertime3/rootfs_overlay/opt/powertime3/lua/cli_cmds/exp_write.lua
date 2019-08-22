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
              "expw",
              --...
            }
--
local help = {
    desc = "write expander",
    args = {
              {"id", "0: expander 0 with enables , 1: expander 1( clavier) "},
              {"gpioa", "gpio port A tx values"},
              {"gpiob", "gpio port A tx values"}
           },
    eg = {
            {"expw 0 0x1 0x1"     , "write 0x1 in gpioA and gpio B"}
              --...
         }
}
--
-- require "mod1"
---------------------------------------------------------------------------------------------------
-- command execution method...
local function exec(args)
    local data = {}
	assert(args and #args > 2, "ERROR: too few argument arguments")
    local id  = assert(tonumber(args[1])  , "ERROR: invalid axis " .. tostring(args[1]))
    assert(id >= 0 and id < 2, "ERROR:  invalid addr number ")
    local gpioa = assert(tonumber(args[2]) , "ERROR: invalid mode " .. tostring(args[2]))
    local gpiob = assert(tonumber(args[3]) , "ERROR: invalid mode " .. tostring(args[2]))
	errcnt = powertimeFunc.expander_writevalue(id,gpioa,gpiob)
	LOG_Info(string.format("   expander_writevalue: errcnt %d ", errcnt))
end
--
---------------------------------------------------------------------------------------------------
-- return command to be registered by the debug_cli
return {cmd = cmd, help = help, exec = exec}
