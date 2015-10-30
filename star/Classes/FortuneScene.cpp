#include <iostream>
#include <map>
#include <string>

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "ui/GUIExport.h"
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "network/HttpClient.h"
#include "common.h"
#include "FortuneScene.h"
#include "SelectStarScene.h"
#include "FortuneSetScene.h"
#include "StarRapidJson.h"
#include "PopupLayer.h"
#include "starNetwork.h"
#define STAR_SHAREPIC_URL ("http://img1.imgtn.bdimg.com/it/u=4258453319,853384752&fm=15&gp=0.jpg")
#define STAR_SHAREPIC_LOCALURL ("res/umeng_socialize_sharepic.png")
#define STAR_SHARE_URL ("http://www.alonegames.com")


#define FORTUNE_POPLAYER_FONTSIZE 20
#define FORTUNE_POPLAYER_PADDING 10
#define FORTUNE_POPLAYER_PADDINGTOP 80

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// ������ص�ͷ�ļ�
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/Common/CCUMTypeDef.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
#include "Cocos2dx/Android/CCUMSocialController.h"
// ʹ����������ռ�
USING_NS_UM_SOCIAL;


/*
* ����ص�, �ûص�����ĳ����ĳ�Ա������ ����һ����ͨ�ĺ���, ����ʹ�òο�HelloWorldScene������
* @param platform Ҫ������Ŀ��ƽ̨
* @param stCode ������, 200�������ɹ�, 100����ʼ����
* @param errorMsg ����ʧ��ʱ�Ĵ�����Ϣ,androidƽ̨û�д�����Ϣ
*/
void shareCallback(int platform, int stCode, string& errorMsg)
{
	if (stCode == 100)
	{
		CCLog("#### HelloWorld ��ʼ����");
	}
	else if (stCode == 200)
	{
		CCLog("#### HelloWorld ����ɹ�");
	}
	else
	{
		CCLog("#### HelloWorld �������");
	}

	CCLog("platform num is : %d.", platform);
}
#endif


USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
using namespace network;
using namespace std;

const char* gszFortuneDayPanel[STAR_FORTUNE_FORTUNEDAY_SIZE] =
{
	"Panel_Today",
	"Panel_Tomorrow",
	"Panel_Week",
	"Panel_Month",
	"Panel_Year"
};

const char* gszFortuneConsName[STAR_FORTUNE_COUNT] =
{
	"%E7%99%BD%E7%BE%8A%E5%BA%A7",
	"%E9%87%91%E7%89%9B%E5%BA%A7",
	"%E5%8F%8C%E5%AD%90%E5%BA%A7",
	"%E5%B7%A8%E8%9F%B9%E5%BA%A7",
	"%E7%8B%AE%E5%AD%90%E5%BA%A7",
	"%E5%A4%84%E5%A5%B3%E5%BA%A7",
	"%E5%A4%A9%E7%A7%A4%E5%BA%A7",
	"%E5%A4%A9%E8%9D%8E%E5%BA%A7",
	"%E5%B0%84%E6%89%8B%E5%BA%A7",
	"%E6%91%A9%E7%BE%AF%E5%BA%A7",
	"%E6%B0%B4%E7%93%B6%E5%BA%A7",
	"%E5%8F%8C%E9%B1%BC%E5%BA%A7"
};

const char* gszFortuneDayDescript[STAR_FORTUNE_FORTUNEDAY_SIZE]
{
	"today",
	"tomorrow",
	"week",
	"month",
	"year"
};

CFortune::CFortune()
{
	m_pRoot = NULL;
	for (int i = 0; i < STAR_FORTUNE_FORTUNEDAY_SIZE; i++)
	{
		m_pFortuneContentLabel[i] = NULL;
		m_pFortuneContentButton[i] = NULL;
		m_pPageViewEventListener[i] = NULL;
	}

	m_nFortuneType = 0;
	m_nFortuneDay = 0;
}


Scene* CFortune::createScene(const int nFortuneType)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CFortune::create(nFortuneType);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
CFortune* CFortune::create(const int nFortuneType)
{
	CFortune *pRet = new(std::nothrow) CFortune();
	if (pRet && pRet->init(nFortuneType))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}

}

// on "init" you need to initialize your instance
bool CFortune::init(const int nFortuneType)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	m_nFortuneType = nFortuneType;

	CCLOG("CFortune::initWhenEnter(nFortuneType = %d)", nFortuneType);
	if (!m_pRoot)
	{
		m_pRoot = CSLoader::createNode("FortuneScene/FortuneScene.csb");
		addChild(m_pRoot);
	}

	char szTopBtnName[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
	sprintf(szTopBtnName, "SelectStarScene/%s", gszFortuneName[nFortuneType]);
	CCLOG("szTopBtnName:%s", szTopBtnName);
	Button *pFortunePicBtn = (m_pRoot->getChildByName<Button*>("FortunePic"));
	pFortunePicBtn->loadTextures(szTopBtnName, szTopBtnName, szTopBtnName, Widget::TextureResType::LOCAL);
	m_pRoot->addChild(pFortunePicBtn);

	//��������
	for (int i = 0; i < STAR_FORTUNE_FORTUNEDAY_SIZE; i++)
	{
		Layout *pFortuneDayLayout = (m_pRoot->getChildByName<Layout*>("Panel_DayList"));
		char szDayListBtnName[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
		sprintf(szDayListBtnName, "Button_%d", i);
		m_pFortuneDayBtnList[i] = (pFortuneDayLayout->getChildByName<Button*>(szDayListBtnName));
	}

	//������Ϣ������ʾ
	PageView* pPageView = (m_pRoot->getChildByName<PageView*>("PageView_StarContent"));
	m_nFortuneDay = pPageView->getCurPageIndex(); /* ��ȡ��ǰpageindex */
	pPageView->addEventListenerPageView(this, pagevieweventselector(CFortune::pageViewEvent));

	for (int i = 0; i < STAR_FORTUNE_FORTUNEDAY_SIZE; i++)
	{
		Layout *pFortuneContentLayout = (pPageView->getChildByName<Layout*>(gszFortuneDayPanel[i]));
		if (NULL != m_pFortuneContentLabel[i])
		{
			CCLOG("error:NULL != pFortuneContentLayout");
		}
		else
		{
			m_pFortuneContentLabel[i] = pFortuneContentLayout->getChildByName<Text*>("Content");
			Size nSize = m_pFortuneContentLabel[m_nFortuneDay]->getTextAreaSize(); //��ʾ�ɻ��Ƶ��������ص�
			CCLOG(">>>>>>>>>>>>>>>>> nSize:%f,%f <<<<<<<<<<<<<<<<<<<<<<<<<<", nSize.width, nSize.height);

			//createPageViewEventListener(i);
		}

		if (NULL != m_pFortuneContentButton[i])
		{
			CCLOG("error:NULL != m_pFortuneContentButton");
		}
		else
		{
			m_pFortuneContentButton[i] = pFortuneContentLayout->getChildByName<Button*>("Button");
			m_pFortuneContentButton[i]->setUserData((void*)i);
			m_pFortuneContentButton[i]->addClickEventListener(CC_CALLBACK_1(CFortune::readContentFullScene, this));
			//createPageViewEventListener(i);
		}
	}


	//�ײ���ť
	Layout *pFortuneBottomLayout = (m_pRoot->getChildByName<Layout*>("Panel_Bottom"));
	if (NULL != pFortuneBottomLayout)
	{
		for (int i = 0; i < STAR_FORTUNE_BOTTON_SIZE; i++)
		{
			char szFortuneName[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
			sprintf(szFortuneName, "Button_%d", i);
			Button *pFortuneBtn = (pFortuneBottomLayout->getChildByName<Button*>(szFortuneName));
			pFortuneBtn->setUserData((void*)i);
			pFortuneBtn->addClickEventListener(CC_CALLBACK_1(CFortune::fortuneBottonBtnClick, this));
		}
	}

	setDayListBtnEnable(m_nFortuneDay);

	return true;
}

void CFortune::fortuneBottonBtnClick(Ref *pRef)
{
	Button *pFortuneBtn = (Button*)pRef;
	if (NULL == pFortuneBtn)
	{
		CCLOG("CFortune::fortuneBottonBtnClick(NULL == pFortuneBtn)");
		return;
	}
	int nFortuneButton = (int)pFortuneBtn->getUserData();
	CCLOG("CFortune::fortuneBottonBtnClick(nFortuneButton = %d)", nFortuneButton);

	switch (nFortuneButton)
	{
	case STAR_FORTUNE_BOTTON_YUNSHI:
	{
		Scene *pSelectStarScene = CSelectStarScene::createScene();
		if (NULL != pSelectStarScene)
		{
			Director::getInstance()->replaceScene(pSelectStarScene);
		}
		break;
	}
	case STAR_FORTUNE_BOTTON_SHARE:
	{
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		shareButtonClick();
		#endif
		break;
	}
	case STAR_FORTUNE_BOTTON_DISCOVERY:
		break;
	case STAR_FORTUNE_BOTTON_SET:
	{
		Scene *pFortuneSetScene = CFortuneSetScene::createScene();
		if (NULL != pFortuneSetScene)
		{
			Director::getInstance()->pushScene(pFortuneSetScene);
		}
	}
		break;
	default:
		break;
	}

	return;
}

void CFortune::fortunTopItemClick(Ref *pRef)
{
	CCLOG("CFortune::fortunTopItemClick");
	return;
}


void CFortune::pageViewEvent(Ref *pSender, PageViewEventType type)
{
	if (PAGEVIEW_EVENT_TURNING == type)
	{
		if (NULL != m_pRoot)
		{
			PageView* pPageView = (m_pRoot->getChildByName<PageView*>("PageView_StarContent"));
			int nPageIndex = pPageView->getCurPageIndex(); /* ��ȡ��ǰpageindex */
			m_nFortuneDay = nPageIndex;
			setDayListBtnEnable(m_nFortuneDay);
		}
	}
	else
	{
		CCLOG("Enter error branche in CFortune::pageViewEvent");
	}
}

void CFortune::createPageViewEventListener(const int nIndexBtn)
{
	CCLOG("CFortune::createPageViewEventListener");

	if (NULL == m_pPageViewEventListener[nIndexBtn])
	{
		m_pPageViewEventListener[nIndexBtn] = EventListenerTouchOneByOne::create();
	}

	char szTopBtnName[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
	sprintf(szTopBtnName, "SelectStarScene/%s", gszFortuneName[1]);
	CCLOG("szTopBtnName:%s", szTopBtnName);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	m_pPageViewEventListener[nIndexBtn] = EventListenerTouchOneByOne::create();
	m_pPageViewEventListener[nIndexBtn]->onTouchBegan = CC_CALLBACK_2(CFortune::pageViewTouchBegan, this);
	m_pPageViewEventListener[nIndexBtn]->onTouchMoved = CC_CALLBACK_2(CFortune::pageViewTouchMoved, this);
	m_pPageViewEventListener[nIndexBtn]->onTouchEnded = CC_CALLBACK_2(CFortune::pageViewTouchEnded, this);
	m_pPageViewEventListener[nIndexBtn]->setSwallowTouches(true);//true�����´��ݴ���
	dispatcher->addEventListenerWithSceneGraphPriority(m_pPageViewEventListener[nIndexBtn], m_pFortuneContentLabel[nIndexBtn]);

	return;
}

bool CFortune::pageViewTouchBegan(Touch *touch, Event *event)
{
	CCLOG("CFortune::pageViewTouchBegan");
	return true;
}

void CFortune::pageViewTouchMoved(Touch *touch, Event *event)
{
	CCLOG("CFortune::pageViewTouchMoves");
	return;
}

void CFortune::pageViewTouchEnded(Touch *touch, Event *event)
{
	CCLOG("CFortune::pageViewTouchEnded");
	return;
}


void CFortune::setDayListBtnEnable(const int nIndexBtn)
{
	if (m_dataSummaryMap.end() == m_dataSummaryMap.find(m_nFortuneDay))
	{
		/* ��ǰû�л�ȡ������ */
		getFortuneContentHttp();
	}
	else
	{
		formatPageviewTextContent();
	}
	for (int i = 0; i < STAR_FORTUNE_FORTUNEDAY_SIZE; i++)
	{
		Button* pFortuneDayBtnList = m_pFortuneDayBtnList[i];
		if (pFortuneDayBtnList)
		{
			if (i == nIndexBtn)
			{
				pFortuneDayBtnList->setTitleColor(Color3B::BLUE);
			}
			else
			{
				pFortuneDayBtnList->setTitleColor(Color3B::BLACK);
			}
		}
	}
}

void CFortune::formatPageviewTextContent()
{
	int nFontNum = m_pFortuneContentLabel[m_nFortuneDay]->getStringLength(); //��ʾ����������
	CCLOG(">>>>>>>>>>>>>>>>> nFontNum:%d <<<<<<<<<<<<<<<<<<<<<<<<<<", nFontNum);

	int nFontSize = m_pFortuneContentLabel[m_nFortuneDay]->getFontSize(); //��ʾһ����ռ�ö��ٸ�����

	Size nSize = m_pFortuneContentLabel[m_nFortuneDay]->getTextAreaSize(); //��ʾ�ɻ��Ƶ��������ص�
	CCLOG(">>>>>>>>>>>>>>>>> nSize:%f,%f <<<<<<<<<<<<<<<<<<<<<<<<<<", nSize.width, nSize.height);

	int nLineFontNum = nSize.width / nFontSize; //��ǰ��������Ŀ
	int nRowFontNum = nSize.height / nFontSize; //��ǰ��������

	if (nLineFontNum * nRowFontNum < nFontNum)
	{
		/* ���ֳ�����Ļ��ʾ�� */
		m_pFortuneContentButton[m_nFortuneDay]->setVisible(true);
	}
	else
	{
		m_pFortuneContentButton[m_nFortuneDay]->setVisible(false);
	}

}

void CFortune::readContentFullScene(Ref *pRef)
{
	std::string strContent = m_pFortuneContentLabel[m_nFortuneDay]->getStringValue();
	CCLOG(">>>>>>>>>>>>>>>>> strContent:%s <<<<<<<<<<<<<<<<<<<<<<<<<<", strContent.c_str());

	CPopupLayer* pPopAboutAuthorLayer = CPopupLayer::create("FortuneSet/PopLayer.png");
	pPopAboutAuthorLayer->setContentText(strContent.c_str(), FORTUNE_POPLAYER_FONTSIZE, FORTUNE_POPLAYER_PADDING, FORTUNE_POPLAYER_PADDINGTOP);
	this->addChild(pPopAboutAuthorLayer);
}

void CFortune::getFortuneContentHttp()
{
	HttpRequest* request = new HttpRequest();

	char szUrl[256] = { 0 };
	sprintf(szUrl, URLFORMAT, gszFortuneConsName[m_nFortuneType], gszFortuneDayDescript[m_nFortuneDay], APPKEY);
	request->setUrl(szUrl);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(CFortune::onHttpRequestCompleted));
	HttpClient::getInstance()->send(request);
	request->release();

	return;
}

void CFortune::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
	HttpResponse *response = (HttpResponse*)data;
	if (!response)
	{
		return;
	}
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		CCLOG("%s completed", response->getHttpRequest()->getTag());
	}
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "Http status code:%d ,tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLOG("response code:%d", statusCode);
	if (!response->isSucceed())
	{
		CCLOG("response failed");
		CCLOG("error buffer:%s", response->getErrorBuffer());
	}
	std::vector<char> *buffer = response->getResponseData();
	printf("Http response,dump data:");
	std::string result = "";
	int nBufferSize = buffer->size();
	for (unsigned int i = 0; i < nBufferSize; i++)
	{
		result += (*buffer)[i];
	}

	rapidjson::Document root;
	root.Parse<0>(result.c_str());
	if (root.HasParseError())
	{
		CCLOG("GetParseError%s\n", root.GetParseError());
		return;
	}

	if (!root.IsObject())
		return;

	rapidjson::Value& resultCode = root["error_code"];
	int nResultCode = resultCode.GetInt();
	if (0 != nResultCode)
	{
		m_pFortuneContentLabel[m_nFortuneDay]->setString("Error");
		return;
	}

	rapidjson::Value& strResultCodeValue = root["resultcode"];
	std::string strResultCode = strResultCodeValue.GetString();


	std::string strContent = "";
	rapidjson::Value _array;
	if ((m_nFortuneDay == 0 || m_nFortuneDay == 1) && root.HasMember("summary")) //���죬����
	{
		_array = root["summary"];
		strContent += _array.GetString();
	}
	else if ((m_nFortuneDay == 2)) //��
	{
		if (root.HasMember("health"))
		{
			_array = root["health"];
			strContent += _array.GetString();
		}

		if (root.HasMember("job"))
		{
			_array = root["job"];
			strContent += _array.GetString();
		}

		if (root.HasMember("love"))
		{
			_array = root["love"];
			strContent += _array.GetString();
		}

		if (root.HasMember("money"))
		{
			_array = root["money"];
			strContent += _array.GetString();
		}

		if (root.HasMember("work"))
		{
			_array = root["work"];
			strContent += _array.GetString();
		}
	}
	else if ((m_nFortuneDay == 3)) //��
	{
		if (root.HasMember("all"))
		{
			_array = root["all"];
			strContent += _array.GetString();
		}

		if (root.HasMember("love"))
		{
			_array = root["love"];
			strContent += _array.GetString();
		}
	}
	else if ((m_nFortuneDay == 4)) //��
	{
		if (root.HasMember("mima"))
		{
			_array = root["mima"];
			if (_array.IsArray())
			{
				CCLOG("year array");
			}
			else
			{
				int nType = _array.GetType();
				if (_array.IsNull())
				{
					CCLOG("year mima info == NULL");
				}
				else if(_array.IsObject())
				{
					for (rapidjson::Value::MemberIterator itr = _array.MemberBegin(); itr != _array.MemberEnd(); ++itr)
					{
						std::string jkey = itr->name.GetString();
						if (jkey == "info")
						{
							rapidjson::Value &entry = itr->value;
							strContent += entry.GetString();

						}

						if (jkey == "text")
						{
							rapidjson::Value &entry = itr->value;
							int nEnteryType = entry.GetType();
							CCLOG("nEnteryType:%d", nEnteryType);
							if (entry.IsArray())
							{
								for (rapidjson::SizeType i = 0; i < entry.Size(); ++i)
								{
									if (entry[i].IsString()) {
										strContent += entry[i].GetString();
									}
								}
							}
							//strContent += entry.GetString();
						}
					}
				}
			}
		
		}
	}
	else
	{
		strContent = "Error Error";
		return;
	}


	if (NULL == m_pFortuneContentLabel[m_nFortuneDay])
	{
		CCLOG("NULL == m_pFortuneContentLabel");
		return;
	}

	m_pFortuneContentLabel[m_nFortuneDay]->setTextAreaSize(Size(640, 480));
	m_pFortuneContentLabel[m_nFortuneDay]->setString(strContent);
	m_dataSummaryMap.insert(std::pair<int, std::string>(m_nFortuneDay, strContent));
	formatPageviewTextContent();
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// CFortuneΪcocos2d::CCLayer������, shareButtonClickΪĳ����ť����¼��Ĵ�����
void CFortune::shareButtonClick()
{
	// ��ȡһ��CCUMSocialSDKʵ��
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("562242dae0f55ac169001602");
	if (NULL == sdk)
	{
		CCLOG("SDK == NULL");
	}
	// ��������appkey,���create�������˲��õ��øú���
	// sdk->setAppKey("4eaee02c527015373b000003");
	// **********************   ����ƽ̨��Ϣ  ***************************
	// sdk->setQQAppIdAndAppKey("����QQ��app id", "appkey");
	// sdk->setWeiXinAppInfo("����΢�ź�����Ȧ��app id","app key");
	// sdk->setYiXinAppKey("�������ź���������Ȧ��app id");
	// sdk->setLaiwangAppInfo("����������������̬��app id", 
	//              "����������������̬��app key", "�ҵ�Ӧ����");
	// sdk->setFacebookAppId("���facebook appid");
	//     // �򿪻��߹ر�log
	// sdk->setLogEnable(true) ;
	// **********************   END ***************************
	
	// �����û����һ��ͼ�ķ���ʱ�û���ת����Ŀ��ҳ��, һ��Ϊapp��ҳ��������ҳ��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	char szText[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
	sprintf(szText, "%s:%s", ReadString::getInstance()->parse(STAR_JSON_KEY_SHARE_STAR).c_str(), STAR_SHARE_URL);
	std::string strContent = ReadString::getInstance()->parse(STAR_JSON_KEY_ABOUT_STAR).c_str();
	sdk->setPlatformShareContent(SINA, szText, STAR_SHAREPIC_LOCALURL, szText, STAR_SHARE_URL);
	sdk->setPlatformShareContent(RENREN, szText, STAR_SHAREPIC_LOCALURL, szText, STAR_SHARE_URL);
	sdk->setPlatformShareContent(DOUBAN, szText, STAR_SHAREPIC_LOCALURL, szText, STAR_SHARE_URL);
	//sdk->setPlatformShareContent(SINA, szText, "assets/StartPage.png", ReadString::getInstance()->parse(STAR_JSON_KEY_ABOUT_STAR).c_str(), STAR_SHARE_URL);
	//sdk->setPlatformShareContent(RENREN, szText, "assets/StartPage.png", ReadString::getInstance()->parse(STAR_JSON_KEY_ABOUT_STAR).c_str(), STAR_SHARE_URL);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif

	//sdk->setTargetUrl("http://www.umeng.com/social");
	// �������˷����������ʾ��ƽ̨
	vector<int>* platforms = new vector<int>();
	platforms->push_back(SINA);
	platforms->push_back(RENREN);
	platforms->push_back(DOUBAN);
	//platforms->push_back(QZONE);
	//platforms->push_back(QQ);
	// ����ƽ̨, �ڵ��÷�����Ȩ��صĺ���ǰ��������SDK֧�ֵ�ƽ̨
	sdk->setPlatforms(platforms);

	// �򿪷������, ע�����ص�, ����1Ϊ��������ϵ�ƽ̨, ����2ΪҪ������������ݣ�
	// ����3ΪҪ�����ͼƬ·��(android��IOS��ͼƬ��ַ��ʽ��һ�£���˷�ƽ̨����), ����4Ϊ����ص�.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sdk->openShare(szText, STAR_SHAREPIC_LOCALURL, share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sdk->openShare(szText, STAR_SHAREPIC_LOCALURL, share_selector(shareCallback));
#endif
}
#endif


