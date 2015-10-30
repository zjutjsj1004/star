#include "common.h"
#include "StarRapidJson.h"

ReadString* ReadString::m_pReadString = NULL; //初始化

ReadString* ReadString::create(std::string fileName)
{
	ReadString *RS = new ReadString();

	if (!RS || !RS->init(fileName))
	{
		delete RS;
		RS = nullptr;
		return nullptr;
	}
	return RS;
}

bool ReadString::init(std::string fileName)
{
	bool ret = false;
	do {
		const std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(fileName);
		ssize_t fileSize = 0;
		std::string contentStr;
		unsigned char* titlech = FileUtils::getInstance()->getFileData(jsonpath, "r", &fileSize);
		if (0 == fileSize)
		{
			CCLOG("ReadString::init failed");
		}
		contentStr = std::string((const char*)titlech, fileSize);
		m_doc.Parse<0>(contentStr.c_str());
		CC_BREAK_IF(m_doc.HasParseError());
		CCLOG("ReadString::init OK");
		ret = true;
	} while (0);
	return ret;
}

ReadString* ReadString::getInstance()
{
	std::string strJsonPath = "message/";
	strJsonPath += STAR_LANGUAGE_JSON_NAME;
	if (m_pReadString == NULL)
		m_pReadString = ReadString::create(strJsonPath);
	return m_pReadString;
}

string ReadString::parse(int key)
{
	if (!m_doc.IsNull() && !m_doc.IsArray())  //判断是不是数组
	{
		char szKey[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
		sprintf(szKey, "%d", key);
		rapidjson::Value& strResultCodeValue = m_doc[szKey];
		if (!strResultCodeValue.IsNull())
		{
			CCLOG("ReadString::parse(Value:%s)", strResultCodeValue.GetString());
			return strResultCodeValue.GetString();
		}
		
	}
	CCLOG("ReadString::parse(key:%d) return NULL", key);
	return ""; //没查找到任何对象则返回空字符串
}