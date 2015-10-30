/************************************************************************/
/* 作者:http://www.tuicool.com/articles/veM3ma                                                                     */
/************************************************************************/
#ifndef __STAR_RAPIDJSON_H__
#define __STAR_RAPIDJSON_H__

/*
* 获取字符串类 单例
* 用于获取JSON文件中的中文字符串
*/
#include "cocos2d.h"
#include <string> 
#include "cocostudio\CocoStudio.h" 
#include "ui\CocosGUI.h" 

USING_NS_CC;
using namespace std;
using namespace cocostudio;

/**
* 数据ID的宏定义，用于找到中文数据
*/
static int s_iExit = 1;  //再次按下返回键退出游戏 

class ReadString
{
protected:
	rapidjson::Document m_doc;    //暂存的数据
	static ReadString* m_pReadString;
public:
	static ReadString* getInstance();
	std::string parse(int key);
private:
	static ReadString* create(std::string fileName);
	bool init(std::string fileName);
	ReadString() {};
	~ReadString(void) {};
};

#endif // __POPUP_LAYER_H__
