LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# our own branch needs these headers

FLY_INCLUDE	:= $(LOCAL_PATH)/../../include
FLY_AUDIO_INCLUDE := $(LOCAL_PATH)/../include

FLYUTILS_INCLUDE := $(FLY_AUDIO_INCLUDE)/flyutils
FLYNATIVE_SERVICE_INCLUDE := $(FLY_AUDIOINCLUDE)/libflyaudioNativeServer
FLYMODULE_INCLUDE := $(FLY_AUDIO_INCLUDE)/flyaudiomodule
FLYDRIVER_INCLUDE := $(FLY_AUDIO_INCLUDE)/driver

LOCAL_LDLIBS:= -llog

LOCAL_SRC_FILES := FlyModuleService.cpp \
					FlyProperties.cpp \
					$(LOCAL_PATH)/Tinyxml/tinyxml.cpp \
		            $(LOCAL_PATH)/Tinyxml/tinyxmlparser.cpp \
		            $(LOCAL_PATH)/Tinyxml/tinyxmlerror.cpp \
		            $(LOCAL_PATH)/Tinyxml/tinystr.cpp


LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include \
					$(LOCAL_PATH)/../include \
					$(LOCAL_PATH)/Tinyxml

LOCAL_C_INCLUDES += $(FLYMODULE_INCLUDE) \


LOCAL_SRC_FILES += $(LOCAL_PATH)/../../include/moduleCommApi.c \
					$(LOCAL_PATH)/../../include/commonFunc.c

LOCAL_MODULE := FlyModuleService
include $(BUILD_EXECUTABLE)
