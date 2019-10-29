---  Contains all funciton related to the motion controller fpga implementation
-- @author SwissTiming , Mikael Trigo
-- @license  (c) COPYRIGHT 2018 by Swisstiming Switzerland.  All rights reserved.
-- @script  powertime

-- -------------------------------------------------------------------------------------------------
-- ABSTRACT:
-- powertime.lua
-- ===============
--
-- HISTORY:
-- Date Author Description
--   2019-02-09   mt        created   

-- -------------------------------------------------------------------------------------------------
-- ************************************************************************************************
-- Declaration of constants used in the script...
-- ------------------------------------------------------------------------------------------------
local DonotLogMessage = false
-- ************************************************************************************************
-- Public functions ...
-- ------------------------------------------------------------------------------------------------
-- ************************************************************************************************
-- Local functions ...
-- ----
local function GetSscratch(axis)
	local errCnt = 0 

	local readArray = {}
	if axis < 1 or axis > 3 then
		errCnt = setError("AXIS_OUT_OF_RANGE" , "from: "..debug.getinfo(1, "n").name)
	else
	end
	return errCnt
end
-- 
---but est de lire un registre du battery charger :BQ25898DYFFR
-- @within system function
-- @param regaddr [0...21] see datacheet for description
-- @return ErrCnt

local function battery_read_reg(regaddr)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	--bit 17: 0: write 1: read
	-- bit 16: enable transaction
	-- bit 7_0: register adress
	-- bit 15_8 : write value 
	local read_start  = 0x30000
	local read_stop  = 0x00000
	local write_start = 0x10000
	
	errCnt, readArray = FpgaReadReg(i2c_ctrl_c[1], 1, errCnt)
	local busy = band(0x1,rshift(readArray[1],16))
	
	--debug
	if busy == 0x1 then
		errCnt = setError("I2C_BUSY" , "from: "..debug.getinfo(1, "n").name)
	else

		errCnt = FpgaWriteReg(i2c_ctrl_c[1],{bor(read_start,band(0x00FF,regaddr))}, errCnt) 
		msleep(1)
		errCnt, readArray = FpgaReadReg(i2c_ctrl_c[1], 1, errCnt)
		busy = band(0x1,rshift(readArray[1],16))
		
		if busy == 0x1 then
			errCnt = setError("I2C_BUSY" , "from: "..debug.getinfo(1, "n").name)
		end 
			--readback value sent by i2c slave
		errCnt, readArray = FpgaReadReg(i2c_read_c[1], 1, errCnt)
		
		returnvalue = band(0xff, readArray[1])
	end 	
	return errCnt, returnvalue
end
---but est d ecrire  un registre du battery charger :BQ25898DYFFR
-- @within system function
-- @param regaddr [0...21] see datasheet for description
-- @param txvalue  [0...255] see datasheet for description
-- @return ErrCnt

local function battery_write_reg(regaddr,txvalue)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	--bit 17: 0: write 1: read
	-- bit 16: enable transaction
	-- bit 7_0: register adress
	-- bit 15_8 : write value 
	local read_start  = 0x30000
	local write_start = 0x10000
	
	errCnt, readArray = FpgaReadReg(i2c_ctrl_c[1], 1, errCnt)
	local busy = band(0x1,rshift(readArray[1],16))
	
	--debug
	if busy == 0x1 then
		errCnt = setError("I2C_BUSY" , "from: "..debug.getinfo(1, "n").name)
	else
		local temp = lshift(band(txvalue,0xFF),8)
		errCnt = FpgaWriteReg(i2c_ctrl_c[1],{bor(write_start,bor(temp,band(regaddr,0x00FF)))}, errCnt) 

	end 	
	return errCnt
end


local function battery_read_adc()
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local txdata
	local battery_mvolt
	errcnt,returndata = powertimeFunc.battery_read_reg(0x2)--read ADC register
	returndata = band(returndata,0x3f) --celar bit 6 and 7  of REG02
	txdata = bor(returndata,0x40) --enable auto conversion
	errcnt = powertimeFunc.battery_write_reg(0x2,txdata) -- Start ADC Conversion (– One shot ADC conversion )
	msleep(100)
	errcnt,returndata = powertimeFunc.battery_read_reg(0xE)--read ADC register
	returndata = band(returndata,0x7f) --celar bit7
	battery_mvolt= returndata * 20  + 2304 --base is 2.304V

	
	errcnt = powertimeFunc.battery_write_reg(0x2,band(txdata,0x3f)) -- disable auto conversion

	
	return errCnt,battery_mvolt
end


---readout expander
-- @within system function
-- @param id  [0...1] 0: expander with all enable signal , 1 : expander with readout and keyboard
-- @param regaddr if null readout current value of reg, if 0...0x20 read internal register of ecpander
-- @return ErrCnt
-- @return gpioA return value ofgpioA or bit 7 ..0 of register slected
-- @return gpioB return value ofgpioB or bit 15 ..8 of register slected

local function expander_readvalue(id,regaddrr)
	local errCnt = 0 
	local readArray = {}
	local readArraymain = {}
	local returnvalue
	--bit 17: 0: write 1: read
	-- bit 16: enable transaction
	-- bit 7_0: register adress
	-- bit 15_8 : write value 
	local read_start  = 0x30000
	local write_start = 0x10000
	local gpioA = 0x00
	local gpioB = 0x00
	local a = 0
	result, readArraymain = FpgaReadReg(portexp_main_ctrl_c[1], 1, errCnt)
	result =FpgaWriteReg(portexp_main_ctrl_c[1],{bor(readArraymain[1],0x0)})
	msleep(2)
	if regaddrr == null then
		if id == 0 then
			errCnt = FpgaWriteReg(portexp1_ctrl_rd_c[1],{0x01120000}, errCnt) 
			msleep(1)
			result, readArray = FpgaReadReg(portexp1_ctrl_rd_c[1], 1, errCnt)
		else 
			errCnt = FpgaWriteReg(portexp2_ctrl_rd_c[1],{0x01120000}, errCnt) 
			msleep(1)
			result, readArray = FpgaReadReg(portexp2_ctrl_rd_c[1], 1, errCnt)
		end 


	else
		local tmp = lshift(band(regaddrr,0xFF), 16)
   
		if id == 0 then
			errCnt = FpgaWriteReg(portexp1_ctrl_rd_c[1],{bor(0x01000000,tmp)}, errCnt) 
			msleep(1)
			result, readArray = FpgaReadReg(portexp1_ctrl_rd_c[1], 1, errCnt)
		else 
			errCnt = FpgaWriteReg(portexp2_ctrl_rd_c[1],{bor(0x01000000,tmp)}, errCnt) 
			msleep(1)
			result, readArray = FpgaReadReg(portexp2_ctrl_rd_c[1], 1, errCnt)
		end 

	end

	if band(0x1,rshift(readArray[1],26)) == 0x1 then
		errCnt = setError("EXPANDERA_ERROR" , "from: "..debug.getinfo(1, "n").name)
	else
		gpioA = band(0xFF,readArray[1])
		gpioB = band(0xFF,rshift(readArray[1],8))
	end
	result =FpgaWriteReg(portexp_main_ctrl_c[1],{readArraymain[1]})
	return errCnt, gpioA , gpioB
end


---write value out of the expander expander
-- @within system function
-- @param id  [0...1] 0: expander with all enable signal , 1 : expander with readout and keyboard
-- @param regaddr if null readout current value of reg, if 0...0x20 read internal register of ecpander
-- @return ErrCnt
-- @return gpioA return value ofgpioA or bit 7 ..0 of register slected
-- @return gpioB return value ofgpioB or bit 15 ..8 of register slected

local function expander_writevalue(id,gpioA_tx, gpioB_tx)
	local errCnt = 0 
	local readArray = {}
	local returnvalue

	local tmp = lshift(band(gpioB_tx,0xFF), 8)
    if id == 0 then
      errCnt = FpgaWriteReg(portexp1_ctrl_wr_c[1],{bor(tmp,band(gpioA_tx,0xFF))}, errCnt) 
    else 
      errCnt = FpgaWriteReg(portexp2_ctrl_wr_c[1],{bor(tmp,band(gpioA_tx,0xFF))}, errCnt) 
    end
	return errCnt
  
end


--- readback the last value written in the expander id 0 ( with all the enables) 
-- @within system function
-- @return ErrCnt
-- @return gpioA return value ofgpioA or bit 7 ..0 of register slected
-- @return gpioB return value ofgpioB or bit 15 ..8 of register slected

local function expander0_readbacklocal()
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local gpioA = 0x00
	local gpioB = 0x00
	result, readArray = FpgaReadReg(portexp1_ctrl_wr_c[1], 1, errCnt)
	gpioA = band(0xFF,readArray[1])
	gpioB = band(0xFF,rshift(readArray[1],8))
	return errCnt, gpioA , gpioB
  
end

---initialize the expanders with correct input output modes
-- @within system function
-- @return ErrCnt

local function expander_init()
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	--readback and write start init bit
	LOG_Info(string.format("   Init expander"))
	errCnt, readArray = FpgaReadReg(portexp_main_ctrl_c[1], 1, errCnt)
	errCnt =FpgaWriteReg(portexp_main_ctrl_c[1],{bor(readArray[1],0x1)}, errCnt) 
	return errCnt
end
---initialize keyboardautoreads
-- @within system function
-- @param enb =: disable 1 : enable
-- @return ErrCnt

local function keyboardautoread(enb)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	--readback and write start init bit
	result, readArray = FpgaReadReg(portexp_main_ctrl_c[1], 1, errCnt)
	if enb == 1 then
		errCnt =FpgaWriteReg(portexp_main_ctrl_c[1],{bor(readArray[1],0x2)}, errCnt)
	else
		errCnt =FpgaWriteReg(portexp_main_ctrl_c[1],{band(readArray[1],0xD)}, errCnt) 
	end
	return errCnt
end

---write to a register in the DAC that control the 10 MHZ generator
-- @within system function
-- @param command  : reg id
-- @param data : data to write 16 bit
-- @return ErrCnt

local function clk_ctrl_dac_wr(command,data)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local cmd = lshift(band(command,0xF),16)
	local regcmd = bor(band(data,0xFFFF),cmd)
	result =FpgaWriteReg(clockext_ctrl_c[1],{bor(regcmd,0x100000)})
	return errCnt
end  



--- control MUX to connect to MHZ to Zynq, if Internal Use , the 3.3V clock is enabled through expander
-- @within system function
-- @param source  : 0 : local 10 MHZ, 1 GPS 10 MHz 
-- @return ErrCnt

local function clk_source_ctrl(source)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	if source == 0 then
		errCnt= expander_writevalue(0,bor(localA,0x04), band(localB,0xFD)) -- enable OSC_EN bit ( GPA2) and  and 0 to CLKSRC_CTRL GPB1
	elseif source == 1 then
		errCnt= expander_writevalue(0,band(localA,0xFB), bor(localB,0x02)) -- disable OSC_EN bit ( GPA2) and  and eanble to CLKSRC_CTRL GPB1
	else
		errCnt= expander_writevalue(0,bor(localA,0x04), bor(localB,0x02)) -- disable OSC_EN bit ( GPA2) and  and eanble to CLKSRC_CTRL GPB1
	end

	return errCnt
end  

--- control CHRONO_IN_EN
-- @within system function
-- @param source  : 0 : disable : 1 enalble
-- @return ErrCnt

local function chron_in_ctrl(enb)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	if enb == 1 then
		errCnt= expander_writevalue(0,bor(localA,0x10), localB) -- enable  CHRONO_IN_EN bit ( GPA4) and  and 0 to CLKSRC_CTRL GPB1
	else
		errCnt= expander_writevalue(0,band(localA,0xEF), localB) -- disable CHRONO_IN_EN bit ( GPA4) and  and eanble to CLKSRC_CTRL GPB1
	end

	return errCnt
end  

--- control CHRONO_SW_EN
-- @within system function
-- @param source  : 0 : disable : 1 enalble
-- @return ErrCnt

local function chron_sw_ctrl(enb)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	result, readArray = FpgaReadReg(masterio_c[1], 1, errCnt)
	if enb == 1 then
		result =FpgaWriteReg(masterio_c[1],{bor(readArray[1],0x0001)})
	else
		result =FpgaWriteReg(masterio_c[1],{band(readArray[1],0xFFFE)})
	end

	return errCnt
end  

--- control mux in serial
-- @within system function
-- @param enb  : 0 : disable : 1 enalble
-- @param enb  : 0 : rs232 1: rs424 2: pulse
-- @return ErrCnt

local function mux_in_serial_ctrl(enb, mux)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	localB=band(localB,0x1F)-- disable locally mux control signal
	localA=band(localA,0xFC)-- disable locally ZYNQ_RS232_EN ans  ZYNQ_RS422_EN
	if enb == 1 then
		if mux == 0 then
			errCnt= expander_writevalue(0,bor(localA,0x1), bor(localB,0x80)) -- 1  1A_ENA : 0: 1A_SA0,  1A_SA1 and enable ZYNQ_RS232_EN
		elseif mux==1 then
			errCnt= expander_writevalue(0,bor(localA,0x2), bor(localB,0xA0)) -- 1  1A_ENA : 0: 1A_SA0,  1A_SA1 and enable ZYNQ_RS422_EN
		else
			errCnt= expander_writevalue(0,localA, bor(localB,0xC0)) -- 1  1A_ENA : 0: 1A_SA0,  1A_SA1
			chron_sw_ctrl(1)--must enabled chrono
		end 
		
	else
		errCnt= expander_writevalue(0,localA, localB) -- disable CHRONO_IN_EN bit ( GPA4) and  and eanble to CLKSRC_CTRL GPB1
		chron_sw_ctrl(0)
	end

	return errCnt
end 


--- control CHRONO_SW_EN
-- @within system function
-- @param enb  : 0 : disable : 1 enalble
-- @param rts  : 0 : ready to send disable : 1  ready to send  enalble
-- @return ErrCnt

local function print_ctrl(enb,rts)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	errCnt,localA, localB =expander0_readbacklocal()
	localA=band(localA,0x7F)-- disable locally ZYNQ_RS232_EN ans  ZYNQ_RS422_EN
	
	
	result, readArray = FpgaReadReg(rs232_ctrl_c[1], 1, errCnt)
	if enb == 1 then
		LOG_Info(string.format(" 	PWTINFO:   Printer  enabled command"))
		errCnt= expander_writevalue(0,bor(localA,0x80), localB) -- biGPA7 ZYNQ_PRT_EN enable
	else
		LOG_Info(string.format(" 	PWTINFO:   Printer  disabled command "))
		errCnt= expander_writevalue(0,localA, localB) -- biGPA7 ZYNQ_PRT_EN enable
	end
	if rts == 1 then
		LOG_Info(string.format(" 	PWTINFO:   Printer  RTS is eanbled"))
		result =FpgaWriteReg(rs232_ctrl_c[1],{bor(readArray[1],0x0001)})
	else
		LOG_Info(string.format(" 	PWTINFO:   Printer  RTS is disabled"))
		result =FpgaWriteReg(rs232_ctrl_c[1],{band(readArray[1],0xFFFE)})
	end
	result, readArray = FpgaReadReg(rs232_ctrl_c[1], 1, errCnt)
	local prtinvalidn = band(0x1,rshift(readArray[1],1))
	local cts = band(0x1,rshift(readArray[1],2))
	LOG_Info(string.format(" 	PWTINFO:   Printer  readback STATUS"))
	if prtinvalidn == 0  and  enb == 0 then
		LOG_Info(string.format(" 		   	ATTENTION PRINTER IS INVALID ( disabled)"))
	end
	if cts == 1 then
		LOG_Info(string.format(" 		  	Printer  CTS is eanbled"))
	else
		LOG_Info(string.format(" 		  	 Printer  CTS is disabled"))
	end
	
	return errCnt
end  

--- control mux monitoring input
-- @within system function
-- @param ctrl  : 0 : 12V  1:5V ,2  3.3V
-- @return ErrCnt

local function mux_in_monitoring_ctrl(ctrl)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	localB=band(localB,0xE7)-- disable locally MON_A1 MON_A0 

	if ctrl == 0 then
		errCnt= expander_writevalue(0,localA, localB) -- MON_A1 MON_A0  = 0 0
	elseif ctrl==1 then
		errCnt= expander_writevalue(0,localA, bor(localB,0x08)) -- MON_A1 MON_A0  = 0 1
	else
		errCnt= expander_writevalue(0,localA, bor(localB,0x10)) -- MON_A1 MON_A0  = 1 0
	end 
		

	return errCnt
end 
--- control external PHY
-- @within system function
-- @param ctrl  : 0 : PHY_EN OFF, 1 : PHY_EN ON
-- @return ErrCnt

local function ext_phy_ctrl(ctrl)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	localB=band(localB,0xFE)-- disable locally PHY_EN

	if ctrl == 0 then
		errCnt= expander_writevalue(0,localA, localB) 
	else
	
		errCnt= expander_writevalue(0,localA, bor(localB,0x01))
	end 
		

	return errCnt
end 


--- control external USB power   from the USB ideal diode to the charger
-- @within system function
-- @param ctrl  : 0 : USB_PWR_EN_n = 1  , 1 : USB_PWR_EN_n = 0  ( active default)
-- @return ErrCnt

local function ext_usbcharge_ctrl(ctrl)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	localA=band(localA,0xBF)-- mask USB_PWR_EN_n
	-- attention USB_PWR_EN_n is active low

	if ctrl == 0 then
		errCnt= expander_writevalue(0,bor(localA,0x40), localB) 
	else
		errCnt= expander_writevalue(0,localA,localB )
	end 

	return errCnt
end 

--- control external USB power for mas storage
-- @within system function
-- @param ctrl  : 0 : OTG_EN =0 (disable)   , 1 : OTG_EN = 1  ( active)
-- @return ErrCnt

local function ext_usbmasstroage_ctrl(ctrl)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	localA=band(localA,0xF7)-- mask OTG_EN


	if ctrl == 0 then
		errCnt= expander_writevalue(0,localA, localB) 
	else
		errCnt= expander_writevalue(0,bor(localA,0x08),localB )
	end 

	return errCnt
end 

--- control external POE enable from the POE ideal diode to the charger
-- @within system function
-- @param ctrl  : 0 : POE_EN_n = 1 ( inactive default )  , 1 : POE_EN_n = 0  
-- @return ErrCnt

local function ext_poe_ctrl(ctrl)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	local localA, localB
	errCnt,localA, localB =expander0_readbacklocal()
	localA=band(localA,0xDF)-- mask POE_EN_n
	-- attention POE_EN_n is active low
	if ctrl == 0 then
		errCnt= expander_writevalue(0,bor(localA,0x20), localB) 
	else
		errCnt= expander_writevalue(0,localA,localB )
	end 

	return errCnt
end 
--- LCD backlight and reset control
-- @within system function
-- @return ErrCnt

local function lcdcontrol(dutycycle,reset)
	local errCnt = 0 
	local readArray = {}
	local returnvalue
	result, readArray = FpgaReadReg(lcd_ctrlreg_c[1], 1, errCnt)
	if reset == 1 then
		result =FpgaWriteReg(lcd_ctrlreg_c[1],{band(readArray[1],0xFFFE)})
	else
		result =FpgaWriteReg(lcd_ctrlreg_c[1],{bor(readArray[1],0x0001)})
	end 
	
  --CONSTANT lcd_backlight_c              	: swtb_reg_t := (x"001C", x"13882710", x"FFFFFFFF",x"00000000");
  -- 0 : 15 : perdio in use
  -- 31: 16 : duty cycle on in us
	result, readArray = FpgaReadReg(lcd_ctrlreg_c[1], 1, errCnt)
	local period400Khz= 0x2710
	-- if duty cycle is active make sure Backlight is enable
	if dutycycle >= 100 then
		dutycycle = 100
		result =FpgaWriteReg(lcd_ctrlreg_c[1],{bor(readArray[1],0x100)})
	elseif dutycycle <= 0 then
		dutycycle = 0
		result =FpgaWriteReg(lcd_ctrlreg_c[1],{band(readArray[1],0xEFF)})
	else
		result =FpgaWriteReg(lcd_ctrlreg_c[1],{bor(readArray[1],0x100)})
	end
	local dutytmp= dutycycle*period400Khz/100 
	if dutycycle == 100 then
		dutytmp = dutytmp-1
	end
	result =FpgaWriteReg(lcd_backlight_c[1],{bor(lshift(dutytmp,16),period400Khz)})
	return errCnt
end  

--- generate an interrupt
-- @within system function
-- @return ErrCnt

local function interruptgen()
	local errCnt = 0 
	local readArray = {}
	local returnvalue

	result =FpgaWriteReg(scratch_c[1],{0x1})
	msleep(1)
	result =FpgaWriteReg(scratch_c[1],{0x0})
	return errCnt
end  

-- ------------------------------------------------------------------------------------------------
--
-- ************************************************************************************************
-- Declaration of the functions available in this script...
-- ------------------------------------------------------------------------------------------------

powertimeFunc = {
  GetSscratch = GetSscratch,
  battery_read_reg = battery_read_reg,
  battery_write_reg = battery_write_reg ,
  expander_readvalue=expander_readvalue,
  expander_writevalue = expander_writevalue,
  expander_init = expander_init,
  clk_ctrl_dac_wr = clk_ctrl_dac_wr,
  expander0_readbacklocal= expander0_readbacklocal,
  clk_source_ctrl = clk_source_ctrl,
  chron_sw_ctrl = chron_sw_ctrl,
  chron_in_ctrl = chron_in_ctrl,
  mux_in_serial_ctrl = mux_in_serial_ctrl,
  interruptgen=interruptgen,
  print_ctrl = print_ctrl,
  keyboardautoread = keyboardautoread,
  mux_in_monitoring_ctrl=mux_in_monitoring_ctrl,
  ext_phy_ctrl = ext_phy_ctrl,
  ext_usbcharge_ctrl = ext_usbcharge_ctrl ,
  ext_usbmasstroage_ctrl= ext_usbmasstroage_ctrl,
  ext_poe_ctrl = ext_poe_ctrl,
  lcdcontrol =lcdcontrol,
  battery_read_adc= battery_read_adc
  
}

