#ifndef __DataBase_H__
#define __DataBase_H__

#include<string>
#include<vector>
#include"cocos2d.h"
#include"json/document.h"
#include"json/rapidjson.h"
using namespace std;
using namespace rapidjson;
USING_NS_CC;
struct SDataBase
{
public:
	SDataBase() {
		nID = 0;
	}
	int nID;
};
class CDataBaseMgr
{
public:
	CDataBaseMgr();
	~CDataBaseMgr();
	virtual void loadFile(const string& strPath);
	SDataBase* getDataByID(int nID);
	virtual void parse(Document& doc) = 0;
	SDataBase* getDataByIndex(int nIndex);
	vector<SDataBase*> getAllData();
	int getSize();
protected:
	vector<SDataBase*> m_VecData;
};

#endif
