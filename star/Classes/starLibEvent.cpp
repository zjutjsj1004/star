#include <stdio.h>

#include "event2/event.h"
#include "event2/util.h"
#include "common.h"
#ifdef WIN32
#else
#include <netinet/tcp.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include "starLibEvent.h"
#include "starPB.h"
#include "cocos2d.h"
USING_NS_CC;



struct echo_context {
    struct event_base *base;
    struct event *event_write;
    struct event *event_read;
    const char * echo_contents;
    int echo_contents_len;
    int recved;
};

void write_cb(evutil_socket_t sock, short flags, void * args)
{
    CCLOG("start write_cb");

    struct echo_context *ec = (struct echo_context *)args;

    //int ret = send(sock, ec->echo_contents, ec->echo_contents_len, 0);
    //CCLOG("connected, write to echo server: %d\n", ret);
    event_add(ec->event_write, 0);
}

void read_cb(evutil_socket_t sock, short flags, void * args)
{
    CCLOG("start read_cb");

    struct echo_context *ec = (struct echo_context *)args;
    char buf[128];
    int ret = recv(sock, buf, 128, 0);

    CCLOG("read_cb, read %d bytes\n", ret);
    if (ret > 0)
    {
        ec->recved += ret;
        buf[ret] = 0;
        CCLOG("recv:%s\n", buf);
    }
    else if (ret == 0)
    {
        CCLOG("read_cb connection closed\n");
        event_base_loopexit(ec->base, NULL);
        return;
    }
    if (ec->recved < ec->echo_contents_len)
    {
        event_add(ec->event_read, 0);
    }

    event_base_loopexit(ec->base, NULL);
}

static evutil_socket_t make_tcp_socket()
{
#ifdef WIN32
    int nIPPROTO = IPPROTO_TCP; /* #define IPPROTO_TCP 6  */
#else
    /* #define IPPROTO_TCP 6 ,��Win32ƽ̨����Ҫ���ͷ�ļ���#include <netinet/tcp.h>
    #include <sys/select.h>
    #include <sys/socket.h>
    #include <arpa/inet.h> */
    int nIPPROTO = IPPROTO_TCP; 
#endif
    int on = 1;
    evutil_socket_t sock = socket(AF_INET, SOCK_STREAM, nIPPROTO);

    evutil_make_socket_nonblocking(sock); /* ��ע�;���connectʱ���ִ���10035: �޷��������һ������ֹ���׽��ֲ���*/
#ifdef WIN32
    setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (const char *)&on, sizeof(on));
#else
    setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (void *)&on, sizeof(on));
#endif

    return sock;
}

CStarLibeventNetwork* CStarLibeventNetwork::sm_pInstance = NULL;
evutil_socket_t CStarLibeventNetwork::m_pSocket = 0;


void CStarLibeventNetwork::echo_client(struct event_base *base)
{
    CCLOG("start CStarLibeventNetwork::echo_client(m_pSocket:%d)", m_pSocket);
    if (m_pSocket <=0)
    {
        m_pSocket = make_tcp_socket();
        struct sockaddr_in serverAddr;

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(STAR_NETWORK_ECHO_PORT);
#ifdef WIN32
        serverAddr.sin_addr.S_un.S_addr = inet_addr(STAR_NETWORK_ECHO_SERVER);
#else
        serverAddr.sin_addr.s_addr = inet_addr(STAR_NETWORK_ECHO_SERVER);
#endif
        memset(serverAddr.sin_zero, 0x00, 8);

        if (0 != connect(m_pSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)))
        {
#if 0
#ifdef WIN32
            int nErr = WSAGetLastError();
#else 
            int nErr = ERROR_COMMMON_FAILED;
#endif
#endif
            int nErr = EVUTIL_SOCKET_ERROR(); /* �ر��߳����һ���׽��ֲ�����ȫ�ִ���ţ� */
            CCLOG("connect err = %d", nErr);
            return;
        }
    }
    
    

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
    if (send(m_pSocket, bufTmp, length, 0) < 0)
    {
        CCLOG("send error in echo_client");
        return;
    }

#if 0
    /* �����л� */
    int nLen = strlen(bufTmp);
    printf("%d\n", nLen);

    LogonReqMessage logonReqTmp;
    logonReqTmp.ParseFromArray(bufTmp, nLen);
    std::string strTmp = logonReqTmp.passwd();
    CCLOG("%s", strTmp.c_str());
    printf("received message : %s\n", logonReqTmp.passwd().c_str());
#endif

       delete[]bufTmp;

    struct event * ev_write = NULL;
    struct event * ev_read = NULL;
    struct timeval tv = { 10, 0 };
    struct echo_context *ec = (struct echo_context*)calloc(1, sizeof(struct echo_context));

    ev_write = event_new(base, m_pSocket, EV_WRITE, write_cb, (void*)ec);
    ev_read = event_new(base, m_pSocket, EV_READ, read_cb, (void*)ec);

    ec->event_write = ev_write;
    ec->event_read = ev_read;
    ec->base = base;
    ec->echo_contents = strdup("echo client tneilc ohce\n");
    ec->echo_contents_len = strlen(ec->echo_contents);
    ec->recved = 0;
    if (NULL == ev_write)
    {
        CCLOG("CStarLibeventNetwork::echo_client(ev_write == NULL)");
    }
    else
    {
#ifdef WIN32
        //android ��ִ����һ�����
        event_add(ev_write, &tv);
#endif
    }

    if (NULL == ev_read)
    {
        CCLOG("CStarLibeventNetwork::echo_client(ev_read == NULL)");
    }
    else
    {
#ifdef WIN32
        //android ��ִ����һ�����
        event_add(ev_read, &tv);
#endif
    }

    CCLOG("End CStarLibeventNetwork::echo_client(m_pSocket:%d)", m_pSocket);

    return;
}

int CStarLibeventNetwork::sendData()
{
    struct event_base * base = 0;
#ifdef WIN32
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 2);

    (void)WSAStartup(wVersionRequested, &wsaData);
#endif

    base = event_base_new();
    echo_client(base);
    event_base_dispatch(base);
    //event_base_free(base);

    return 0;
}

