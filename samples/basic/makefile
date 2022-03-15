
APP:=basic

SRC_CC := $(wildcard ./*.cc)
OBJ_CC := $(SRC_CC:%.cc=bin/%.o)

SERVER_HEADERS=../../server/src
SERVER_SHARE=http_server
SERVER_PATH=../../server/bin

CFLAGS := -Wall -g3 -std=c++17 -MMD -I../src -I$(SERVER_HEADERS)

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
all: $(APP)
	@echo Done making $(APP)

#
# Build server
#
$(SERVER_PATH)/$(SERVER_SHARE).so:
	@$(MAKE) -C ../../server 	

#
# Compile
#
bin/%.o: %.cc
	@mkdir -p bin/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 
	
#
# Link
#
$(APP): $(SERVER_PATH)/$(SERVER_SHARE).so $(OBJ_CC)		
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
