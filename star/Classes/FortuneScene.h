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
	void readContentFullScene(Ref *pRef); //全屏查看星座信息
	void getFortuneContentHttp();
	void onHttpRequestCompleted(cocos2d::CCNode * sender, void * data);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void shareButtonClick();
#endif
private:
	int m_nFortuneType; //十二星座类型
	int m_nFortuneDay; /* 今天0，明天1，本周2，本月3，本年4 */
	std::map<int, std::string> m_dataSummaryMap;/* key:今天0，明天1，本周2，本月3，本年4 */
	Node* m_pRoot; //根节点
	Button* m_pFortuneDayBtnList[STAR_FORTUNE_FORTUNEDAY_SIZE];
	Text* m_pFortuneContentLabel[STAR_FORTUNE_FORTUNEDAY_SIZE]; //星座内容显示
	Button* m_pFortuneContentButton[STAR_FORTUNE_FORTUNEDAY_SIZE]; //星座阅读全文按钮
	EventListenerTouchOneByOne *m_pPageViewEventListener[STAR_FORTUNE_FORTUNEDAY_SIZE];
};

#endif // __FORTUNE_SCENE_H__
