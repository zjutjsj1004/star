
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
    struct echo_context *ec = (struct echo_context *)args;

    int ret = send(sock, ec->echo_contents, ec->echo_contents_len, 0);
    printf("connected, write to echo server: %d\n", ret);
    event_add(ec->event_read, 0);
}

void read_cb(evutil_socket_t sock, short flags, void * args)
{
    struct echo_context *ec = (struct echo_context *)args;
    char buf[128];
    int ret = recv(sock, buf, 128, 0);

    printf("read_cb, read %d bytes\n", ret);
    if (ret > 0)
    {
        ec->recved += ret;
        buf[ret] = 0;
        printf("recv:%s\n", buf);
    }
    else if (ret == 0)
    {
        printf("read_cb connection closed\n");
        event_base_loopexit(ec->base, NULL);
        return;
    }
    if (ec->recved < ec->echo_contents_len)
    {
        event_add(ec->event_read, 0);
    }
}

static evutil_socket_t make_tcp_socket()
{
#ifdef WIN32
    int nIPPROTO = IPPROTO_TCP; /* #define IPPROTO_TCP 6  */
#else
    /* #define IPPROTO_TCP 6 ,非Win32平台下需要添加头文件：#include <netinet/tcp.h>
    #include <sys/select.h>
    #include <sys/socket.h>
    #include <arpa/inet.h> */
    int nIPPROTO = IPPROTO_TCP; 
#endif
    int on = 1;
    evutil_socket_t sock = socket(AF_INET, SOCK_STREAM, nIPPROTO);

    //evutil_make_socket_nonblocking(sock); /* 不注释就在connect时出现错误10035: 无法立即完成一个非阻止性套接字操作*/
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
    if (m_pSocket <=0)
    {
        m_pSocket = make_tcp_socket();
        struct sockaddr_in serverAddr;
        struct event * ev_write = 0;
        struct event * ev_read = 0;
        struct timeval tv = { 10, 0 };
        struct echo_context *ec = (struct echo_context*)calloc(1, sizeof(struct echo_context));

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
#ifdef WIN32
            int nErr = WSAGetLastError();
#else 
            int nErr = ERROR_COMMMON_FAILED;
#endif
            printf("connect err = %d", nErr);
            return;
        }
    }
    
    

    send(m_pSocket, "helloworld!", 11, 0);
#if 0
    ev_write = event_new(base, sock, EV_WRITE, write_cb, (void*)ec);
    ev_read = event_new(base, sock, EV_READ, read_cb, (void*)ec);

    ec->event_write = ev_write;
    ec->event_read = ev_read;
    ec->base = base;
    ec->echo_contents = strdup("echo client tneilc ohce\n");
    ec->echo_contents_len = strlen(ec->echo_contents);
    ec->recved = 0;

    event_add(ev_write, &tv); 
#endif

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
    //event_base_dispatch(base);
    //event_base_free(base);

    return 0;
}

