#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "common.h"
#include "PopupLayer.h"
#include "FortuneSetScene.h"
#include "StarRapidJson.h"

USING_NS_CC;
using namespace ui;
#define FORTUNE_SET_BTN_COUNT  4   /* 星座设置界面按钮数 */
#define FORTUNE_SET_ABOUT_BTN  0   /* 星座设置界面关于星座按钮 */
#define FORTUNE_SET_AUTHOR_BTN 1   /* 星座设置界面关于作者按钮 */
#define FORTUNE_SET_RETURN_BTN 2   /* 星座设置界面返回按钮 */
#define FORTUNE_SET_QUIT_BTN   3   /* 星座设置界面退出星座按钮 */

#define FORTUNE_SET_POPLAYER_FONTSIZE 20
#define FORTUNE_SET_POPLAYER_PADDING 10
#define FORTUNE_SET_POPLAYER_PADDINGTOP 80

CFortuneSetScene::CFortuneSetScene()
{
	m_pPopAboutStarLayer = NULL;
	m_pPopAboutAuthorLayer = NULL;
}

CFortuneSetScene::~CFortuneSetScene()
{
	m_pPopAboutStarLayer = NULL;
	m_pPopAboutAuthorLayer = NULL;
}

Scene* CFortuneSetScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CFortuneSetScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CFortuneSetScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("FortuneSet/FortuneSetScene.csb");
	addChild(rootNode);

	for (int i = 0; i < FORTUNE_SET_BTN_COUNT; i++)
	{
		char szFortuneName[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
		sprintf(szFortuneName, "Button_%d", i);
		Button *pFortuneBtn = (rootNode->getChildByName<Button*>(szFortuneName));
		if (NULL == pFortuneBtn)
		{
			CCLOG("CFortuneSetScene Button Count Error");
			continue;
		}
		pFortuneBtn->setUserData((void*)i);
		pFortuneBtn->addClickEventListener(CC_CALLBACK_1(CFortuneSetScene::fortuneSetBtnClick, this));
	}

    return true;
}

void CFortuneSetScene::fortuneSetBtnClick(Ref *pRef)
{
	Button *pFortuneSetBtn = (Button*)pRef;
	if (NULL == pFortuneSetBtn)
	{
		CCLOG("CFortuneSetScene::fortuneSetBtnClick(NULL == pFortuneSetBtn)");
		return;
	}

	int nFortuneSetBtn = (int)pFortuneSetBtn->getUserData();
	CCLOG("CSelectStarScene::FortuneClick(nFortune = %d)", nFortuneSetBtn);

	switch (nFortuneSetBtn)
	{
	case FORTUNE_SET_ABOUT_BTN:
	{
		createFortuneClickBtnLayer(nFortuneSetBtn);
		showFortuneClickBtnLayer(nFortuneSetBtn);
		break;
	}
	case FORTUNE_SET_AUTHOR_BTN:
	{
		createFortuneClickBtnLayer(nFortuneSetBtn);
		showFortuneClickBtnLayer(nFortuneSetBtn);
		break;
	}
	case FORTUNE_SET_RETURN_BTN:
		Director::getInstance()->popScene();
		break;
	case FORTUNE_SET_QUIT_BTN:
		Director::getInstance()->end();
		break;
	default:
		CCLOG("CFortuneSetScene Button Count Error in fortuneSetBtnClick");
		break;
	}
}

void CFortuneSetScene::createFortuneClickBtnLayer(int nBtnType)
{
	if (FORTUNE_SET_ABOUT_BTN == nBtnType)
	{
		m_pPopAboutStarLayer = CPopupLayer::create("FortuneSet/PopLayer.png");
		// ContentSize是可选的设置，可以不设置，如果设置则把它当做9图缩放
		//popup->setContentSize(CCSizeMake(400, 360));
		m_pPopAboutStarLayer->setTitle(ReadString::getInstance()->parse(STAR_JSON_KEY_ABOUT_STAR).c_str());
		m_pPopAboutStarLayer->setContentText(ReadString::getInstance()->parse(STAR_JSON_KEY_FORTUNESET_STAR).c_str(), FORTUNE_SET_POPLAYER_FONTSIZE, FORTUNE_SET_POPLAYER_PADDING, FORTUNE_SET_POPLAYER_PADDINGTOP);
		// 设置回调函数，回调传回一个CCNode以获取tag判断点击的按钮
		// 这只是作为一种封装实现，如果使用delegate那就能够更灵活的控制参数了
		//popup->setCallBackFunc(this, callfuncN_selector(HelloWorld::buttonCallBack));
		//添加按钮，设置图片、文字，tag信息
		//popup->addButton("button.png", "button.png", "Ok", 0);
		//popup->addButton("button.png", "button.png", "Cancel", 1);
		this->addChild(m_pPopAboutStarLayer);
		m_pPopAboutStarLayer->setVisible(false);
	}

	if (FORTUNE_SET_AUTHOR_BTN == nBtnType)
	{
		m_pPopAboutAuthorLayer = CPopupLayer::create("FortuneSet/PopLayer.png");
		// ContentSize是可选的设置，可以不设置，如果设置则把它当做9图缩放
		//popup->setContentSize(CCSizeMake(400, 360));
		m_pPopAboutAuthorLayer->setTitle(ReadString::getInstance()->parse(STAR_JSON_KEY_ABOUT_AUTHOR).c_str());
		m_pPopAboutAuthorLayer->setContentText(ReadString::getInstance()->parse(STAR_JSON_KEY_FORTUNESET_AUTHOR).c_str(), FORTUNE_SET_POPLAYER_FONTSIZE, FORTUNE_SET_POPLAYER_PADDING, FORTUNE_SET_POPLAYER_PADDINGTOP);
		// 设置回调函数，回调传回一个CCNode以获取tag判断点击的按钮
		// 这只是作为一种封装实现，如果使用delegate那就能够更灵活的控制参数了
		//popup->setCallBackFunc(this, callfuncN_selector(HelloWorld::buttonCallBack));
		//添加按钮，设置图片、文字，tag信息
		//popup->addButton("button.png", "button.png", "Ok", 0);
		//popup->addButton("button.png", "button.png", "Cancel", 1);
		this->addChild(m_pPopAboutAuthorLayer);
		m_pPopAboutAuthorLayer->setVisible(false);
	}
}

void CFortuneSetScene::showFortuneClickBtnLayer(int nBtnType)
{
	if (FORTUNE_SET_AUTHOR_BTN == nBtnType)
	{
		m_pPopAboutAuthorLayer->setVisible(true);
		//m_pPopAboutStarLayer->setVisible(false);
	}
	else if (FORTUNE_SET_ABOUT_BTN == nBtnType)
	{
		//m_pPopAboutAuthorLayer->setVisible(false);
		m_pPopAboutStarLayer->setVisible(true);
	}
	else
	{
		m_pPopAboutAuthorLayer->setVisible(false);
		m_pPopAboutStarLayer->setVisible(false);
	}
}


