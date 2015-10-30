#ifndef __FORTUNE_SCENE_H__
#define __FORTUNE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace ui;

class CFortune : public cocos2d::Layer
{
public:
	CFortune();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(const int nFortuneType);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(const int nFortuneType);

	// implement the "static create()" method manually
    //CREATE_FUNC(CFortune);
	static CFortune* create(const int nFortuneType);

private:
	void fortuneBottonBtnClick(Ref *pRef);
	void fortunTopItemClick(Ref *pRef);
	void pageViewEvent(Ref *pSender, PageViewEventType type);
	void createPageViewEventListener(const int nIndexBtn);
	bool pageViewTouchBegan(Touch *touch, Event *event);
	void pageViewTouchMoved(Touch *touch, Event *event);
	void pageViewTouchEnded(Touch *touch, Event *event);
	void setDayListBtnEnable(const int nIndexBtn);
	void formatPageviewTextContent();  
	void readContentFullScene(Ref *pRef); //ȫ���鿴������Ϣ
	void getFortuneContentHttp();
	void onHttpRequestCompleted(cocos2d::CCNode * sender, void * data);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void shareButtonClick();
#endif
private:
	int m_nFortuneType; //ʮ����������
	int m_nFortuneDay; /* ����0������1������2������3������4 */
	std::map<int, std::string> m_dataSummaryMap;/* key:����0������1������2������3������4 */
	Node* m_pRoot; //���ڵ�
	Button* m_pFortuneDayBtnList[STAR_FORTUNE_FORTUNEDAY_SIZE];
	Text* m_pFortuneContentLabel[STAR_FORTUNE_FORTUNEDAY_SIZE]; //����������ʾ
	Button* m_pFortuneContentButton[STAR_FORTUNE_FORTUNEDAY_SIZE]; //�����Ķ�ȫ�İ�ť
	EventListenerTouchOneByOne *m_pPageViewEventListener[STAR_FORTUNE_FORTUNEDAY_SIZE];
};

#endif // __FORTUNE_SCENE_H__
