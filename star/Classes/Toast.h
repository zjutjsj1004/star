#ifndef __TOAST_H__
#define __TOAST_H__
#include "cocos2d.h"

USING_NS_CC;
enum 
{
	TOAST_LONG = -1,
	TOAST_SHORT = -2,
	TOAST_INFINITE = -3,
};

class Toast:public CCSprite
{
public:
	static void show(const char * string, int duration, CCNode * parent);
	static void dismiss(CCNode * parent);
	static void show(const char * string, int duration, CCNode * parent, CCPoint point);
private:
	virtual bool init(const char* string ,int duration);
	void remove(float dt);
	void show();
	static Toast * create(int duration);
	static Toast * create(const char * string, int duration);
	
	CC_SYNTHESIZE(int, m_Duration, Duration);

};




#endif

