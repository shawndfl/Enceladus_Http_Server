
SERVER_PATH=server/bin
SERVER_SHARE=http_server

$(SERVER_PATH)/lib$(SERVER_SHARE).so:
	@$(MAKE) -C server
	
#
# Bulid app
# 
all: $(SERVER_PATH)/lib$(SERVER_SHARE).so 
	@$(MAKE) -C unittests
	@$(MAKE) -C $(wildcard samples/*)
