#ifndef __ConfigMgr_H__
#define __ConfigMgr_H__

#include"DataBase.h"

class CConfigMgr
{
public:

	static CConfigMgr* getInstance();
	//�����ȡ�����ӿ�
	CDataBaseMgr* getData(string strName);
	void setData(string strName,CDataBaseMgr* pDataBaseMgr);
private:
	CConfigMgr();
	~CConfigMgr();
	static CConfigMgr* m_pInstance;
	map<string, CDataBaseMgr*> m_MapDatas;
};



#endif
