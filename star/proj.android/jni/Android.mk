LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/StartScene.cpp \
				   ../../Classes/SelectStarScene.cpp \
				   ../../Classes/FortuneScene.cpp \
				   ../../Classes/FortuneSetScene.cpp \
				   ../../../common/StarRapidJson.cpp \
				   ../../../common/PopupLayer.cpp \
../../Classes/Cocos2dx/Android/CCUMSocialController.cpp  \
../../Classes/Cocos2dx/ShareButton/UMShareButton.cpp \
../../Classes/Cocos2dx/Common/CCUMSocialSDK.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
				$(LOCAL_PATH)/../../../common 


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
