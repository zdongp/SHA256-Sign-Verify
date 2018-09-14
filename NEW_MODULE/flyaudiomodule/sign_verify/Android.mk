LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := $(LOCAL_PATH)/src/libcrypto
LOCAL_SRC_FILES := $(LOCAL_PATH)/src/libcrypto.a

include $(PREBUILT_STATIC_LIBRARY)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src/

LOCAL_SRC_FILES := $(LOCAL_PATH)/src/SignVerify.cpp

LOCAL_LDFLAGS += $(LOCAL_PATH)/src/libcrypto.a

LOCAL_LDLIBS:= -llog

LOCAL_MODULE := SignVerify 

include $(BUILD_EXECUTABLE)
