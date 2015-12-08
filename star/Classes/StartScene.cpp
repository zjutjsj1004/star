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
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isNetworkConnected", "()Z")) {
        r = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    if (r == false)
    {
        CCLOG("Android********************false");
    }
    else
    {
        CCLOG("Android********************true");
    }
#else
    CCLOG("*************************");
#endif
}
