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

LOCAL_SRC_FILES := api.cpp

LOCAL_SRC_FILES += 	libflyoperation/flyopen.c

LOCAL_SRC_FILES += 	app/appResponseCommand.cpp \
					app/appResponseFunction.cpp \
					app/appRequestCommand.cpp \
					app/appRequestFunction.cpp \
					


LOCAL_SRC_FILES += 	hal/halResponseCommand.cpp \
					hal/halResponseFunction.cpp \
					hal/halRequestFunction.cpp \

LOCAL_SRC_FILES +=	othermodule/otherModuleRequestCommand.cpp \
					othermodule/otherModuleRequestFunction.cpp \
					othermodule/otherModuleResponseCommand.cpp \
					othermodule/otherModuleResponseFunction.cpp \

LOCAL_SRC_FILES +=	moduleparam/moduleParamRequest.cpp \
					moduleparam/moduleParamResponse.cpp \
					FlySystemAbout.cpp \
					SteeringWheelStudy.cpp \

LOCAL_SRC_FILES += 	param/param.cpp \

LOCAL_SRC_FILES += 	flyJniSdk/CNotifyAndResponseFlyJniSdk.cpp \

LOCAL_SRC_FILES += timer/timer_interface.cpp \
					timer/TimerModuleResponseCommand.cpp \
					
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../include/commonFunc.c \
					$(FLYUTILS_INCLUDE)/debug.cpp \
					$(FLYUTILS_INCLUDE)/list.cpp \
					$(LOCAL_PATH)/../FlyModuleService/Tinyxml/tinyxml.cpp \
					$(LOCAL_PATH)/../FlyModuleService/Tinyxml/tinyxmlparser.cpp \
					$(LOCAL_PATH)/../FlyModuleService/Tinyxml/tinyxmlerror.cpp \
					$(LOCAL_PATH)/../FlyModuleService/Tinyxml/tinystr.cpp \

					
LOCAL_C_INCLUDES := 	$(FLY_INCLUDE)  \
			$(LOCAL_PATH) \
			$(FLY_AUDIO_INCLUDE) \
			$(LIB_FLYAUDIO_MODULE_DIR) \
			$(FLYMODULE_INCLUDE) \
			$(FLYDRIVER_INCLUDE) \
			$(FLY_AUDIO_INCLUDE)/flyaudioObject \
			$(LOCAL_PATH)/../FlyModuleService/Tinyxml \
			
			

LOCAL_C_INCLUDES += $(LOCAL_PATH)/define \
					$(LOCAL_PATH)/libs \
					$(LOCAL_PATH)/myModuleID \
					$(LOCAL_PATH)/app \
					$(LOCAL_PATH)/hal \
					$(LOCAL_PATH)/othermodule \
					$(LOCAL_PATH)/param \
					$(LOCAL_PATH)/moduleparam \
					$(LOCAL_PATH)/timer \
					$(LOCAL_PATH)/flyJniSdk \
					$(LOCAL_PATH)/libflyoperation \
					$(NDK_ROOT)/sources/cxx-stl/stlport/stlport \

#LOCAL_SHARED_LIBRARIES := liblog libcutils libstlport libtinyxml
#LOCAL_SHARED_LIBRARIES := liblog libcutils libtinyxml
LOCAL_LDLIBS:= -llog

#LOCAL_LDFLAGS +=	-L$(FLY_LIBS_OUT) -lflyaudiomodule \
									#-L$(FLY_LIBS_OUT) -lflyutils \
									#$(LOCAL_PATH)/libs/libunicodestring.a \
			 		 				#$(LOCAL_PATH)/libs/libproductinfo_access.so \
			 		 				#$(LOCAL_PATH)/libs/libflyoperation.so
LOCAL_CFLAGS := \
'-D_STLP_USE_NEWALLOC'

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := system_moran.flyaudio

## For Android 2.3 using this TAGS ( eng, optional, debug, ...)
LOCAL_MODULE_TAGS := optional

# Generate module config.h file && must be after LOCAL_MODULE
# DEBUG_DISABLE := true			# if true, disable logcat information
#include $(FLY_CONFIG_MK)

#LOCAL_MODULE_PATH := $(FLY_MODULE_OUT)
LOCAL_MODULE_RELATIVE_PATH := fa

include $(BUILD_SHARED_LIBRARY)


