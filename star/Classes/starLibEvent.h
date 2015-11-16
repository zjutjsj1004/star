#ifndef __STAR_LIBEVENT_NETWORK_H__
#define __STAR_LIBEVENT_NETWORK_H__

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

private:
    CStarLibeventNetwork() {};

public:
    static CStarLibeventNetwork *sm_pInstance;
};


#endif // __STAR_LIBEVENT_NETWORK_H__
