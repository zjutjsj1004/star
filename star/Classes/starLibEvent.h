#ifndef __STAR_LIBEVENT_NETWORK_H__
#define __STAR_LIBEVENT_NETWORK_H__

#include "event2/event.h"
#include "event2/util.h"


class CStarLibeventNetwork
{
public:
    static CStarLibeventNetwork *GetInstance()//通过静态公有函数获得该类的实例对象
    {
        if (sm_pInstance == NULL)
        {
            sm_pInstance = new CStarLibeventNetwork();
        }
        return sm_pInstance;
    }
    ~CStarLibeventNetwork() {};

    static int sendData();
    static void echo_client(struct event_base *base);

private:
    CStarLibeventNetwork() {};

public:
    static CStarLibeventNetwork *sm_pInstance;
    static evutil_socket_t m_pSocket;

};

#endif // __STAR_LIBEVENT_NETWORK_H__
