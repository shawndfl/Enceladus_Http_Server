
SERVER_PATH=server/bin
SERVER_SHARE=http_server
	
# Phony targets
.PHONY: all clean

#
# Bulid app
# 
all: $(SERVER_PATH)/lib$(SERVER_SHARE).so 
	@$(MAKE) -C examples/01_static_site
	@$(MAKE) -C examples/02_json_response
	@$(MAKE) -C examples/03_more_requests
	@$(MAKE) -C examples/unittests
	@echo
	@echo Done making all
	@echo	

clean: 
	@$(MAKE) -C server                         clean
	@$(MAKE) -C examples/unittests             clean
	@$(MAKE) -C examples/01_static_site        clean
	@$(MAKE) -C examples/02_json_response      clean
	@$(MAKE) -C examples/03_more_requests      clean


$(SERVER_PATH)/lib$(SERVER_SHARE).so:
	@$(MAKE) -C server