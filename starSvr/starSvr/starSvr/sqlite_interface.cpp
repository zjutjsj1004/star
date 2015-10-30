#include<stdio.h>
#include "sqlite3.h"
#include "sqlite_interface.h"

CSqliteInterface* CSqliteInterface::sm_pInstance = NULL;

CSqliteInterface::CSqliteInterface()
{
}

CSqliteInterface::~CSqliteInterface()
{
}

bool CSqliteInterface::initSqliteDB()
{
    sqlite3 *db = NULL;
    char *zErrMsg = 0;
    int rc;

    //��ָ�������ݿ��ļ�,��������ڽ�����һ��ͬ�������ݿ��ļ�
    //A database connection handle is usually  returned in *ppDb, even if an error occurs
    rc = sqlite3_open("zieckey.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }
    else
    {
        printf("open zieckey.db successfully!\n");
    }
    sqlite3_close(db); //�ر����ݿ�

    return true;
}
