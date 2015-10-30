/************************************************************************/
/* ����:http://blog.sina.com.cn/s/blog_705a5ff00101ox4s.html                                                                     */
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

	//��̬��������������һ�������㣬���ñ���ͼƬ
	static CPopupLayer* create(const char* backgroundImage);

	//���ñ���
	void setTitle(const char* title, int fontsize = 20);
	//�����ı����ݣ�padding Ϊ���ֵ��Ի�������Ԥ���ľ��룬���ǿɿصģ����Ϸ��ľ����������
	void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddingTop = 100);

	//�����ϲ������ϲ�ص����������ڻص�ʱ����CCNode����
	void setCallBackFunc(CCObject* target, SEL_CallFuncN callfun);

	//���menuItem��ť����װ��һ������������Щ��Ҫ�Ĳ���
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);

	//Ϊ������ʾ��ʱ��������Ч��ѡ����onEnter�ﶯ̬����
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

	//�����������ߵĿհ�����
	int m_contentPadding;
	int m_contentPaddingTop;
	CCObject* m_callbackListener;
	EventListenerTouchOneByOne* m_pPopLayerTouchListener;
	SEL_CallFuncN m_callback;
	//������CCMenu*���ͱ���m_pMenu, ����ֱ�Ӷ���Ĭ�ϵ�set/get����
	CC_SYNTHESIZE_RETAIN(CCMenu*, m_pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(CCSprite*, m_sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m_s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_ltContentText, LabelContentText);
};

#endif // __POPUP_LAYER_H__
