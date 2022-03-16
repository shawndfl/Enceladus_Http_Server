

APP:=bin/unit_tests

SRC_CC := $(wildcard ../src/*.cc) $(wildcard ./*.cc)
SRC_CPP := $(wildcard ./UnitTest++/*.cpp) $(wildcard ./UnitTest++/Posix/*.cpp)

SRC_CC := $(notdir $(SRC_CC:%.cc=%))
SRC_CPP := $(notdir $(SRC_CPP:%.cpp=%))

OBJ_CC := $(filter-out bin/main.o,$(SRC_CC:%=bin/%.o))
OBJ_CPP := $(SRC_CPP:%=bin/%.o)

SERVER_HEADERS=../../server/src
SERVER_SHARE=http_server
SERVER_PATH=../../server/bin

CFLAGS := -Wall -g3 -std=c++17 -MMD -I$(SERVER_HEADERS)

LDLIBS :=  -lstdc++ -pthread      \
					 -l$(SERVER_SHARE)      \
					 -L$(SERVER_PATH)       \
					  -Wl,-rpath=$(SERVER_PATH)

vpath %.cc ../src/
vpath %.cc ./
vpath %.cpp ./UnitTest++/
vpath %.cpp ./UnitTest++/Posix

# Phony targets
.PHONY: all clean debug

#
# Bulid app
#
all: $(APP)
	@$(MAKE) -C ../../server
	@echo Done making $(APP)

#
# Build server
#
$(SERVER_PATH)/lib$(SERVER_SHARE).so:
	@$(MAKE) -C ../../server 	

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
$(APP): $(SERVER_PATH)/lib$(SERVER_SHARE).so $(OBJ_CPP) $(OBJ_CC)	
	@echo linking $@
	@$(CXX) -o $@ $(OBJ_CPP) $(OBJ_CC) $(LDFLAGS) $(LDLIBS)

#
# Clean
#
clean:
	@echo cleaning
	@rm -f bin/*
	@rm -f $(APP)

-include $(OBJ:.o=.d)
