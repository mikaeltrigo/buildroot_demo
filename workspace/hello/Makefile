.PHONY: all

CXXFLAGS += -g

all: clean hello

hello: main.o
	$(CXX) -o $@ $<

clean:
	$(RM) hello
	$(RM) *.o

