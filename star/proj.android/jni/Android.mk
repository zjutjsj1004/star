LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp
#widcardΪ��չͨ���
#����Ŀ¼����Ŀ¼
define walk
 $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef
#����·��Classes�µ�Ŀ¼����Ŀ¼�ļ���������ALLFILES������
ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
ALLFILESPRO = $(call walk, $(LOCAL_PATH)/../../../common/protobuf-lite)
ALLFILES += $(ALLFILESPRO)
#��ALLFILESĿ¼����ȡ�ļ���������FILE_LIST��
#.cc��Linux/Unix��ΪC++Դ�ļ���Ĭ����չ��,��.cppһ����˼
#.c ��Ϊ��Ҫ�õ�sqlite3.c  
FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(filter %.cpp, $(ALLFILES))
FILE_LIST += $(filter %.c, $(ALLFILES))
FILE_LIST += $(filter %.cc, $(ALLFILES))
FILE_LIST += $(LOCAL_PATH)/../../../common/StarRapidJson.cpp 
FILE_LIST += $(LOCAL_PATH)/../../../common/PopupLayer.cpp 
FILE_LIST += $(LOCAL_PATH)/../../../common/protobuf/starPB.cpp 


#����Classes�µ���Ŀ¼�ļ�
FILE_INCLUDES += $(shell find $(LOCAL_PATH)/../../Classes -type d)
FILE_INCLUDES_PROTO += $(shell find $(LOCAL_PATH)/../../../common/protobuf-lite -type d)
FILE_INCLUDES += $(FILE_INCLUDES_PROTO)
#�������������ļ��� ������Դ�ļ�
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
#�ṩ�����ļ���·��
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
