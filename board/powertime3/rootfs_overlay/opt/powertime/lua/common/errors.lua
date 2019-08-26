--- Describe all the error in the lua level
-- @module  errors

--- Error at LUA level
errors = {
    "UNKOWN_ERROR",                   --1
    "UNDEFINED_ERROR",                --2
    "TEST_FAILED",                    --3
    "FPGA_ACCESS_FAIL",               --14
    "OUTPUT_NOT_ENABLED",             --15
    "ERR_DEVICE_LOCKED",
	"EXPANDERA_ERROR",
	"I2C_BUSY"
}

--Revert the table, so with have errors-cods as keys
errorsToNbr = {}
for k,v in pairs(errors) do
    errorsToNbr[v]=k
end