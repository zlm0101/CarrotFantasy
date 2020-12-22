#include"DataBase.h"

CDataBaseMgr::CDataBaseMgr()
{
}

CDataBaseMgr::~CDataBaseMgr()
{
}

void CDataBaseMgr::loadFile(const string & strPath)
{
	//获取全路径
	string strFullPath = FileUtils::getInstance()->fullPathForFilename(strPath);
	//获取文件信息
	string strData = FileUtils::getInstance()->getStringFromFile(strFullPath);

	Document doc;
	doc.Parse(strData.c_str());

	this->parse(doc);

	doc.Clear();
}

SDataBase * CDataBaseMgr::getDataByID(int nID)
{
	for (SDataBase* pData : m_VecData)
	{
		if (pData->nID == nID)
		{
			return pData;
		}
	}
	return nullptr;
}

SDataBase * CDataBaseMgr::getDataByIndex(int nIndex)
{
	if (nIndex<0 || nIndex>m_VecData.size() - 1) {
		return nullptr;
	}
	return m_VecData[nIndex];
}

vector<SDataBase*> CDataBaseMgr::getAllData()
{
	return m_VecData;
}

int CDataBaseMgr::getSize()
{
	return m_VecData.size();
}
