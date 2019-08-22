-- (c) COPYRIGHT 2019 by Swisstiming, Switzerland.  All rights reserved.
--
-- LUA:  log methods
--
-- ABSTRACT:
--  Contains log methods used in the lua scripts
--
-- HISTORY:
--  Date        Author      Description
--  2019-02-10  mt          created

local hasSyslog,syslog = pcall(require,"syslog")

logToSyslog = false
logToConsole = true
function LOG_EnableSyslog(disableConsole)
    if disableConsole == nil or disableConsole == true then
        logToConsole = false
    else
        logToConsole = true 
    end
    if hasSyslog then
        logToSyslog = true
        return 0
    else
        return 1
    end
end

function LOG_Error(message)
    if logToSyslog then
        syslog.syslog("LOG_ERR", message)
    end
    if logToConsole then
        print (message)
    end
end
function LOG_Debug(message)
    if logToSyslog then
        syslog.syslog("LOG_DEBUG", message)
    end
    if logToConsole then
        print (message)
    end
end
function LOG_Notice(message)
    if logToSyslog then
        syslog.syslog("LOG_NOTICE", message)
    end
    if logToConsole then
        print (message)
    end
end
function LOG_Warning(message)
    if logToSyslog then
        syslog.syslog("LOG_WARNING", message)
    end
    if logToConsole then
        print (message)
    end
end
function LOG_Info(message, notLogMessage)
    if notLogMessage == nil then notLogMessage =false end
    if logToSyslog and notLogMessage == false then
        syslog.syslog("LOG_INFO", message)
    end
    if logToConsole then
        print (message)
    end
end


module('log',package.seeall)
