LIB_NAME = msleep.so
SOURCES = lib/msleep.c

OBJ = $(SOURCES:.c=.o)
CFLAGS += -Wall -g #usefull fordebug

# LUA configuration
#LUA_VERSION ?= 5.2
LUA_CFLAGS ?= $(shell pkg-config lua$(LUA_VERSION) --cflags)
LUA_LDFLAGS ?= $(shell pkg-config lua$(LUA_VERSION) --libs)

all: clean $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(CC) -shared -fpic -o $(LIB_NAME) $(OBJ) $(LUA_LDFLAGS)

%.o: %.c
	$(CC) -fpic -c -o $@ $< $(CFLAGS) $(LUA_CFLAGS)

clean:
	rm -rf $(LIB_NAME) $(OBJ)

.PHONY: all clean
