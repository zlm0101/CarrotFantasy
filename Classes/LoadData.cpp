#include "LoadData.h"
#include "ConfigMgr.h"
#include "DataClass.h"
CLoadData::CLoadData()
{
	this->initConfigs();
}


CLoadData::~CLoadData()
{
}

void CLoadData::initConfigs()
{

	//����ѡ��ؿ�����
	CselLevelDtMgr* pSelLevelDtMgr = new CselLevelDtMgr();
	pSelLevelDtMgr->loadFile("Config/SelLevel.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("SelLevelDtMgr", pSelLevelDtMgr);


	//���عؿ�����
	CLevelDtMgr* pLevelDtMgr = new CLevelDtMgr();
	pLevelDtMgr->loadFile("Config/LevelDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("LevelDtMgr", pLevelDtMgr);


	//���ص�������
	CEnemyDtMgr* pEnemyDtMgr = new CEnemyDtMgr();
	pEnemyDtMgr->loadFile("Config/EnemyDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("EnemyDtMgr", pEnemyDtMgr);


	//�����ϰ�������
	CObstaclesDtMgr* pObstaclesDtMgr = new CObstaclesDtMgr();
	pObstaclesDtMgr->loadFile("Config/obstaclesDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("ObstaclesDtMgr", pObstaclesDtMgr);

	//���ؿ�Ƭ����
	CCardDtMgr* pCardDtMgr = new CCardDtMgr();
	pCardDtMgr->loadFile("Config/CardDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("CardDtMgr", pCardDtMgr);


	//������̨����
	CTowerDtMgr* pTowerDtMgr = new CTowerDtMgr();
	pTowerDtMgr->loadFile("Config/TowerDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("TowerDtMgr", pTowerDtMgr);

	//�����ӵ�����
	CBulletDtMgr* pBulletDtMgr = new CBulletDtMgr();
	pBulletDtMgr->loadFile("Config/BulletDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("BulletDtMgr", pBulletDtMgr);


	//�����ӵ���ը����
	CEffectDtMgr* pEffectDtMgr = new CEffectDtMgr();
	pEffectDtMgr->loadFile("Config/EffectDt.json");
	//�洢�����ù���������
	CConfigMgr::getInstance()->setData("EffectDtMgr", pEffectDtMgr);

}
