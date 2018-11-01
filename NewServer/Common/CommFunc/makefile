#
# makefile 
#

include ../../Make/makefile_lib
				
TARS_INCLUDE = /usr/local/tars/cpp/include

SOURCE_FILE:=$(wildcard *.cpp) $(wildcard *.c)
OBJ_FILE:=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE_FILE)))

all: $(OBJ_FILE)
	$(AR) q ../$(LIB_FILE) $(OBJ_FILE)

%.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c $<  -I./  -I$(TARS_INCLUDE) $(INC_COMM) 

%.o:%.c
	$(CXX) $(CXX_FLAGS) -c $<  -I./ -I$(TARS_INCLUDE) $(INC_COMM) -I./

clean:
	rm -rf *.o

