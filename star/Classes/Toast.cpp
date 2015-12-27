#include "Toast.h"
#include "VisibleRect.h"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;
using namespace ui;

enum 
{
	kTagToast = 0x7fffffff,
};
Toast * Toast::create(int duration)
{
	return create("", duration);
}

Toast * Toast::create(const char * n, int duration)
{
	Toast * t = new Toast;
	if (t && t->init(n, duration))
	{
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}

bool Toast::init(const char* string ,int duration)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::init());
		//CCLabelTTF *label = CCLabelTTF::create(string,"Arial", 28);
		CCLabelTTF *label = CCLabelTTF::create(string, "Arial", 28,
			CCSizeMake(0,45), kCCTextAlignmentCenter, 
			kCCVerticalTextAlignmentCenter);
		label->setColor(ccc3(255,255,255));
		Scale9Sprite* c9s = Scale9Sprite::create("res/Toast/toast_bg.png");
		CCSize labelSize = label->getContentSize();
		label->setPosition(ccp((labelSize.width + 100)/2, 45/2));
		label->setAnchorPoint(ccp(0.5,0.5));
		
		CCSize c9sSize = CCSizeMake(labelSize.width + 100, 45);
		c9s->setContentSize(c9sSize);
		
		addChild(c9s);
		addChild(label);
		c9s->setPosition(Vec2::ZERO); //2.2.6Ê¹ÓÃCCPointZero
		c9s->setAnchorPoint(Vec2::ZERO);
		
		setContentSize(c9s->getContentSize());
		m_Duration = duration;
		setVisible(false);
		setScaleX(0);
		ret = true;
	} while (0);
	
	return ret;
}

void Toast::show(const char * string, int duration, CCNode * parent)
{
	CCNode * n = parent->getChildByTag(kTagToast);
	if (n != NULL)
	{
		parent->removeChildByTag(kTagToast);
	}
	
	Toast * toast = Toast::create(string, duration);
	toast->setPosition(VisibleRect::center());
	toast->setAnchorPoint(ccp(0.5, 0.5));
	parent->addChild(toast,200, kTagToast);
	toast->show();
}

void Toast::show()
{
	setVisible(true);
	CCActionInterval*  actionTo = CCScaleTo::create(.3f, 1.0f,1.0f);
	CCActionInterval* scale_ease_out  = CCEaseOut::create(actionTo, 2.5f);
	this->runAction(scale_ease_out);
	if (m_Duration == TOAST_SHORT)
	{
		scheduleOnce(SEL_SCHEDULE(&Toast::remove), 3);
	}
	else if (m_Duration == TOAST_LONG)
	{
		scheduleOnce(SEL_SCHEDULE(&Toast::remove), 5);
	}else if(m_Duration == TOAST_INFINITE)
	{
	}
	else
	{
		scheduleOnce(SEL_SCHEDULE(&Toast::remove), m_Duration);
	}
}

void Toast::show( const char * string, int duration, CCNode * parent, CCPoint point )
{
	CCNode * n = parent->getChildByTag(kTagToast);
	if (n != NULL)
	{
		parent->removeChildByTag(kTagToast);
	}

	Toast * toast = Toast::create(string, duration);
	toast->setPosition(point);
	toast->setAnchorPoint(ccp(0.5, 0.5));
	parent->addChild(toast,200, kTagToast);
	toast->show();
}

void Toast::dismiss(CCNode * parent)
{
	parent->removeChildByTag(kTagToast);
}

void Toast::remove(float dt)
{
	this->removeFromParent();
}