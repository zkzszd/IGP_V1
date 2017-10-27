LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libIGP
LOCAL_ARM_MODE := arm
LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_SRC_FILES := 	../Adapter/SpaceAdapter.cpp \
					\
					../ImageInfo/IGPBitmap.cpp \
					../ImageInfo/IGPBitmapBase.cpp \
					../ImageInfo/IGPBitmapHSL.cpp \
					\
					../ProcessModule/BlurModule.cpp \
					../ProcessModule/FilletModule.cpp \
					../ProcessModule/GrayModule.cpp \
					../ProcessModule/ZoomModule.cpp \
					\
					../Typedef/_struct.cpp \
					\
					../Util/UtilAllocator.cpp \
					../Util/UtilMath.cpp

LOCAL_CFLAGS           := #-Wall -g -gdwarf-3
LOCAL_LDFLAGS          := #-Wl,-Map,xxx.map
LOCAL_LDLIBS := -lGLESv1_CM -llog -L$(DIRECTORY_TO_OBJ)

include $(BUILD_SHARED_LIBRARY)
