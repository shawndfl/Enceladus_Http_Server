
APP:=../lib/libenceladus.so
MAJOR := 0
MINOR := 1
PATCH := 0

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

install: $(APP)	  
	cp -f $(APP) /usr/local/lib/$(APP).$(MAJOR).$(MINOR).$(PATCH)	
	cd /usr/local/lib/ && ln -s -f  $(APP).$(MAJOR).$(MINOR).$(PATCH) $(APP).$(MAJOR)
	cd /usr/local/lib/ && ln -s -f $(APP).$(MAJOR).$(MINOR).$(PATCH) $(APP)
	@mkdir -p /usr/local/include/enceladus
	@rm /usr/local/include/enceladus/*
	cp -f ./src/*.h  /usr/local/include/enceladus/ 

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
