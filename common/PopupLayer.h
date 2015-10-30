/************************************************************************/
/* 作者:http://blog.sina.com.cn/s/blog_705a5ff00101ox4s.html                                                                     */
/************************************************************************/
#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
USING_NS_CC;
using namespace ui;

class CPopupLayer : public CCLayer {
public:
	CPopupLayer();
	~CPopupLayer();
	virtual bool init();

	//静态创建函数，创建一个弹出层，设置背景图片
	static CPopupLayer* create(const char* backgroundImage);

	//设置标题
	void setTitle(const char* title, int fontsize = 20);
	//设置文本内容，padding 为文字到对话框两边预留的距离，这是可控的，距上方的距离亦是如此
	void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddingTop = 100);

	//设置上层对象和上层回调函数，用于回调时传递CCNode参数
	void setCallBackFunc(CCObject* target, SEL_CallFuncN callfun);

	//添加menuItem按钮，封装了一个函数，传入些必要的参数
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);

	//为了在显示层时的属性生效，选择在onEnter里动态生成
	virtual void onEnter();
	virtual void onExit();

	void addPopLayerTouchEvent();
	void removePopLayerTouchEvent();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual bool onTouchesMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	CREATE_FUNC(CPopupLayer);

private:
	void buttonCallBack(CCObject* pSender);

	//文字内容两边的空白区域
	int m_contentPadding;
	int m_contentPaddingTop;
	CCObject* m_callbackListener;
	EventListenerTouchOneByOne* m_pPopLayerTouchListener;
	SEL_CallFuncN m_callback;
	//定义了CCMenu*类型变量m_pMenu, 并且直接定义默认的set/get方法
	CC_SYNTHESIZE_RETAIN(CCMenu*, m_pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(CCSprite*, m_sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m_s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_ltContentText, LabelContentText);
};

#endif // __POPUP_LAYER_H__
