---  Command line interface
-- @author SwissTiming , Mikael Trigo
-- @license  (c) COPYRIGHT 2018 by Swisstiming Switzerland.  All rights reserved.
-- @script  debug_cli

---------------------------------------------------------------------------------------------------
-- ABSTRACT:
--   debug_cli.lua
--   =========
--   command line interface, debugging tool
--
-- HISTORY:
--   Date         Author  Description
--   2019-02-03   mt      created
--
---------------------------------------------------------------------------------------------------

print(".... starting command line interface:")
--*************************************************************************************************
-- CONFIGURATION
--*************************************************************************************************
local TERM_MODE = {}
local HIST_ENAB = true    -- enable/disable command history (up/down arrow keys)
local HIST_SIZE = 25      -- size of the command history
local PROMPT = "cli: "
local initCmds = {        -- list of commands to be executed at startup
          "restore"
      }
local cmdPath = "cli_cmds"  -- path to the command scripts
--
--*************************************************************************************************
-- Required modules 
--*************************************************************************************************
require "init"
require "utility"
LOG_EnableSyslog(false)
--
-- WELCOME message
local function welcome()
    local msg = "PowerTIme command line:"
    local succ, curFPGAVersion = pcall(fpga_rreg,0x000)
    pcall(function()  -- append lua version
        msg = msg .. string.format("\n    LUA version:  %s", VERSION_AMS_LUA[1])
        end)
    pcall(function()  -- append FPGA version
        msg = msg .. string.format("\n    FPGA version: 0x%04X", curFPGAVersion)
        end)
    pcall(function()  -- version check
            if curFPGAVersion < VERSION_AMS_LUA[2] then
                msg = msg .. string.format(" is to old, expected version: 0x%04X!!!", 
                                            VERSION_AMS_LUA[2])
            end
        end)
    local len = 80
    for i,msg in ipairs(splitString(msg,'\n')) do
        msg = msg .. " "
        while msg:len() < 80 do
            msg = msg .. " "
        end
        print(colorMsg(msg,ANSI_COLORS.CYAN,1,ANSI_COLORS.BLACK))
    end    
    print()
end
---------------------------------------------------------------------------------------------------
-- Logging functions...
---------------------------------------------------------------------------------------------------
ANSI_COLORS = {
          BLACK   = 0,
          RED     = 1,
          GREEN   = 2,
          YELLOW  = 3,
          BLUE    = 4,
          MAGENTA = 5,
          CYAN    = 6,
          GRAY    = 7
      }
--
local function escColor(forground, bold, background)
    local code = "\27["
    if bold == 1 then code = code .. "1;"
    else              code = code .. "0;" end
    code = code .. (30+forground)
    if background ~= nil then
        code = code .. ";" .. (40+background)
    end
    return code .. "m"
end
local function escColorReset()
    return "\27[0m"
end
--
function colorMsg(msg, fore, bold, back)
    return escColor(fore, bold, back) .. tostring(msg) .. escColorReset()
end
--
function errorMsg(msg)
    return "\07" .. colorMsg(msg, ANSI_COLORS.RED, 1, ANSI_COLORS.BLACK)
end
--
function okMsg(msg)
    return colorMsg(msg, ANSI_COLORS.GREEN, 1)
end
--
function warnMsg(msg)
    return colorMsg(msg, ANSI_COLORS.YELLOW, 1)
end
--
function LogError(msg)
    print(errorMsg(msg))
end
function LogOk(msg)
    print(okMsg(msg))
end
function LogWarn(msg)
    print(warnMsg(msg))
end
function LogInfo(msg,fore,bold,back)
    if fore == nil then
        print(msg)
    else
        print(colorMsg(msg,fore,bold,back))
    end
end 
--
---------------------------------------------------------------------------------------------------
-- common debug utility function to be used by commands...
---------------------------------------------------------------------------------------------------
--
-- waits on key press and returns the key code
function getch_unix()
    os.execute("stty cbreak </dev/tty >/dev/tty 2>&1")
    local key = io.read(1)
    os.execute("stty -cbreak </dev/tty >/dev/tty 2>&1")
    return key
end
--
-- trims the trailing and leading white spaces from a string
function trimString(str)
    -- trim leading white characters...
    local lead=1
    for c in str:gmatch"." do
        if c < '!' or c > '~' then
            lead = lead + 1
        else 
            break
        end
    end
    str = string.sub(str,lead)
    -- trim trailing...
    local strLen = #str
    for j=0,#str-1 do
        local c = str:sub(#str-j,#str-j)
        if c < '!' or c > '~' then
            strLen = strLen - 1
        else 
            -- print("no whitespace @ j " .. c)
            break
        end
    end
    str = str:sub(1,strLen)
    return str
end
--
-- Splits a string by a given delimiter and returns them as an array...
--    cString: string to be split
--    delim:   delimiter
local function _splitString(cString, delim)
    local delInd = 1
    local index = 1
    local strs = {}
    while true do
        local nextDelim = string.find(cString,delim,delInd)
        local subStr = string.sub(cString, delInd, nextDelim and nextDelim-1 or #cString)
        if subStr:len() > 0 then
            strs[#strs+1] = subStr
        end
        if nextDelim == nil then
            break
        else
            delInd = nextDelim + string.len(delim)
        end
        index = index + 1
    end
    return strs
end
function splitString(cString, delim)
    local succ,res = pcall(_splitString, cString, delim)
    if not succ then
        res = nil
    end
    return res
end
--
-- waits on key press and returns the key code
function getch_unix(nonblocking)
    local curSTTY = io.popen("stty -g")
    curSTTY = curSTTY:read("*all")
    local sttyOpt = "-echo -icanon -icrnl time 0 min 0 "
    if nonblocking == nil or nonblocking == false then
        sttyOpt = "cbreak </dev/tty >/dev/tty 2>&1"
    end
    --
    os.execute("stty " .. sttyOpt)
    local key = io.read(1)
    os.execute("stty " .. curSTTY)
    return key
end
--
function printResult(result)
    if result == 0 then
        print("\27[1;32m----- OK -----\27[0m")
    elseif result == nil then
        print("\27[1;33m----- result is nil\27[0m")
    else
        print("\27[1;31m----- error code = " .. resolveConstant(ERROR_CODES, result) .. "\27[0m")
    end
end
--
function formatValue(val, f)
    local str = ""
    if f == nil then
        local dec = val
        if band(0x8000,val) == 0x8000 then
            dec = val - 0x10000
        end
        str = string.format("0x%04X, %6s",val,dec)
    end
    return str
end
--
--
---------------------------------------------------------------------------------------------------
-- local miscellaneous functions
---------------------------------------------------------------------------------------------------
--    
-- Prints a string with a specific indent. If the string contains multiple lines, each line will
-- use the indent...
--  str:    string to be printed 
--  indent: indent to be used
--  fore:   optional foreground color (see ANSI_COLORS)
--  bold:   optional bold, 0 or 1
--  back:   optional background color (see ANSI_COLORS)
--
local globIndent=3
function printIndent(str,indent, fore, bold, back)
    local printLine = print
    if fore ~= nil then
        printLine = function(msg)
            print(colorMsg(msg, fore, bold, back))
        end
    end
    --
    if str == nil then
        print() -- new line
        return
    end
    local lines = splitString(str, "\n")
    if lines then
        local idStr = ""
        if indent ~= nil then
            globIndent = indent
        end    
        for i=1,globIndent do
            idStr = idStr .. " "
        end
        for i=1,#lines do
            printLine(idStr .. lines[i])
        end
    end
end
---------------------------------------------------------------------------------------------------
-- Command access function...
---------------------------------------------------------------------------------------------------
local cmds = {}
---------------------------------------------------------------------------------------------------
-- Get one of the registerd commands by its name...
--  command: command name 
--  returns the command 
function getCmd(command)
    for i,c in ipairs(cmds) do
        if c.cmd == command then
            return c
        elseif type(c.cmd) == "table" then
            for j,s in ipairs(c.cmd) do
                if s == command then
                    return c
                end
            end
        end
    end
end
--
-- executes the command:
--  command:  command name,
--  args:     a table containing all arguments to be passed to the command 
--  returns the return value of the commands execution function
function execCmd(command, args)
    local cmd = getCmd(command)
    if cmd ~= nil then
        return cmd.exec(args)
    else
        error("ERROR: Command " .. tostring(command) .. " not found")
    end
end
--
---------------------------------------------------------------------------------------------------
-- load commands:
---------------------------------------------------------------------------------------------------
local function loadCommands()
    -- reload:
    if cmds ~= nil and #cmds > 2 then
        print("reload commands:")
        local pCnt = 0
        for i,p in pairs(package.loaded) do
            pCnt = pCnt + 1
        end
        for i=3,#cmds do
            package.loaded[cmds[i].modName] = nil
        end
        for i,p in pairs(package.loaded) do
            pCnt = pCnt - 1
        end
        print(pCnt .. " modules removed")
        while #cmds > 2 do
            table.remove(cmds, #cmds)
        end
    end
    --
    local f = io.popen("ls " .. cmdPath .. "/*.lua") 
    local errMsg
    local totalCmdCnt = 0
    local loadedCmdCnt = 0
    for cmd in f:lines() do 
        local modName = string.sub(cmd,1,-5)
        -- print(cmd)
        local succ, cmd = pcall(require, modName) 
        if not succ then
            totalCmdCnt = totalCmdCnt + 1
            if errMsg == nil then
                errMsg = tostring(cmd)
            else
                errMsg = errMsg .. "\n" .. tostring(cmd)
            end
        else
            cmd.modName = modName
            if cmd ~= nil and cmd.cmd ~= nil then
                cmds[#cmds+1] = cmd
                totalCmdCnt = totalCmdCnt + 1
                loadedCmdCnt = loadedCmdCnt + 1
            elseif type(cmd) == "table" and cmd.cmd == nil then -- may by multiple commands
                for i,c in ipairs(cmd) do
                    if c.cmd ~= nil then
                        cmds[#cmds+1] = c
                        totalCmdCnt = totalCmdCnt + 1
                        loadedCmdCnt = loadedCmdCnt + 1
                    end    
                end
            end
        end
    end
    printIndent(string.format(".... %d/%d commands loaded",loadedCmdCnt,totalCmdCnt),nil,
                ANSI_COLORS.GREEN,1,ANSI_COLORS.BLACK)
    if loadedCmdCnt < totalCmdCnt then
        printIndent(string.format(".... %d FAILED!!!",totalCmdCnt-loadedCmdCnt),nil,
                    ANSI_COLORS.RED,1,ANSI_COLORS.BLACK)
    end
    print()
    return errMsg
end
local loadErr = loadCommands()
if loadErr ~= nil then
    print(loadErr)
end
--
---------------------------------------------------------------------------------------------------
-- HELP
---------------------------------------------------------------------------------------------------
local function ignoreCaseSort(a,b)
    local s1,s2 = a,b
    if type(a) == 'string' then
        s1 = a:lower()
    end
    if type(b) == 'string' then
        s2 = b:lower()
    end
    return s1 < s2
end
--
-- Gets all available commands group in a table
local function getCommandGroups()
    local cmdGroups = {
              general = {}
          }
    for _,c in ipairs(cmds) do
        local cmdStr = {c.cmd}
        if type(c.cmd) == "table" then
            cmdStr = {}
            for i,s in ipairs(c.cmd) do
                table.insert(cmdStr,s)
            end
        end
        if not c.help or not c.group then
            table.insert(cmdGroups.general, cmdStr)
        else
            local groupKey = tostring(c.group)
            if not cmdGroups[groupKey] then
                cmdGroups[groupKey] = {}
            end
            table.insert(cmdGroups[groupKey], cmdStr)
        end
    end
    --
    -- equalize length of the commands inside their group
    local eqLenGroups = {}
    for gN,g in pairs(cmdGroups) do
        local len = {}
        for _,cmds in ipairs(g) do
            for i,c in ipairs(cmds) do
                if not len[i] then
                    len[i] = string.len(c)
                else
                    len[i] = math.max(len[i], string.len(c))
                end
            end
        end
        for _,cmds in ipairs(g) do
            local cmdStr
            for i,c in ipairs(cmds) do
                local cStr = c
                while string.len(c) < len[i] do
                    c = c .. " "
                end
                if not cmdStr then
                    cmdStr = c
                else
                    cmdStr = cmdStr .. " | " .. c
                end
            end
            if not eqLenGroups[gN] then
                eqLenGroups[gN] = {}
            end
            table.insert(eqLenGroups[gN],cmdStr)
        end  
    end
    --
    return eqLenGroups
end
--    
-- List all available commands. Used if help is called without a specific command...
local function listCommands(grp)
    print(".... available commands:")
    if not grp then
        print("    <<< | exit : exits this program")
    end
    --
    -- sort command groups
    local cmdGroups = getCommandGroups()
    if grp then
        if not cmdGroups[grp] then
            LogError("ERROR: command groups " .. tostring(grp) .. " does not exists")
            return
        else
            local cGrp = cmdGroups[grp]
            cmdGroups = {}
            cmdGroups[grp] = cGrp
        end
    end
    local groups = {}
    for key,val in pairs(cmdGroups) do
        if val ~= cmdGroups.general then
            table.insert(groups, key)
        end
    end
    --
    -- create help
    local groupPref = "    -- "
    local helpMsg = {}
    table.sort(groups, ignoreCaseSort)
    for _, key in ipairs(groups) do
        local gName = groupPref .. key:gsub("^%s*(.-)%s*$", "%1") .. " "
        table.insert(helpMsg, gName)
        local gCmds = cmdGroups[key]
        table.sort(gCmds, ignoreCaseSort)
        for _,cmd in ipairs(gCmds) do
            table.insert(helpMsg, "       " .. cmd)
        end
    end
    -- add general commands
    if cmdGroups.general and #cmdGroups.general > 0 then
        if #helpMsg > 0 then
            table.insert(helpMsg, groupPref)
        end
        table.sort(cmdGroups.general, ignoreCaseSort)
        for _,cmd in ipairs(cmdGroups.general) do
            table.insert(helpMsg, "       " .. cmd)
        end
    end
    local gLen = 50
    for _,str in ipairs(helpMsg) do
        if str:sub(1,groupPref:len()) == groupPref then
            gLen = math.max(gLen, str:len())
        end
    end
    for i,str in ipairs(helpMsg) do
        if str == groupPref then
            helpMsg[i] = helpMsg[i]:sub(1,groupPref:len()-1)
            while(helpMsg[i]:len() < gLen) do
                helpMsg[i] = helpMsg[i] .. "-"
            end
        elseif str:sub(1,groupPref:len()) == groupPref then
            while(helpMsg[i]:len() < gLen) do
                helpMsg[i] = helpMsg[i] .. "-"
            end
        end
    end
    --
    for _,str in ipairs(helpMsg) do
        print(str)
    end
    print()
    print("use help COMMAND for command specific help")
end
--
-- Displays the help of specific command...
--  help:     help structure of the command,
--  cmdName:  command name
local function printHelp(help, cmdName)
    print()
    local desc = help.desc
    if help.desc == nil then
        desc = tostring(cmdName)
    end
    LogInfo("   " .. desc .. ":", ANSI_COLORS.MAGENTA,1)
    io.write("   ")
    local underLnLen = -1
    for i,s in ipairs(splitString(desc,"\n")) do
        underLnLen = math.max(underLnLen,s:len())
    end
    if underLnLen < 1 then
        underLnLen = string.len(desc)
    end
    for i=1,underLnLen+1 do
        io.write("-")
    end
    print()
    if help.args ~= nil then
        LogInfo("   arguments: ")
        local ind = 0
        for i,a in ipairs(help.args) do
            ind = math.max(ind, string.len(a[1]))
        end
        ind = "%" .. (-ind - 4) .. "s"
        for i,a in ipairs(help.args) do
            local desc = splitString(a[2],"\n")
            LogInfo("      " .. string.format(ind .. "%s", a[1],colorMsg(desc[1] .. ": ", ANSI_COLORS.MAGENTA))) 
            for i=2,#desc do
                LogInfo("      " .. string.format(ind .. "  %s", "",desc[i]), ANSI_COLORS.MAGENTA) 
            end
        end
    end
    if help.ret ~= nil then
        LogInfo("   returns: ")
        local ind = 0
        for i,a in ipairs(help.ret) do
            ind = math.max(ind, string.len(a[1]))
        end
        ind = "%" .. (-ind - 4) .. "s"
        for i,a in ipairs(help.ret) do
            LogInfo("      " .. string.format(ind .. ": %s", a[1],a[2])) 
        end
    end
    if help.eg ~= nil then
        for i,eg in ipairs(help.eg) do
            LogInfo("    eg " .. i .. ": " .. eg[2], ANSI_COLORS.CYAN)
            LogInfo("         " .. eg[1])
        end
    end
end     
--
---------------------------------------------------------------------------------------------------
-- Add global commands
---------------------------------------------------------------------------------------------------
--
-- register help command...
local helpCmd = { 
    cmd = "help", 
    exec = function(args) 
                if #args == 0 then
                    listCommands()
                elseif args[1] == "-g" then
                    if not args[2] then
                        local cmdGroups = {}
                        for key,val in pairs(getCommandGroups()) do
                            if key ~= "general" then
                                table.insert(cmdGroups, key)
                            end
                        end
                        table.sort(cmdGroups, ignoreCaseSort)
                        print(".... available command groups:")
                        for _,grp in ipairs(cmdGroups) do
                            print("   " .. grp)
                        end
                    else
                        listCommands(args[2])
                    end
                else
                    local cmd = getCmd(args[1])
                    if cmd ~= nil then
                        if cmd.help == nil then
                            LogWarn("   no help available for " .. args[1])
                        else
                            printHelp(cmd.help, args[1])
                        end
                    else
                        LogError("ERROR: command " .. tostring(args[1]) .. " does not exists")
                    end
                end
            end
}
--
-- register reload command...
local reloadCmd = { 
    cmd = "reload", 
    help = {
            desc = "reloads the commands or a specific module: reload <mod>",
            args = {
                      {"<mod>", "optional name of the module to be reloaded, if not specified all commands are reloaded"}
                   }
        },
    exec = function(args) 
                if args ~= nil and #args > 1 then
                    error("ERROR: Invalid arguments")
                end
                if args ~= nil and #args == 1 then
                    local modName = args[1] 
                    if package.loaded[modName] == nil then
                        error("ERROR: Module " .. modName .. " not found!")
                    else
                        package.loaded[modName] = nil
                        local succ, module = pcall(require, modName) 
                        if not succ then
                            error(module)
                            for i,cmd in ipairs(cmds) do
                                if cmd.modName == modName then
                                    table.remove(cmds,i)
                                    break
                                end
                            end
                        elseif module ~= nil and type(module) == "table" and module.cmd ~= nil then
                            for i,cmd in ipairs(cmds) do
                                if cmd.cmd == module.cmd then
                                    return
                                end
                            end
                            table.insert(cmds, module)
                        end
                    end
                else
                    return loadCommands()
                end
            end
}
table.insert(cmds, 1, helpCmd)
table.insert(cmds, 1, reloadCmd)
--
---------------------------------------------------------------------------------------------------
-- HISTORY
---------------------------------------------------------------------------------------------------
--
-- Set the current terminal mode, used to process escape sequences...
local function setTermMode(mode)
    if mode == nil then
        local tp = io.popen("echo $TERM")
        mode = (tp:read('*all')):gsub("^%s*(.-)%s*$", "%1")
    end
    TERM_MODE = {}
    if mode == "xterm" then
        TERM_MODE.xterm = true
    elseif mode == "linux" then
        TERM_MODE.linux = true
    else
        mode = mode .. " (UNKNOWN)"
    end
    LogInfo("Terminal Mode: " .. mode)
end
--
local history = {}
local hInd = 0
--
-- process escape sequence...
--  cmd: current command line
local function escSeq(cmd)
    -- 
    -- decode escape sequence...
    local k = getch_unix()
    if k == "[" then  -- still valid
        k = getch_unix()
    end
    --
    -- remove escape characters...
    local esc = k
    if TERM_MODE.linux then
        if k == "A" then  -- up arrow
            io.write(string.char(0x1B) .. "[B") -- move cursor back down
        end
    elseif TERM_MODE.xterm then
        io.write("\b\b\b\b    \b\b\b\b")
    end
    --
    -- process history command...
    local histCmd = true
    if k == "A" then
        if hInd <= 1 then
            hInd = #history
        else
            hInd = hInd - 1
        end
    elseif k == "B" then
        if hInd < #history then
            hInd = hInd + 1
        else
            hInd = 1
        end
    else
        histCmd = false
    end
    if histCmd then
        cmd = history[hInd]
    end
    --
    return histCmd, cmd
end
--
-- reads a line character by character and processing escape sequence for history control...
local addH = false
local function readLineCharByChar()
    local k = getch_unix()
    local c = string.byte(k)  -- ASCII code of k
    local cmdStr = ""
    while true do -- until ENTER is pressed
        if cmdStr == nil then cmdStr = "" end
        if c == 0x0A then
            break
        end
        --
        if c >= string.byte(" ") and c <= string.byte("~") then -- glyph
            cmdStr = cmdStr .. k
            addH = true
        else -- control character
            if c == string.byte("\b") then  -- back space
                if string.len(cmdStr) > 0 then
                    addH = true
                    cmdStr = string.sub(cmdStr,1,-2)
                    io.write("\b\b\b   \b\b\b")
                else
                    io.write("\b\b  \b\b")
                end
            elseif c == 127 then
                if string.len(cmdStr) < 1 then
                    io.write(" ")
                else
                    cmdStr = string.sub(cmdStr,1,-2)
                end
                -- print("del")
            elseif c == 0x1B then -- ESC
                local oldLen = string.len(cmdStr)
                addH, cmdStr = escSeq(cmdStr)
                for i=1,oldLen do
                    io.write("\b")
                end
                if cmdStr ~= nil then
                    io.write(cmdStr)
                    if string.len(cmdStr) < oldLen then
                        local seq = {" ","\b"}
                        for j,clrCh in ipairs(seq) do
                            for i=1,(oldLen-string.len(cmdStr)) do
                                io.write(clrCh)
                            end
                        end
                    end
                else
                    local seq = {" ","\b"}
                    for j,clrCh in ipairs(seq) do
                        for i=1,oldLen do
                            io.write(clrCh)
                        end
                    end
                end
            else  -- unknown
                io.write(string.format("|%02X[%s[%d|",c,k,string.len(k))) 
            end
            io.flush()
        end
        -- get next character
        k = getch_unix()
        c = string.byte(k)
    end
    --
    if addH then
        if #history == HIST_SIZE then 
            table.remove(history,1)
        end
        history[#history+1] = cmdStr
        hInd = 0
    end
    return cmdStr
end
--
--*************************************************************************************************
-- parameters
--*************************************************************************************************
local params = {...}
local skip = 0
local term
local run = true
for i,p in ipairs(params) do
    if skip == 0 then
        if p == "-r" then -- remove all initial commands
            initCmds = {}
        elseif p == "-h" then
            LogWarn("Disable History")
            HIST_ENAB = false
        elseif string.sub(p,1,2) == "-t" then
            term = params[i+1]
            skip = 1
        elseif string.sub(p,1,2) == "-c" then
            run = false
            table.insert(initCmds, params[i+1])
            skip = 1
        end
    else
        skip = skip - 1
    end
end
setTermMode(term)
--
-- choose read line method depending on history...
local readLine = readLineCharByChar   -- default
if not HIST_ENAB then
    -- history is disable, use regular io method
    readLine = function() 
                    return io.read("*l")
               end
end
if run then
    welcome()
end
---------------------------------------------------------------------------------------------------
-- main loop
---------------------------------------------------------------------------------------------------
while true do
    --
    -- get input...
    local cmdInput = ""
    if #initCmds > 0 then   -- process initial commands
        cmdInput = initCmds[1]
        table.remove(initCmds,1)
        print("execute " .. cmdInput)
    elseif not run then
        os.exit(0)
    else
        -- prompt...
        io.write(PROMPT)
        cmdInput = readLine()
    end
    --
    -- extract command name and arguments from command input...
    local command
    local args = {}
    if cmdInput ~= nil and string.len(cmdInput) > 0 then
        --
        -- extract arguments...
        command = (cmdInput:gsub("^%s*(.-)%s*$", "%1"))
        if string.len(command) > 0 then
            for k in command:gmatch("%S+") do
                args[#args+1] = k
            end
            command = args[1]
            table.remove(args,1)
        end
    end
    --
    -- execute command...
    if command == nil then  -- skip
    elseif command == "<<<" or command == "exit" then
        break
    else
        local cmd = getCmd(command)
        if cmd == nil then
            LogError("ERROR: command " .. tostring(command) .. " not found!")
            print()
        else
            local cmdSucc, cmdRes = pcall(cmd.exec, args)
            if run then
                if not cmdSucc then
                    -- local errMsg = "ERROR: command failed:\n"
                    -- for i,res in ipairs(splitString(cmdRes,"\n")) do
                        
                    LogError("ERROR: command failed:\n   " .. tostring(cmdRes))
                elseif cmdRes == nil then
                    LogOk("----- OK -----")
                elseif type(cmdRes) == "table" then
                    LogOk("----- OK -----")
                    for i=1,#cmdRes do
                        printIndent(cmdRes[i],3, ANSI_COLORS.CYAN)
                    end
                else
                    printIndent(cmdRes,3)
                end
                print()
            end
        end
    end
end
--
print(".... exit command line interface")
print()
