#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "controlqt.h"

/*----------------------------------------------------------------------------*/
int open_control()
{
	int fd;
	int buf_size = 32;
	char path[buf_size];

	snprintf(path, buf_size, "/dev/%s", CHAR_DEV_NAME);

	if((fd = open(path, O_RDWR)) < 0)
		printf("Error opening device: %s\n", strerror(errno));

	return fd;
}

/*----------------------------------------------------------------------------*/
void close_control(int fd)
{
	close(fd);
}

/*----------------------------------------------------------------------------*/

int write_value(int fd, int addr,int value)
{
	int ret;
	lseek(fd, addr, SEEK_SET);
	ret = write(fd, &value, sizeof(value));

	if(ret < 0)
	{
		printf("Write error: %s\n", strerror(errno));
		return -1;
	}

	if(ret != sizeof(value))
	{
		printf("Write error, written %i, expected %i\n",
				ret, sizeof(value));
		return -1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
int read_value(int fd, int addr, int *value)
{
	int ret;
	lseek(fd, addr, SEEK_SET);
	ret = read(fd, value, sizeof(*value));

	if(ret < 0)
	{
		printf("Read error: %s\n", strerror(errno));
		return -1;
	}

	if(ret != sizeof(*value))
	{
		printf("Read error, read %i, expected %i\n",
				ret, sizeof(*value));
		return -1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
void test_rw_same_value(int fd,int addr, int value)
{
	int r_value;

	assert(write_value(fd,addr, value) == 0);
	assert(read_value(fd,addr, &r_value) == 0);
	assert(r_value == value);
	assert(read_value(fd,addr, &r_value) == 0);
	assert(r_value == value);
}

/*----------------------------------------------------------------------------*/
void test_rw()
{
	int fd;
	int valuereg;
	int regaddress;
	printf("Test read and write values ... ");

	fd = open_control();
	assert(fd >= 0);

	// Test with two values in case of it was already in register in scratch reg
	test_rw_same_value(fd, 4,0x00000081);
	printf("Test second one");
	test_rw_same_value(fd, 4,0x00000083);

	close_control(fd);

	printf("OK!\n");
}



/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
	// Same random ...
	srand(time(NULL));
	printf("Let's write and read at adress of scratch register of FPGA space!\n");
	test_rw();

	printf("Tests passed!\n");

	return 0;
}
