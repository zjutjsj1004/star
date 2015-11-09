LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp
#widcard为扩展通配符
#遍历目录和子目录
define walk
 $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef
#遍历路径Classes下得目录和子目录文件，并存入ALLFILES变量中
ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
ALLFILESPRO = $(call walk, $(LOCAL_PATH)/../../../common/protobuf-lite)
ALLFILES += $(ALLFILESPRO)
#从ALLFILES目录中提取文件，并存入FILE_LIST中
#.cc是Linux/Unix下为C++源文件的默认扩展名,与.cpp一个意思
#.c 因为我要用到sqlite3.c  
FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(filter %.cpp, $(ALLFILES))
FILE_LIST += $(filter %.c, $(ALLFILES))
FILE_LIST += $(filter %.cc, $(ALLFILES))
FILE_LIST += $(LOCAL_PATH)/../../../common/StarRapidJson.cpp 
FILE_LIST += $(LOCAL_PATH)/../../../common/PopupLayer.cpp 
FILE_LIST += $(LOCAL_PATH)/../../../common/protobuf/starPB.cpp 


#搜索Classes下的子目录文件
FILE_INCLUDES += $(shell find $(LOCAL_PATH)/../../Classes -type d)
FILE_INCLUDES_PROTO += $(shell find $(LOCAL_PATH)/../../../common/protobuf-lite -type d)
FILE_INCLUDES += $(FILE_INCLUDES_PROTO)
#根据搜索到的文件名 编译资源文件
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
#提供搜索文件的路径
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
  $(FILE_INCLUDES) \
  $(LOCAL_PATH)/../../../common \
  $(LOCAL_PATH)/../../../common/protobuf \
  $(LOCAL_PATH)/../../../common/protobuf-lite 


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
