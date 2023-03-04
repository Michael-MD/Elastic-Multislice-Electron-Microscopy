BINARY=bin
CODEDIRS=. ./src/
INCDIRS=. ./include/
LIBSDIR=./libs/

CC=g++ -std=c++17
OPT=-O0

DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -g $(foreach D, $(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)
CFILES=$(foreach D, $(CODEDIRS),$(wildcard $(D)/*.cpp))

OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o a.out $^ $(wildcard $(LIBSDIR)/*.a)

%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(foreach D, $(CODEDIRS),$(wildcard $(D)/*.o)) $(foreach D, $(CODEDIRS),$(wildcard $(D)/*.d)) a.out
