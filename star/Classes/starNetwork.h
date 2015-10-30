#ifndef __STAR_NETWORK_H__
#define __STAR_NETWORK_H__

class CStarNetwork
{
public:
	static CStarNetwork *GetInstance()//通过静态公有函数获得该类的实例对象
	{
		if (sm_pInstance == NULL)
		{
			sm_pInstance = new CStarNetwork();
		}
		return sm_pInstance;
	}
	~CStarNetwork();
	void resetMember();
	bool initNetwork();
	bool uninitNetwork();

	static int sendData(int nMessType, const void *buf, size_t len);

private:
	CStarNetwork();

public:
	static CStarNetwork *sm_pInstance;

private:
	static void* m_pCtx;
	static void* m_pSocket;
};



#endif // __STAR_NETWORK_H__
