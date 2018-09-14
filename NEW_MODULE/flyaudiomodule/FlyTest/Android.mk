LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# our own branch needs these headers

LOCAL_LDLIBS:= -llog

LOCAL_SRC_FILES := FlyTest.cpp 


LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include \
					$(LOCAL_PATH)/../include 

LOCAL_SRC_FILES += $(LOCAL_PATH)/../../include/commonFunc.c

LOCAL_MODULE := FlyTest
include $(BUILD_SHARED_LIBRARY)

