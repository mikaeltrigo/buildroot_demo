--- Config pkgis a table containing an index pointer for each parameter set.
-- @script configpkg

--
-- ABSTRACT:
-- configpkg.lua
-- =============
-- This file contains a collection of configuration parameters to be used
-- in the PowerTime system.
-- These parameters are NOT accessible through the user interface. They are evaluated
-- during system integration and used according to the application.
--
-- HISTORY:
-- Date Author Description
-- 2019-02-12 mt created

-- ------------------------------------------------------------------------------------------------
-- ************************************************************************************************
-- Declaration of system configuration parameter...
-- ------------------------------------------------------------------------------------------------
-- -----------------------------------------------------------------------------------------------
-- Note as configpkg is the first package declared , all relation to other module in configpkg must be required here


glob_car = false
Unplugreenable = false -- reenable power automatically if the user unplug the cable
POWERTIME_TYPE = {
  PWRT1 = 0x0, 
  PWRT2 = 0x2,  
  PWRT2 = 0x3
}

-- global Feature Flags..
featureFlags = 
{   
  proVersion = 0, 
  testVersion = 0
}
