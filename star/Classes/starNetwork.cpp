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

	//ʹ��tcpЭ�����ͨ�ţ���Ҫ���ӵ�Ŀ�����IP��ַΪ192.168.1.2
	//ͨ��ʹ�õ�����˿� Ϊ7766 
    //const char * pAddr = "tcp://127.0.0.1:11214";
    const char * pAddr = "192.168.9.165:11214";

	//����context 
	//if ((m_pCtx = zmq_ctx_new()) == NULL)
	{
	//	return false;
	}
	//����socket 
	//if ((m_pSocket = zmq_socket(m_pCtx, ZMQ_DEALER)) == NULL)
	{
	//	zmq_ctx_destroy(m_pCtx);
	//	return false;
	}
	int iSndTimeout = 5000;// millsecond
						   //���ý��ճ�ʱ 
	//if (zmq_setsockopt(m_pSocket, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
	{
	//	zmq_close(m_pSocket);
	//	zmq_ctx_destroy(m_pCtx);
	//	return false;
	}
	//����Ŀ��IP192.168.1.2���˿�7766 
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
	//��ǰ��ȡ�������л���ռ�õĿռ䲢����һ���Է��䣬�Ӷ������η���
	//����ɵ����ܿ�����ͨ�����ַ�ʽ�������Խ����л�������ݽ��м��ܡ�
	//֮���ٽ��г־û������Ƿ��͵�Զ�ˡ�
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
