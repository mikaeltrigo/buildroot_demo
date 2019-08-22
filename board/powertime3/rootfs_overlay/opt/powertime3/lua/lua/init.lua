---  Contains init function for all scripts with required require("") and path
--   Upon execution of this script, all functions are declared and
--   all scripts are loaded
-- @author SwissTiming , Mikael Trigo
-- @license  (c) COPYRIGHT 2018 by Swisstiming Switzerland.  All rights reserved.
-- @script  init


-- -------------------------------------------------------------------------------------------------
--
-- ABSTRACT:
--   init.lua
--   ========
--   Lua Initialization Script for PowerTime
--   Upon execution of this script, all functions are declared and
--   all scripts are loaded
--
-- -------------------------------------------------------------------------------------------------
--
-- HISTORY:
--                  Version  Date        FPGA-Version    Author     Description
-- -----------------------------------------------------------------------------

VERSION_PWRT_LUA = {"V00.01, 2019-02-13", 0x0001}      -- mt :add more steps for approach, add help function

-- Require any packages here...
package.path = package.path .. ';./?.lua'
package.path = package.path .. ';./common/?.lua'

require("configpkg")
require("errors")
require("utility")
require("system")
require("powertime")
require("msleep")

-- Switches (for debug)
printVerbose = true          -- enable/disable print statements which are mainly used for debugging
print ("PowerTime module loaded LUA version "..VERSION_PWRT_LUA[1])

-- Print lua version
print (_VERSION)
