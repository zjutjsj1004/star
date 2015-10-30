#ifndef __FORTUNE_SET_SCENE_H__
#define __FORTUNE_SET_SCENE_H__

#include "cocos2d.h"

class CPopupLayer;

class CFortuneSetScene : public cocos2d::Layer
{
public:
	CFortuneSetScene();
	~CFortuneSetScene();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(CFortuneSetScene);

private:
	void fortuneSetBtnClick(Ref *pRef);
	void createFortuneClickBtnLayer(int nBtnType);
	void showFortuneClickBtnLayer(int nBtnType);
private:
	CPopupLayer* m_pPopAboutStarLayer;
	CPopupLayer* m_pPopAboutAuthorLayer;
};

#endif // __FORTUNE_SET_SCENE_H__
