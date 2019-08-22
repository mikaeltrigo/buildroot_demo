--- Contains utility methods used in the AMS lua scripts
-- @author Swisstiming, Mikael Trigo
-- @license  (c) COPYRIGHT 2019 by Swisstiming AG, Switzerland.  All rights reserved.
-- @script  utility

-- ----------------------------------------------------------------------------------
-- ABSTRACT:
--  Contains utility methods used in the AMS lua scripts
--
-- HISTORY:
--  Date        Author      Description
--   2019-02-09   mt        created   
-- -------------------------------------------------------------------------------------------------

require("fpga_access")
--require("utils")
package.path = '/opt/powertime/lua/common/?.lua;' .. package.path
package.path = package.path .. ';/common/?.lua'
require("log")

------------------------------------------------------------------------------------
-- =================================================================================
-- GLOBAL DEFINITIONS:
-- ---------------------------------------------------------------------------------
band = bit32.band
bor = bit32.bor 
bxor = bit32.bxor
bnot = bit32.bnot
lshift = bit32.lshift
rshift = bit32.rshift
usleep = utils_usleep

      
-- =================================================================================
-- GENERAL PURPOSE FUNCTIONS:
-- ---------------------------------------------------------------------------------
function isint(n)
  if n == 0 then
    return true
  end 
  
  if  n==math.floor(n) then
    return true
  else
    return false
  end
  
end
printf = function(s, ...)
    return io.write(s:format(...))
end

function trunc(x)
    integral, fractional = math.modf(x)
    return integral
end


function saturate(value, min, max)
    return math.min(math.max(value, min), max)
end

function to_signed(value, bitWidth)
    if band(value, lshift(1, bitWidth-1)) == 0 then
        return value
    else
        return value - lshift(1, bitWidth)
    end
end

function setError(err, message)
    if errorsToNbr[err] == nil then
        LOG_Error("UNDEFINED_ERROR".." "..message)
        return errorsToNbr["UNDEFINED_ERROR"]
    else
        if type(message) == "string" then
            LOG_Error("  ERROR: "..err.." "..message)
        end
        return errorsToNbr[err]
    end
end
-- -- sleep in milliseconds
-- function msleep(n)
    -- --utils_usleep(n*1000)
	-- msleep(n * 1000); 
-- end
--
function wait(seconds)
  local start = os.time()
  repeat until os.time() > start + seconds
end


--

function scaleArray(inputArray, coefficient)
    if inputArray == nil then
        LOG_Error("scaledArray's inputArray parameter is nil.")
    elseif coefficient == nil then
        LOG_Error("scaledArray's coefficient parameter is nil.")
    elseif type(inputArray) ~= "table" then
        LOG_Error("scaledArray expects a table.")
    elseif type(coefficient) ~= "number" then
        LOG_Error("scaledArray's coefficient must be a number.")
    end

    local scaledArray = {}

    for key, value in pairs(inputArray) do
        scaledArray[key] = value * coefficient
    end

    return scaledArray
end

-- Because #table sometimes returns 0...
function GetTableSize(table)
    local size, i, v
    
    size = 0
    if table ~= nil then
        for i, v in pairs(table) do
            size = size + 1
        end
    end
    return size
end

function deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[deepcopy(orig_key)] = deepcopy(orig_value)
        end
        setmetatable(copy, deepcopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end


function orderedPairs(t)
    -- Equivalent of the pairs() function on tables. Allows to iterate
    -- in order
    return orderedNext, t, nil
end

function byteToBinString(data)
    -- convert a byte to a binary string
    data = band(0xFF,data)
    local binString
    if band(0x01,data) == 1 then
        binString = "1"
    else
        binString = "0"
    end
    for i = 2,8 do
        data = rshift(data,1)
        if band(0x01,data) == 1 then
            binString = "1" .. binString
        else
            binString = "0" .. binString
        end
    end    
    return binString
end  

function binStringToByte(binString)
  local number = 0
    for i = 1,string.len(binString) do
        if string.sub(binString,i,i) == "1" then
            number = number + 2^(string.len(binString)-i)
        end
    end    
    return number
end

-- Basic PL access
-- ---------------------------------------------------------------------------------
-- Reads one or a certain number of PL registers
--  arguments:
--    - addr: address of the 1st register to be read
--    - size: optional number of consecutive registers to be read (default = 1)
--  return:
--    if size is nil or 1, the register values as a 32-bit signed, 
--    an array with the register values otherwise 
--
function pl_rreg(addr,size)
    fpga_open()
    local rdat = fpga_read(addr, size or 1)
    fpga_close()
    if #rdat == 1 then
        rdat = rdat[1]
    end
    return rdat
end

-- ---------------------------------------------------------------------------------
-- Write a certain number of PL registers
--  arguments:
--    - addr: address of the 1st register to be written
--    - wdat: either a single 32-bit value, or 
--            an array if multiple registers shall be written
--
function pl_wreg(addr,wdat)
  fpga_open()
  fpga_write(addr, type(wdat) == 'table' and wdat or {wdat})
  fpga_close()
end

--
-- Performs a read-modify-write of one or more FPGA registers, this function 
-- expects setMask and clrMask are either both a single bit-mask, or if they are
-- array, they have the same size.
-- Clear has priority over set!
-- Not checks are performed 
--  Arguments:
--    - addr:     address of the 1st register
--    - setMask:  either a 32-bit mask, or an array of 32-bit masks 
--    - clrMask:  either a 32-bit mask, or an array of 32-bit masks 
function pl_mreg(addr, setMask, clrMask)
    local wdat = {}
    fpga_open()
    local rdat = fpga_read(addr, (type(setMask) == 'table') and #setMask or 1)
    if type(setMask) == 'table' then
        if type(rdat) == 'number' then
            rdat = {rdat} -- convert single value to table
        end
        for i=1,#rdat do
            wdat[i] = band(bnot(clrMask[i]),bor(rdat[i],setMask[i]))
        end
    else
        wdat[1] = band(bnot(clrMask),bor(rdat,setMask))
    end
    fpga_write(addr, wdat)
    fpga_close()
end

-- =================================================================================
-- PowerTime SPECIFIC FUNCTIONS:
-- ---------------------------------------------------------------------------------
function InitPowerTime(luaVersion)
    local result, ReadArray
    local errorFlag = 0 --default
    -- check compatibility of lua script and FEoC Version
    LOG_Info("PowerTime Script Version: " .. luaVersion[1])   
    result, ReadArray = FpgaReadReg(0x0000,1)
    if ReadArray[1] < luaVersion[2] then
        LOG_Error("ERROR: FPGA Version " .. string.format("0x%04X", ReadArray[1]) .. " is too old for this lua script version!!!!")
        LOG_Error(" required FPGA Version " .. string.format("0x%04X", luaVersion[2]))
        errorFlag = 1 
    else
        LOG_Info("FPGA Version: " .. string.format("0x%04X", ReadArray[1]))    
    end
	  print ("let's enable QUANTUM for debug in InitPowerTime: ")
	  powertimeFunc.expander_init()
	  msleep(10)
	  errcnt = powertimeFunc.chron_in_ctrl(1)
	  print ("Enable Rs232/PPS ")
	  errcnt = powertimeFunc.mux_in_serial_ctrl(1,0)
	  print ("Enable Autoread keyboard ")
	  errcnt = powertimeFunc.keyboardautoread(1)  
	  
    return errorFlag
end

-- Reads a number of FPGA registers:
--  Arguments:
--    - address:  start address of the register to be read
--    - size:    number of 32-bit values to be read
--  Return:
--    - result:     0 = succeeded, error code otherwiese
--    - readArray:  containing the 32-bit words read from the registers
function FpgaReadReg(address,size,errCnt)
  local result
  local readArray = {}

  if address == nil or size== nil then
      result = setError("FPGA_ACCESS_FAIL" ,  "from: "..debug.getinfo(1, "n").name)
  else
      fpga_open()
      readArray = fpga_read(address, size)
      fpga_close()
      result = 0   -- preliminary!
  end
  if errCnt == nil or errCnt == 0 then 
    return result, readArray
  else
    return errCnt, readArray -- keep last error if detected, do not overwrite it
  end
end
-- Reads a number of FPGA registers on the quantum adress range:
--  Arguments:
--    - address:  start address of the register to be read
--    - size:    number of 32-bit values to be read
--  Return:
--    - result:     0 = succeeded, error code otherwiese
--    - readArray:  containing the 32-bit words read from the registers
function FpgaReadRegqt(address,size,errCnt)
  local result
  local readArray = {}

  if address == nil or size== nil then
      result = setError("FPGA_ACCESS_FAIL" ,  "from: "..debug.getinfo(1, "n").name)
  else
      fpga_open_qt()
      readArray = fpga_read_qt(address, size)
      fpga_close_qt()
      result = 0   -- preliminary!
  end
  if errCnt == nil or errCnt == 0 then 
    return result, readArray
  else
    return errCnt, readArray -- keep last error if detected, do not overwrite it
  end
end
--
-- Writes an array of data into FPGA registers
--  Arguments:
--    - address:    start address of the register to be written
--    - dataArray:  array containing the 32-bit words to be written
--  Return:
--    - result: 0 = succeeded, error code otherwiese
function FpgaWriteReg(address,dataArray,errCnt)
  local result
  if address == nil or dataArray == nil then
      result = setError("FPGA_ACCESS_FAIL" ,  "from: "..debug.getinfo(1, "n").name)
  else
      fpga_open()
      fpga_write(address, dataArray)
      fpga_close()
      result = 0   -- preliminary!
  end
  if errCnt == nil or errCnt == 0 then 
    return result
  else
    return errCnt -- keep last error if detected, do not overwrite it
  end
    
end
-- Writes an array of data into FPGA registers on the quantum adress range
--  Arguments:
--    - address:    start address of the register to be written
--    - dataArray:  array containing the 32-bit words to be written
--  Return:
--    - result: 0 = succeeded, error code otherwiese
function FpgaWriteRegqt(address,dataArray,errCnt)
  local result
  if address == nil or dataArray == nil then
      result = setError("FPGA_ACCESS_FAIL" ,  "from: "..debug.getinfo(1, "n").name)
  else
      fpga_open_qt()
      fpga_write_qt(address, dataArray)
      fpga_close_qt()
      result = 0   -- preliminary!
  end
  if errCnt == nil or errCnt == 0 then 
    return result
  else
    return errCnt -- keep last error if detected, do not overwrite it
  end
    
end
--
-- Performs a read-modify-write of FPGA registers
--  Arguments:
--    - address:  start address of the 1st register
--    - setArray: array containing the 32-bit mask of the bits to be set for each register
--    - clrArray: array containing the 32-bit mask of the bits to be clear for each register
--  Return:
--    - result: 0 = succeeded, error code otherwiese
function FpgaModifyReg(address, setArray, clrArray)
  local size = GetTableSize(setArray)
  local result, readArray, writeArray 
  if size ~= GetTableSize(clrArray) then
      result = setError("FPGA_ACCESS_FAIL" ,  "from: "..debug.getinfo(1, "n").name)
  else
      result, readArray = FpgaReadReg(address, size)
      writeArray = {}
      if result == 0 then
          for i = 1, size do
              writeArray[i] = band(bnot(clrArray[i]), bor(readArray[i], setArray[i]))
              -- LOG_Info(string.format("read data: 0x%08X; clr 0x%08X set 0x%08X => 0x%08X", 
              --                        readArray[i], bnot(clrArray[i]), setArray[i], writeArray[i]))
          end
          result = FpgaWriteReg(address, writeArray)
      end
  end
  return result
end

--
-- writes a number of data into FPGA registers and compares the data against the read back
--  Arguments: 
--    - address:    address of the first register
--    - dataArray:  array containing the 32-bit words to be written
--  Return:
--    - result: -1 on error, else the number of missmatched write data and read back
--
function FpgaWriteRegVerify(address, dataArray)
  if type(dataArray) ~= "table" then
    return -2
  end
  local result = FpgaWriteReg(address, dataArray)
  if result ~= 0 then
    return -1
  end
  
  -- read back
  local readback = {}
  result, readback = FpgaReadReg(address, GetTableSize(dataArray))
  if result ~= 0 then
    return -1
  end
  
  -- check
  local errCnt = 0
  for i,v in ipairs(readback) do
    if dataArray[i] ~= readback[i] then
      print("FpgaWriteRegVerify readback failure at address " ..
      string.format("0x%04X: 0x%04X /= 0x%04X", address+2*(-i), dataArray[i], readback[i]))
      errCnt = errCnt + 1
    end
  end

  if errCnt > 0 then
    print("FpgaWriteRAMVerify detected " .. errCnt .. " failures.")
  end
  
  return errCnt
end

-- reads a number of values from FPGA registers and prints out the results
--  Arguments:
--    - address:  address of the first register
--    - size:   number of 32-bit words to be read
--  Return:
--    - result: 0 if succeeded, an error code otherwise
function FpgaDumpReg(address, size)
  local result, data
  result, data = FpgaReadReg(address, size)
  if result ~= 0 then
    LOG_Error("Error reading FEoC RAM for dump.")
    return result
  end
  print("Register Dump @ " .. string.format("0x%03X", address))
  for i,d in ipairs(data) do
    print(string.format(" 0x%03X: 0x%04X", (address+2*(i-1)), d))
  end
  return 0
end
