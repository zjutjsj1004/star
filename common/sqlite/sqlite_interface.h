#ifndef SQLITE_INTERFACE
#define SQLITE_INTERFACE

class CSqliteInterface
{
public:
    static CSqliteInterface *GetInstance()//ͨ����̬���к�����ø����ʵ������
    {
        if (sm_pInstance == NULL)
        {
            sm_pInstance = new CSqliteInterface();
        }
        return sm_pInstance;
    }
    ~CSqliteInterface();

    static bool initSqliteDB();

public:
    static CSqliteInterface *sm_pInstance;

private:
    CSqliteInterface();

};



#endif  // SQLITE_INTERFACE
