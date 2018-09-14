# Generate module config.h file
CURRENT_MODULE_NAME := $(LOCAL_MODULE)
PWD_PATH := $(LOCAL_PATH)

FLY_CONFIG := $(PWD_PATH)/config.h
ID := $(strip $(patsubst %.flyaudio, %, $(CURRENT_MODULE_NAME)))

$(shell echo -e '/* This File Auto Generated And Please Do not Edit it */\n' > $(FLY_CONFIG))
$(shell echo '#ifndef _CONFIG_H' >> $(FLY_CONFIG))
$(shell echo '#define _CONFIG_H' >> $(FLY_CONFIG))
$(shell echo -e '\n\n' >> $(FLY_CONFIG))

$(shell echo -e '#define CURRENT_MODULE_ID \t"$(ID)"' >> $(FLY_CONFIG))
$(shell echo -e '#define CURRENT_MODULE_NAME \t"Current FlyAudio Module Is $(ID)"' >> $(FLY_CONFIG))


ifeq ($(strip $(DEBUG_DISABLE)), true)
$(shell echo -e '\n\n' >> $(FLY_CONFIG))
$(shell echo -e '#define DEBUG_DISABLE'>> $(FLY_CONFIG))
else
$(shell echo -e '\n\n' >> $(FLY_CONFIG))
$(shell echo -e '#define TAG \t\t"Module_$(ID)"' >> $(FLY_CONFIG))
endif

$(shell echo -e '\n\n' >> $(FLY_CONFIG))
$(shell echo '#endif //_CONFIG_H' >> $(FLY_CONFIG))
