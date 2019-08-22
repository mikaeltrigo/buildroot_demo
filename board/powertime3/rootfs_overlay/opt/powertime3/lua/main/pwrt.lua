--- main loop of the lua environement an
-- #!/usr/bin/env lua
-- @author Swisstiming 
-- @license  (c) COPYRIGHT 2019 by Swisstiming, Switzerland.  All rights reserved.
-- @module pwrt

-- Include the common directory into the package path
package.path = package.path .. ';../common/?.lua'
package.path = package.path .. ';../?.lua'
require "utility"
require "init"
--local system = require("system")

function main()
    local readArray = {}


    

    InitPowerTime(VERSION_PWRT_LUA)

end


LOG_EnableSyslog()


LOG_Notice("pwrt.lua Starting program")
main()
