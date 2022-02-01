
APP:=bin/http_server

SRC_CC := $(wildcard ./src/*.cc)
SRC := $(notdir $(SRC_CC:%.cc=%))
OBJ := $(filter-out main.o,$(SRC:%=bin/%.o))

CFLAGS := -Wall -O3 -std=c++17 -MMD
LDLIBS := -lstdc++ -pthread

# Phony targets
.PHONY: all clean debug env

#
# Bulid app
#
all: $(APP)
	@make -C unittests debug	
	@echo Done making $(APP)

#
# build
#
test:
	make -C unittests debug	
	
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

env:
	@echo "SRC = $(SRC)"
	@echo ""		
	@echo "OBJ = $(OBJ)"
#
# Clean
#
clean:
	@echo cleaning
	@make -C unittests clean 
	@rm -f bin/*
	@rm -f $(APP)

-include $(OBJ:.o=.d)		
