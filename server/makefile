
APP:=./bin/libhttp_server.so

SRC_CC := $(wildcard ./src/*.cc)
SRC := $(notdir $(SRC_CC:%.cc=%))
OBJ := $(filter-out main.o,$(SRC:%=bin/%.o))

CFLAGS := -Wall -O3 -std=c++17 -MMD -fPIC
LDLIBS := -lstdc++ -pthread -shared -lc  

# Phony targets
.PHONY: all clean debug

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
bin/%.o: src/%.cc
	@mkdir -p bin/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 

#
# Link
#
$(APP): $(OBJ)		
	@echo linking $@
	@$(CXX) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

#
# Clean
#
clean:
	@echo cleaning	
	@rm -f bin/*
	@rm -f $(APP)

-include $(OBJ:.o=.d)		
