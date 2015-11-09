#include <stdio.h>
#include "common.h"
#include "starNetwork.h"

//#include "zmq.h"
#include "starNetwork.h"
#include "starPB.h"
#include "cocos2d.h"
USING_NS_CC;

CStarNetwork* CStarNetwork::sm_pInstance = NULL;
void* CStarNetwork::m_pCtx = NULL;
void* CStarNetwork::m_pSocket = NULL;

CStarNetwork::CStarNetwork()
{
	resetMember();
}

CStarNetwork::~CStarNetwork()
{
	resetMember();
}

void CStarNetwork::resetMember()
{
	m_pCtx = NULL;
	m_pSocket = NULL;
}

bool CStarNetwork::initNetwork()
{

	//使用tcp协议进行通信，需要连接的目标机器IP地址为192.168.1.2
	//通信使用的网络端口 为7766 
    //const char * pAddr = "tcp://127.0.0.1:11214";
    const char * pAddr = "192.168.9.165:11214";

	//创建context 
	//if ((m_pCtx = zmq_ctx_new()) == NULL)
	{
	//	return false;
	}
	//创建socket 
	//if ((m_pSocket = zmq_socket(m_pCtx, ZMQ_DEALER)) == NULL)
	{
	//	zmq_ctx_destroy(m_pCtx);
	//	return false;
	}
	int iSndTimeout = 5000;// millsecond
						   //设置接收超时 
	//if (zmq_setsockopt(m_pSocket, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
	{
	//	zmq_close(m_pSocket);
	//	zmq_ctx_destroy(m_pCtx);
	//	return false;
	}
	//连接目标IP192.168.1.2，端口7766 
	//if (zmq_connect(m_pSocket, pAddr) < 0)
	{
	//	zmq_close(m_pSocket);
	//	zmq_ctx_destroy(m_pCtx);
	//	return false;
	}
	
	return true;
}

bool CStarNetwork::uninitNetwork()
{
	if (NULL != m_pCtx)
	{
	//	zmq_ctx_destroy(m_pCtx);
	}

	if (NULL != m_pSocket)
	{
	//	zmq_close(m_pSocket);
	}
	
	return true;
}

int CStarNetwork::sendData(int nMessType, const void *buf, size_t len)
{

	LogonReqMessage logonReq;
	logonReq.set_acctid(20);
	logonReq.set_passwd("Hello World");
	//提前获取对象序列化所占用的空间并进行一次性分配，从而避免多次分配
	//而造成的性能开销。通过该种方式，还可以将序列化后的数据进行加密。
	//之后再进行持久化，或是发送到远端。
	int length = logonReq.ByteSize();
	char* bufTmp = new char[length];
	logonReq.SerializeToArray(bufTmp, length);
	int nSizeof = sizeof(bufTmp);
	//if (zmq_send(m_pSocket, bufTmp, length, 0) < 0)
	{
//		return ERROR_COMMMON_FAILED;
	}
	
	int nLen = strlen(bufTmp);
	printf("%d\n", nLen);

	LogonReqMessage logonReqTmp;
	logonReqTmp.ParseFromArray(bufTmp, nLen);
	std::string strTmp = logonReqTmp.passwd();
    CCLOG("%s", strTmp.c_str());
	printf("received message : %s\n", logonReqTmp.passwd().c_str());
	delete[]bufTmp;
	return ERROR_COMMON_SUCCESS;
}
