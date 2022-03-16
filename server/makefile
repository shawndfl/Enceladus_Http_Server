
APP:=../lib/libhttp_server.so

SRC_CC := $(wildcard ./src/*.cc)
SRC := $(notdir $(SRC_CC:%.cc=%))
OBJ := $(filter-out main.o,$(SRC:%=../obj/%.o))

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
../obj/%.o: src/%.cc	
	@mkdir -p ../obj/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 

#
# Link
#
$(APP): $(OBJ)		
	@mkdir -p ../lib/
	@echo linking $@
	@$(CXX) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

#
# Clean
#
clean:
	@echo cleaning	
	@rm -f ../lib/*
	@rm -f ../obj/*
	@rm -f $(APP)

-include $(OBJ:.o=.d)		
