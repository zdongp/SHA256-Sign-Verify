# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

FLY_INCLUDE	:= $(LOCAL_PATH)/../../include
FLY_AUDIO_INCLUDE := $(LOCAL_PATH)/../include

FLYUTILS_INCLUDE := $(FLY_AUDIO_INCLUDE)/flyutils
FLYNATIVE_SERVICE_INCLUDE := $(FLY_AUDIOINCLUDE)/libflyaudioNativeServer
FLYMODULE_INCLUDE := $(FLY_AUDIO_INCLUDE)/flyaudiomodule
FLYDRIVER_INCLUDE := $(FLY_AUDIO_INCLUDE)/driver

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false


LOCAL_DNV_MODULE_INCLUDES :=$(FLYMODULE_INCLUDE) \
										$(FLY_AUDIO_INCLUDE) \
										$(LOCAL_PATH) \
										$(FLY_INCLUDE) \
										$(FLY_AUDIO_INCLUDE)/flyaudioObject \
										$(LOCAL_PATH)/libs \
										$(LOCAL_PATH)/include \
										ndk/sources/cxx-stl/stlport/stlport/\
										$(LOCAL_PATH)/FlyDNV \
										$(NDK_ROOT)/sources/cxx-stl/stlport/stlport \
										
LOCAL_INCLUDES := $(LOCAL_DNV_MODULE_INCLUDES)
LOCAL_C_INCLUDES := $(LOCAL_DNV_MODULE_INCLUDES)
LOCAL_CFLAGS := -D_STLP_USE_NO_IOSTREAMS -D_STLP_USE_MALLOC


LOCAL_SRC_FILES :=api.cpp\
					FlyDNV/DNVParam.cpp\
					FlyDNV/DNVApp.cpp \
					FlyDNV/DNVModule.cpp \
					FlyDNV/DNVHal.cpp
					

LOCAL_SRC_FILES += $(LOCAL_PATH)/../../include/commonFunc.c \
					$(FLYUTILS_INCLUDE)/debug.cpp \
					$(FLYUTILS_INCLUDE)/list.cpp \
					
LOCAL_LDLIBS:= -llog

#LOCAL_LDFLAGS +=	-L$(FLY_LIBS_OUT) -lflyaudiomodule -lflyutils \
									#$(LOCAL_PATH)/libs/libunicodestring.a \

LOCAL_MODULE :=  dnv.flyaudio

## For Android 2.3 using this TAGS ( eng, optional, debug, ...)
# DEBUG_DISABLE := true			# if true, disable logcat information

# Generate module config.h file && must be after LOCAL_MODULE
#include $(FLY_CONFIG_MK)

#LOCAL_MODULE_PATH := $(FLY_MODULE_OUT)
LOCAL_MODULE_RELATIVE_PATH := fa

include $(BUILD_SHARED_LIBRARY)


