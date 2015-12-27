#ifndef __STAR_JNIUTIL_H__
#define __STAR_JNIUTIL_H__

/*
* Jni
*/
#include "cocos2d.h"
#include <string> 
#include "cocostudio\CocoStudio.h" 
#include "ui\CocosGUI.h" 

USING_NS_CC;
using namespace std;
using namespace cocostudio;


class JniUtils
{
public:
    static bool JniUtils_isNetworkConnected();
};

#endif // __STAR_JNIUTIL_H__
