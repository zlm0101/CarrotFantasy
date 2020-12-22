#include"Tower.h"
#include"GameScene.h"
CTower::CTower()
	:m_nCurGrade(0)
	, nCurState(E_STATE_NORMAL)
	,m_nSaleCoin(0)
	,m_nDir(0,-1)
	,m_nEnemyIndex(0)
	,m_nCurTowerID(0)
	,i(0)
{
}

CTower::~CTower()
{
}

bool CTower::initWithData(int nTowerID)
{
	if (!Node::init()) {
		return false;
	}
	m_nCurTowerID = nTowerID;
	m_pTowerDt = static_cast<STowerDt*>(CConfigMgr::getInstance()->getData("TowerDtMgr")->getDataByID(nTowerID));
	m_pImage = Sprite::createWithSpriteFrameName(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);
	m_nSaleCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth;
	m_nUpGradeCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin;
	this->addChild(m_pImage);
	this->schedule(CC_CALLBACK_1(CTower::search,this),"search");
	this->schedule(CC_CALLBACK_1(CTower::fire, this), m_pTowerDt->m_VecLevel[m_nCurGrade]->fAckInterval, "fire");
	return true;
}

void CTower::upgrade()
{
	m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[++m_nCurGrade]->VecImg[nCurState]);
	setSaleCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth);
	setUpGradeCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin);
	setCurGrade(m_nCurGrade);
}

CTower * CTower::createWithData(int nTowerID)
{
	CTower* pTower = new CTower();
	if (pTower&&pTower->initWithData(nTowerID)) {
		pTower->autorelease();
		return pTower;
	}
	CC_SAFE_DELETE(pTower);

	return nullptr;
}

//getTarget() {}


void CTower::search(float delta)
{
	//Vector<Node*> VecEnemy = CGameScene::getInstance()->getEnemyMgr()->getChildren();
	//for (Node*& pENode : VecEnemy) {
	//	CEnemy* pEnemy = static_cast<CEnemy*>(pENode);
	CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());
	if (pTarget) {
		Vec2 EnemyPos = pTarget->getPosition();
		Vec2 TowerPos = this->getPosition();
		m_fDisSq = EnemyPos.getDistanceSq(TowerPos);
		float TowerScope = m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope;
		//只有几种塔台才会旋转
		//只有等前一只死了才会重新转向
		if (TowerScope*TowerScope >= m_fDisSq && (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4003 || m_nCurTowerID == 4004 || m_nCurTowerID == 4006)) {
			//进入炮台攻击范围
			//旋转炮台
			Vec2 disPos = EnemyPos - TowerPos;
			m_nDir = disPos.getNormalized();
			
			//float fAngle = Vec2::angle(m_nDir, Vec2(1, 0));
			//float fDegree = CC_RADIANS_TO_DEGREES(fAngle);
			//m_pImage->setRotation(fDegree - 90);
			m_pImage->setRotation(ccpAngle(m_nDir, Vec2(0, -1)) * 180 / 3.14);
		}
	}
}

void CTower::fire(float Dt)
{
	CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());
		if (pTarget) {
			if (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4004) {
			nCurState = E_STATE_FIRE;
			m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);
			SBulletDt* pBulletDt = static_cast<SBulletDt*>(CConfigMgr::getInstance()->getData("BulletDtMgr")->getDataByID(m_pTowerDt->m_VecLevel[m_nCurGrade]->nBulletID));
			CBullet* pBullet = CBullet::createWithData(pBulletDt);
			pBullet->setPosition(this->getPosition());
			_eventDispatcher->dispatchCustomEvent("addBullet", pBullet);
			pBullet->setTarget(pTarget);
			pBullet->setDamage(m_pTowerDt->m_VecLevel[m_nCurGrade]->nAck);
			pBullet->addCollsionCb(CC_CALLBACK_1(CEnemy::onCollision, pTarget));
			Vec2 dir = (pTarget->getPosition() - this->getPosition()).getNormalized();
			pBullet->setRotation(ccpAngle(dir, Vec2(0, -1)) * 180 / 3.14);
		}
	}
	//else if (m_nCurTowerID == 4005) {
	//	//获取冰花范围内的所有敌人
	//	vector<CEnemy*> VecEnemy = CGameScene::getInstance()->getEnemyMgr()->iceFlowerCollic(this->getPosition(), m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope);
	//	//冰花子弹，圆圈范围内
	//	if (!VecEnemy.empty()) {
	//		nCurState = E_STATE_FIRE;
	//		m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);
	//		SBulletDt* pBulletDt = static_cast<SBulletDt*>(CConfigMgr::getInstance()->getData("BulletDtMgr")->getDataByID(m_pTowerDt->m_VecLevel[m_nCurGrade]->nBulletID));
	//		CBullet* pBullet = CBullet::createWithData(pBulletDt);
	//		pBullet->setPosition(this->getPosition());
	//		_eventDispatcher->dispatchCustomEvent("addBullet", pBullet);
	//		pBullet->setDamage(m_pTowerDt->m_VecLevel[m_nCurGrade]->nAck);
	//	}
	//}
		else {
			nCurState = E_STATE_NORMAL;
			m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);
		}
}