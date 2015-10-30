/************************************************************************/
/* ����:http://www.tuicool.com/articles/veM3ma                                                                     */
/************************************************************************/
#ifndef __STAR_RAPIDJSON_H__
#define __STAR_RAPIDJSON_H__

/*
* ��ȡ�ַ����� ����
* ���ڻ�ȡJSON�ļ��е������ַ���
*/
#include "cocos2d.h"
#include <string> 
#include "cocostudio\CocoStudio.h" 
#include "ui\CocosGUI.h" 

USING_NS_CC;
using namespace std;
using namespace cocostudio;

/**
* ����ID�ĺ궨�壬�����ҵ���������
*/
static int s_iExit = 1;  //�ٴΰ��·��ؼ��˳���Ϸ 

class ReadString
{
protected:
	rapidjson::Document m_doc;    //�ݴ������
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
