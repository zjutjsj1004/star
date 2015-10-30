#include "common.h"
#include "SelectStarScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "FortuneScene.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

Scene* CSelectStarScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CSelectStarScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CSelectStarScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("SelectStarScene/SelectStarScene.csb");
	
	for (int i = 0; i < STAR_FORTUNE_COUNT; i++)
	{
		char szFortuneName[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
		sprintf(szFortuneName, "Button_%d", i);
		Button *pFortuneBtn = (rootNode->getChildByName<Button*>(szFortuneName));
		pFortuneBtn->setUserData((void*)i);
		pFortuneBtn->addClickEventListener(CC_CALLBACK_1(CSelectStarScene::fortuneBtnClick, this));
	}

    addChild(rootNode);

    return true;
}

void CSelectStarScene::fortuneBtnClick(Ref *pRef)
{
	Button *pFortuneBtn = (Button*)pRef;
	if (NULL == pFortuneBtn)
	{
		CCLOG("CSelectStarScene::FortuneClick(NULL == pFortuneBtn)");
		return;
	}

	int nFortune = (int)pFortuneBtn->getUserData();
	CCLOG("CSelectStarScene::FortuneClick(nFortune = %d)", nFortune);

	Scene *pFortuneScene = CFortune::createScene(nFortune);
	
	if (NULL != pFortuneScene)
	{
		Director::getInstance()->replaceScene(pFortuneScene);
	}
	CCLOG("CSelectStarScene::fortuneBtnClick");

}


