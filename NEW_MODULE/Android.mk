LOCAL_PATH := $(my-dir)

SHELL_PATH := $(LOCAL_PATH)


include \
		$(LOCAL_PATH)/FlyAiAccessoryJni/Android.mk \
		$(LOCAL_PATH)/FlyBackcarJni/Android.mk \
		$(LOCAL_PATH)/FlyInertialNavJni/Android.mk \
		$(LOCAL_PATH)/FlyModuleJni/Android.mk \
		$(LOCAL_PATH)/flyaudiomodule/Android.mk 
		

