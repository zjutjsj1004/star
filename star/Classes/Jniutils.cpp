#include "common.h"
#include "Jniutils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
bool JniUtils::JniUtils_isNetworkConnected()
{
    jboolean r = false;
    JniMethodInfo t;
#if 1
    //静态：getStaticMethodInfo判断java定义的静态函数是否存在，返回bool
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isNetworkConnected", "()Z"))
    {
        r = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        if (r == false)
        {
            CCLOG("Android isNetworkConnected false");
        }
        else
        {
            CCLOG("Android isNetworkConnected true");
        }
        t.env->DeleteLocalRef(t.classID);
        return r;
    }
#else
    //非静态
    //http://stackoverflow.com/questions/18332343/jni-android-call-to-non-static-method-in-java-from-c
    //http://stackoverflow.com/questions/9568095/how-to-make-a-proper-call-from-android-to-a-non-static-function-in-java-cocos2
    //http://blog.163.com/yg_qi/blog/static/9672173520141993728533/
    //http://www.cnblogs.com/luxiaofeng54/archive/2011/08/17/2142000.html
    //http://blog.csdn.net/dj0379/article/details/18217323
    //http://www.cocos.com/doc/tutorial/show?id=1308
    bool ret = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isNetworkConnected", "()Z");

#endif

}

#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
bool JniUtils::JniUtils_isNetworkConnected()
{
    return false;
}
#endif

