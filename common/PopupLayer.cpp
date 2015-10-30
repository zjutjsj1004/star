#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "PopupLayer.h"

USING_NS_CC;
using namespace ui;


// 构造函数中变量设初值
CPopupLayer::CPopupLayer()
{
	m_contentPadding = 0;
	m_contentPaddingTop = 0;
	m_pMenu = NULL;
	m_callbackListener = NULL;
	m_callback = NULL;
	m_sfBackGround = NULL;
	m_s9BackGround = NULL;
	m_ltContentText = NULL;
	m_ltTitle = NULL;
	m_pPopLayerTouchListener = NULL;
}

//释放
CPopupLayer::~CPopupLayer()
{
	CC_SAFE_RELEASE(m_pMenu);
	CC_SAFE_RELEASE(m_sfBackGround);
	CC_SAFE_RELEASE(m_s9BackGround);
	CC_SAFE_RELEASE(m_ltContentText);
	CC_SAFE_RELEASE(m_ltTitle);
}

//初始化
bool CPopupLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}

	this->setContentSize(Size(0, 0));
	//初始化需要的Menu
	CCMenu* menu = CCMenu::create();
	menu->setPosition(CCPoint(0,0));
	setMenuButton(menu);  //set()方法
	setTouchEnabled(true);  //开启触摸响应
	return true;
}

//创建一个弹出层，给背景精灵变量赋值
CPopupLayer* CPopupLayer::create(const char* backgroundImage) {
	CPopupLayer* popup = CPopupLayer::create();
	Sprite *pBackgroundSprite = Sprite::create(backgroundImage);
	popup->setSpriteBackGround(pBackgroundSprite);

	Scale9Sprite* pBackgroundScale9Sprite = Scale9Sprite::create(backgroundImage);
	popup->setSprite9BackGround(pBackgroundScale9Sprite);
	return popup;
}

//给标题变量赋值
void CPopupLayer::setTitle(const char* title, int fontsize) {
	CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "Arial", fontsize);
	ltfTitle->setColor(ccc3(0, 0, 0));
	setLabelTitle(ltfTitle);
}

//给文本变量赋值
void CPopupLayer::setContentText(const char* text, int fontsize, int padding, int paddingTop) {
	CCLabelTTF* content = CCLabelTTF::create(text, "Arial", fontsize);
	content->setColor(ccc3(0, 0, 0));
	setLabelContentText(content);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

//给下层层变量和回调函数变量赋值
void CPopupLayer::setCallBackFunc(CCObject* target, SEL_CallFuncN callfun) {
	m_callbackListener = target;
	m_callback = callfun;
}

//给menu菜单变量添加Item
bool CPopupLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(winSize.width / 2, winSize.height / 2);

	// 创建图片菜单按钮
	CCMenuItemImage* menuImage = CCMenuItemImage::create(
		normalImage, selectedImage, this, menu_selector(CPopupLayer::buttonCallBack));
	menuImage->setTag(tag);
	menuImage->setPosition(center);

	// 添加文字说明并设置位置
	CCSize menuSize = menuImage->getContentSize();
	CCLabelTTF* ttf = CCLabelTTF::create(title, "Arial", 15);
	ttf->setColor(ccc3(0, 0, 0));
	ttf->setPosition(ccp(menuSize.width / 2, menuSize.height / 2));
	menuImage->addChild(ttf);

	getMenuButton()->addChild(menuImage);
	return true;
}

//销毁弹出框，传递参数node给下层
void CPopupLayer::buttonCallBack(CCObject* pSender) {
	CCNode *node = (CCNode*)pSender;
	CCLOG("touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener)
	{
		//执行HelloWorld层的回调函数，传递node参数
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParentAndCleanup(true);
}

//全部参数都设定好后，在运行时动态加载
void CPopupLayer::onEnter() {
	CCLayer::onEnter();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(winSize.width / 2, winSize.height / 2);
	CCSize contentSize;
	// 设定好参数，在运行时加载
	if (getContentSize().equals(Size::ZERO)) {
		CCSprite* p = getSpriteBackGround();
		p->setPosition(center);
		this->addChild(getSpriteBackGround(), 0, 0);
		contentSize = getSpriteBackGround()->getTexture()->getContentSize();
	}
	else {
		Scale9Sprite* background = getSprite9BackGround();
		background->setContentSize(getContentSize());
		background->setPosition(center);
		this->addChild(background, 0);
		contentSize = getContentSize();
	}

	//添加按钮，并根据Item的个数设置其位置
	this->addChild(getMenuButton());
	float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
	Vector<Node*> array = getMenuButton()->getChildren();
	int i = 0;
	for (CCObject* pObj:array) {
		CCNode *node = (CCNode*)pObj;

		node->setPosition(ccp(winSize.width / 2 - contentSize.width / 2 + btnWidth*(i + 1),
			winSize.height / 2 - contentSize.height / 3));
		i++;
	}

	// 显示对话框标题
	if (getLabelTitle()) {
		getLabelTitle()->setPosition(ccpAdd(center, ccp(0, contentSize.height / 2 - 25.0f)));
		this->addChild(getLabelTitle());
	}

	//显示文本内容
	if (getLabelContentText()) {
		CCLabelTTF* ltf = getLabelContentText();
		ltf->setPosition(center);
		ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ltf);
	}

	//弹出效果
	CCSequence *popupActions = CCSequence::create(
		CCScaleTo::create(0.0, 0.0),
		CCScaleTo::create(0.06, 1.05),
		CCScaleTo::create(0.08, 0.95),
		CCScaleTo::create(0.08, 1.0), NULL);
	this->runAction(popupActions);

	addPopLayerTouchEvent();

}

//退出
void CPopupLayer::onExit() {
	removePopLayerTouchEvent();
	CCLayer::onExit();
}

void CPopupLayer::addPopLayerTouchEvent()
{
	CCLOG("CPopupLayer::addPopLayerTouchEvent");
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	if (NULL != m_pPopLayerTouchListener)
	{
		return;
	}
	m_pPopLayerTouchListener = EventListenerTouchOneByOne::create();
	m_pPopLayerTouchListener->onTouchBegan = CC_CALLBACK_2(CPopupLayer::onTouchBegan, this);
	m_pPopLayerTouchListener->onTouchMoved = CC_CALLBACK_2(CPopupLayer::onTouchMoved, this);
	m_pPopLayerTouchListener->onTouchEnded = CC_CALLBACK_2(CPopupLayer::onTouchEnded, this);
	m_pPopLayerTouchListener->setSwallowTouches(true);//true不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(m_pPopLayerTouchListener, this);
}

void CPopupLayer::removePopLayerTouchEvent()
{
	CCLOG("CPopupLayer::removePopLayerTouchEvent");
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->removeEventListener(m_pPopLayerTouchListener);
}


bool CPopupLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("CPopupLayer::onTouchBegan");
	return true;
}

bool CPopupLayer::onTouchesMoved(Touch *touch, Event *unused_event)
{
	CCLOG("CPopupLayer::onTouchesMoved");
	return true;
}

void CPopupLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	CCLOG("CPopupLayer::onTouchEnded");
	removeFromParentAndCleanup(true);
	return;
}
