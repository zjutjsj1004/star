#include "common.h"
#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SelectStarScene.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CStar::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CStar::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CStar::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

	CCFadeOut *pFadeOutAction = CCFadeOut::create(1);
	CCCallFunc *cal = CCCallFunc::create(rootNode, callfunc_selector(CStar::EnterSelectStarScene));
	CCSequence *seo = CCSequence::create(pFadeOutAction, cal, NULL);
	rootNode->runAction(seo);


    addChild(rootNode);

    return true;
}

void CStar::EnterSelectStarScene()
{
	Scene *pSelectStarScene = CSelectStarScene::createScene();
	if (NULL != pSelectStarScene)
	{
		Director::getInstance()->replaceScene(pSelectStarScene);
	}
	CCLOG("CStar::EnterSelectStarScene");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    jboolean r = false;
    JniMethodInfo t;
#if 0
    //¾²Ì¬
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isNetworkConnected", "()Z"))
    {
        r = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        if (r == false)
        {
            CCLOG("Android********************false");
        }
        else
        {
            CCLOG("Android********************true");
        }
        t.env->DeleteLocalRef(t.classID);
    }
#else
    //·Ç¾²Ì¬
    //http://stackoverflow.com/questions/18332343/jni-android-call-to-non-static-method-in-java-from-c
    //http://stackoverflow.com/questions/9568095/how-to-make-a-proper-call-from-android-to-a-non-static-function-in-java-cocos2
    //http://blog.163.com/yg_qi/blog/static/9672173520141993728533/
    //http://www.cnblogs.com/luxiaofeng54/archive/2011/08/17/2142000.html
    //http://blog.csdn.net/dj0379/article/details/18217323
    //http://www.cocos.com/doc/tutorial/show?id=1308
    bool ret = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isNetworkConnected", "()Z");

#endif
 
    

   


#else
    CCLOG("*************************");
#endif
}
