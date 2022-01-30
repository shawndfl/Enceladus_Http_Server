
APP:=bin/unit_tests

SRC_CC := $(wildcard ../src/*.cc) $(wildcard ./*.cc)
SRC_CPP := $(wildcard ./UnitTest++/*.cpp) $(wildcard ./UnitTest++/Posix/*.cpp)

SRC_CC := $(notdir $(SRC_CC:%.cc=%))
SRC_CPP := $(notdir $(SRC_CPP:%.cpp=%))

OBJ_CC := $(filter-out bin/main.o,$(SRC_CC:%=bin/%.o))
OBJ_CPP := $(SRC_CPP:%=bin/%.o)

CFLAGS := -Wall -O3 -std=c++17 -MMD -I../src
LDLIBS := -lstdc++ -pthread

vpath %.cc ../src/
vpath %.cc ./
vpath %.cpp ./UnitTest++/
vpath %.cpp ./UnitTest++/Posix

# Phony targets
.PHONY: all clean debug env

#
# Bulid app
#
all: $(APP)
	@echo Done making $(APP)

#
# Debug the app
#
debug: CFLAGS += -g3
debug: all

#
# Compile
#
bin/%.o: %.cc
	@mkdir -p bin/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 

bin/%.o: %.cpp
	@mkdir -p bin/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 
	
#
# Link
#
$(APP): $(OBJ_CPP) $(OBJ_CC)		
	@echo linking $@
	@$(CXX) -o $@ $(OBJ_CPP) $(OBJ_CC) $(LDFLAGS) $(LDLIBS)

env:
	@echo "SRC_CC = $(SRC_CC)"
	@echo ""		
	@echo "SRC_CPP = $(SRC_CPP)"
	@echo ""		
	@echo "OBJ_CC = $(OBJ_CC)"
	@echo ""		
	@echo "OBJ_CPP = $(OBJ_CPP)"
#
# Clean
#
clean:
	@echo cleaning
	@rm -f bin/*
	@rm -f $(APP)

-include $(OBJ:.o=.d)		
