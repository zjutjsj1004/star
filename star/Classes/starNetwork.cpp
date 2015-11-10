#include <stdio.h>
#include "common.h"
#include "starNetwork.h"

#ifdef _STAR_ZEROMQ_
#include "zmq.h"
#endif

#include "starNetwork.h"
#include "starPB.h"
#include "cocos2d.h"
USING_NS_CC;

#include "event2/event.h"


CStarNetwork* CStarNetwork::sm_pInstance = NULL;
void* CStarNetwork::m_pCtx = NULL;
void* CStarNetwork::m_pSocket = NULL;

CStarNetwork::CStarNetwork()
{
	resetMember();
    struct event_base *base = event_base_new();
    event_reinit(base);
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
#ifdef _STAR_ZEROMQ_
	//ʹ��tcpЭ�����ͨ�ţ���Ҫ���ӵ�Ŀ�����IP��ַΪ192.168.1.2
	//ͨ��ʹ�õ�����˿� Ϊ7766 
    //const char * pAddr = "tcp://127.0.0.1:11214";
    const char * pAddr = "192.168.9.165:11214";

	//����context 
	if ((m_pCtx = zmq_ctx_new()) == NULL)
	{
		return false;
	}
	//����socket 
	if ((m_pSocket = zmq_socket(m_pCtx, ZMQ_DEALER)) == NULL)
	{
		zmq_ctx_destroy(m_pCtx);
		return false;
	}
	int iSndTimeout = 5000;// millsecond
						   //���ý��ճ�ʱ 
	if (zmq_setsockopt(m_pSocket, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
	{
		zmq_close(m_pSocket);
		zmq_ctx_destroy(m_pCtx);
		return false;
	}
	//����Ŀ��IP192.168.1.2���˿�7766 
	if (zmq_connect(m_pSocket, pAddr) < 0)
	{
		zmq_close(m_pSocket);
		zmq_ctx_destroy(m_pCtx);
		return false;
	}
#endif

	
	return true;
}

bool CStarNetwork::uninitNetwork()
{
#ifdef _STAR_ZEROMQ_
	if (NULL != m_pCtx)
	{
		zmq_ctx_destroy(m_pCtx);
	}

	if (NULL != m_pSocket)
	{
		zmq_close(m_pSocket);
	}
#endif

	
	return true;
}

int CStarNetwork::sendData(int nMessType, const void *buf, size_t len)
{

	LogonReqMessage logonReq;
	logonReq.set_acctid(20);
	logonReq.set_passwd("Hello World");
	//��ǰ��ȡ�������л���ռ�õĿռ䲢����һ���Է��䣬�Ӷ������η���
	//����ɵ����ܿ�����ͨ�����ַ�ʽ�������Խ����л�������ݽ��м��ܡ�
	//֮���ٽ��г־û������Ƿ��͵�Զ�ˡ�
	int length = logonReq.ByteSize();
	char* bufTmp = new char[length];
	logonReq.SerializeToArray(bufTmp, length);
	int nSizeof = sizeof(bufTmp);
#ifdef _STAR_ZEROMQ_
    if (zmq_send(m_pSocket, bufTmp, length, 0) < 0)
    {
        return ERROR_COMMMON_FAILED;
    }
#endif

	
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
