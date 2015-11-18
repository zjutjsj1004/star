#include <stdio.h>

#include "event2/event.h"
#include "event2/util.h"
#include "common.h"
#include "starPB.h"

#ifdef WIN32
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/tcp.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif



#define LISTEN_MAX 5
#define BUFFER_SIZE 1024
struct event_base *base = NULL;


struct sock_ev
{
    struct event *read_ev;
    struct event *write_ev;
    char *buf;
    sock_ev()
    {
        read_ev = NULL;
        write_ev = NULL;
        buf = new char[BUFFER_SIZE];
        memset(buf, 0, BUFFER_SIZE);
    }


    ~sock_ev()
    {
        delete[] buf;
    }
};


void release_sock_cv(sock_ev *ev)
{
    if (ev->read_ev)
    {
        if (0 != event_del(ev->read_ev))
        {
            printf("del err\n");
        }
        event_free(ev->read_ev);
        ev->read_ev = NULL;
    }
    if (ev->write_ev)
    {
        event_del(ev->write_ev);
        event_free(ev->write_ev);
        ev->write_ev = NULL;
    }
    free(ev);
}


void on_read(evutil_socket_t sock, short eventRead, void *arg)
{
    sock_ev *ev = (sock_ev*)arg;
    int nSize = recv(sock, (char*)ev->buf, BUFFER_SIZE, 0);
    if (nSize == SOCKET_ERROR)
    {
        printf("client socket closed\n");
        release_sock_cv(ev);
        closesocket(sock);
        return;
    }

    int nSizeBuf = strlen(ev->buf);
    printf("%d\n", nSizeBuf);
    LogonReqMessage logonReq;
    logonReq.ParseFromArray(ev->buf, nSizeBuf);


    printf("received message : %s\n", logonReq.passwd().c_str());


    char *p = "recv hello world!";
    send(sock, p, strlen(p), 0);
}


void on_write(evutil_socket_t sock, short eventWrite, void *arg)
{
    sock_ev *ev = (sock_ev*)arg;
    //printf("on_write\n");
}

/* EV_READ */
void on_accept(int sock, short eventAccept, void *arg)
{
    struct sockaddr_in cliAddr;
    int nSize = sizeof(sockaddr_in);
    SOCKET cliSock = accept(sock, (sockaddr*)&cliAddr, &nSize);
    sock_ev *ev = new sock_ev;
    struct event *eventRead = event_new(base, cliSock, EV_READ | EV_PERSIST, on_read, ev);
    struct event *eventWrite = event_new(base, cliSock, EV_WRITE | EV_PERSIST, on_write, ev);
    ev->read_ev = eventRead;
    ev->write_ev = eventWrite;
    event_add(eventRead, NULL);
    event_add(eventWrite, NULL);
}


int main()
{
#ifdef WIN32
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif

    SOCKET sockListen = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in srvAddr;
    srvAddr.sin_addr.s_addr = INADDR_ANY;
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(STAR_NETWORK_ECHO_PORT);


    if (bind(sockListen, (sockaddr*)&srvAddr, sizeof(sockaddr)) != 0)
    {
        printf("bind err = %d\n", WSAGetLastError());
        return 0;
    }
    if (0 != listen(sockListen, LISTEN_MAX))
    {
        printf("listen err = %d\n", WSAGetLastError());
        return 0;
    }


    base = event_base_new();
    struct event *eventListen = event_new(base, sockListen, EV_READ | EV_PERSIST, on_accept, NULL);
    event_add(eventListen, NULL);
    event_base_dispatch(base);



    closesocket(sockListen);
    event_base_free(base);

#ifdef WIN32
    WSACleanup();
#endif
    return 0;
}