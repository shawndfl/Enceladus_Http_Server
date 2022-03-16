
SERVER_PATH=server/bin
SERVER_SHARE=http_server
	
# Phony targets
.PHONY: all clean

#
# Bulid app
# 
all: $(SERVER_PATH)/lib$(SERVER_SHARE).so 
	@$(MAKE) -C examples/basic 
	@$(MAKE) -C examples/unittests
	@echo
	@echo Done making all
	@echo	

clean: 
	@$(MAKE) -C server clean
	@$(MAKE) -C examples/unittests clean
	@$(MAKE) -C examples/basic clean


$(SERVER_PATH)/lib$(SERVER_SHARE).so:
	@$(MAKE) -C server