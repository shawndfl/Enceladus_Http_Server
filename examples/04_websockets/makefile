
APP:=04_web_sockets

APP_PATH:=../../bin

SRC_CC := $(wildcard *.cc)
OBJ_CC := $(SRC_CC:%.cc=../../obj/$(APP)_%.o)

SERVER_HEADERS=../../server/src
SERVER_SHARE=http_server
SERVER_PATH=../../lib

CFLAGS := -Wall -g3 -std=c++17 -MMD -I$(SERVER_HEADERS)

LDLIBS :=  -lstdc++ -pthread      \
					 -l$(SERVER_SHARE)      \
					 -L$(SERVER_PATH)       \
					  -Wl,-rpath=$(SERVER_PATH)

vpath %.cc ./

# Phony targets
.PHONY: all clean debug

#
# Bulid app
#
all: $(APP_PATH)/$(APP)
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
../../obj/$(APP)_%.o: %.cc
	@mkdir -p ../../obj/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 
	
#
# Link
#
$(APP_PATH)/$(APP): $(SERVER_PATH)/lib$(SERVER_SHARE).so $(OBJ_CC)
	@mkdir -p $(APP_PATH)		
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
