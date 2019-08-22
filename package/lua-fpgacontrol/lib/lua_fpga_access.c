#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


#include <lualib.h>
#include <lauxlib.h>

#include "lua_fpga_access.h"

#define BUF_SIZE 16

#define FPGA_DEV "/dev/fpga-control"
#define FPGA_DEV_QT "/dev/fpga-control-qt"
/* Global variables */
static int file_handler = -1;
static int file_handlerqt = -1;

/*----------------------------------------------------------------------------*/

static int lua_fpga_write(lua_State *L)
{
	int size;
	int addr;
	unsigned int *buffer;
	int size_wrote;
	int i;

	if (file_handler <= 0) {
		printf ("Fpga is not opened");
		return 0;
	}

	addr = luaL_checkint(L, -2);

	luaL_checktype(L, -1, LUA_TTABLE);
	size = lua_rawlen(L, -1);

	// Reserver size times an integer
	buffer = malloc(4 * size);
	if (buffer == NULL) {
		printf ("Not enought memory available");
		return 0;
	}

	i = 0;
	// Add space for the value stack conatins -1 => nil, -2 => table
	lua_pushnil(L);
	// Pop key and value of the table at index -2
	while(lua_next(L, -2) != 0) {
		// Get Value
		buffer[i] = lua_tounsigned(L, -1);

		// pop the key stack contains -1 => value, -2 => table
		lua_pop(L, 1);
		i++;
		if(i >= size)
			break;
	}

	size = i;

	lseek(file_handler, addr, SEEK_SET);

	size_wrote = write(file_handler, buffer, 4*size);
	if (size_wrote< 0) {
		printf ("Can not read from fpga");
		return 0;
	}

	free(buffer);

	return 1;

}


static int lua_fpga_read(lua_State *L)
{
	int size;
	int addr;
	int size_read;
	unsigned int *buffer;
	int i;
	int ret = 0;

	if (file_handler <= 0) {
		printf ("Fpga is not opened");
		return 0;
	}

	addr = luaL_checkint(L, -2);
	size = luaL_checkint(L, -1);
	buffer = malloc(4*size);
	if (buffer == NULL) {
		printf ("Not enought memory available\n");
		return 0;
	}

	lseek(file_handler, addr, SEEK_SET);

	size_read = read(file_handler, buffer, 4*size);
	if (size_read < 0) {
		printf ("Can not read from fpga\n");
		goto exit;
	}

	lua_newtable(L);
	for (i = 0; i < (size_read / 4); i++) {
		lua_pushunsigned (L, buffer[i]);

		// Do asignment t[i] = value
		lua_rawseti (L, -2, i + 1);
	}

	ret = 1;

exit:
	free(buffer);
	return ret;
}

static int lua_fpga_close(lua_State *L)
{
	close(file_handler);
	return 0;
}

static int lua_fpga_open(lua_State *L)
{	
	file_handler = open(FPGA_DEV, O_CLOEXEC | O_RDWR);
	if (file_handler <= 0) {
		printf ("Can not open %s", FPGA_DEV);
	}
	return 0;
}


/*------------------------------QUANTUM-------------------------------------------*/

static int lua_fpga_write_qt(lua_State *L)
{
	int size;
	int addr;
	unsigned int *buffer;
	int size_wrote;
	int i;

	if (file_handlerqt <= 0) {
		printf ("Fpga is not opened");
		return 0;
	}

	addr = luaL_checkint(L, -2);

	luaL_checktype(L, -1, LUA_TTABLE);
	size = lua_rawlen(L, -1);

	// Reserver size times an integer
	buffer = malloc(4 * size);
	if (buffer == NULL) {
		printf ("Not enought memory available");
		return 0;
	}

	i = 0;
	// Add space for the value stack conatins -1 => nil, -2 => table
	lua_pushnil(L);
	// Pop key and value of the table at index -2
	while(lua_next(L, -2) != 0) {
		// Get Value
		buffer[i] = lua_tounsigned(L, -1);

		// pop the key stack contains -1 => value, -2 => table
		lua_pop(L, 1);
		i++;
		if(i >= size)
			break;
	}

	size = i;

	lseek(file_handlerqt, addr, SEEK_SET);

	size_wrote = write(file_handlerqt, buffer, 4*size);
	if (size_wrote< 0) {
		printf ("Can not read from fpga");
		return 0;
	}

	free(buffer);

	return 1;

}


static int lua_fpga_read_qt(lua_State *L)
{
	int size;
	int addr;
	int size_read;
	unsigned int *buffer;
	int i;
	int ret = 0;

	if (file_handlerqt <= 0) {
		printf ("Fpga is not opened");
		return 0;
	}

	addr = luaL_checkint(L, -2);
	size = luaL_checkint(L, -1);
	buffer = malloc(4*size);
	if (buffer == NULL) {
		printf ("Not enought memory available\n");
		return 0;
	}

	lseek(file_handlerqt, addr, SEEK_SET);

	size_read = read(file_handlerqt, buffer, 4*size);
	if (size_read < 0) {
		printf ("Can not read from fpga\n");
		goto exit;
	}

	lua_newtable(L);
	for (i = 0; i < (size_read / 4); i++) {
		lua_pushunsigned (L, buffer[i]);

		// Do asignment t[i] = value
		lua_rawseti (L, -2, i + 1);
	}

	ret = 1;

exit:
	free(buffer);
	return ret;
}

static int lua_fpga_close_qt(lua_State *L)
{
	close(file_handlerqt);
	return 0;
}

static int lua_fpga_open_qt(lua_State *L)
{	
	file_handlerqt = open(FPGA_DEV_QT, O_CLOEXEC | O_RDWR);
	if (file_handlerqt <= 0) {
		printf ("Can not open %s", FPGA_DEV_QT);
	}
	return 0;
}


/*----------------------------------------------------------------------------*/
LUALIB_API int luaopen_fpga_access(lua_State *L)
{
	lua_register(L, "fpga_open", lua_fpga_open);
	lua_register(L, "fpga_write", lua_fpga_write);
	lua_register(L, "fpga_read", lua_fpga_read);
	lua_register(L, "fpga_close", lua_fpga_close);
	lua_register(L, "fpga_open_qt", lua_fpga_open_qt);
	lua_register(L, "fpga_write_qt", lua_fpga_write_qt);
	lua_register(L, "fpga_read_qt", lua_fpga_read_qt);
	lua_register(L, "fpga_close_qt", lua_fpga_close_qt);
	return 0;
}

