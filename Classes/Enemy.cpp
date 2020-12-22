#include"Enemy.h"
#include"GameScene.h"
#include"DynamicDt.h"
CEnemy::CEnemy()
	:m_nState(E_STATE_LEFT)
	,fDis(0)
	,i(0)
	,dis(0)
	,m_nSpeed(0)
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::initWithData(SEnemyDt * pData)
{
	if (!Node::init()) {
		return false;
	}
	m_pEnemyDt = pData;
	m_nHp = pData->nHp;
	m_nSpeed = pData->nSpeed;
	m_pImage = Sprite::createWithSpriteFrameName(pData->strImg);
	this->setPosition(CGameScene::getInstance()->getTiledMapCtrl()->m_MapPathPos[0]);
	this->addChild(m_pImage);
	this->createAmins(pData);
	this->scheduleUpdate();
	return true;
}

CEnemy * CEnemy::createWithData(SEnemyDt * pData)
{
	CEnemy* pEnemy = new CEnemy();
	if (pEnemy&&pEnemy->initWithData(pData)) {
		pEnemy->autorelease();
		return pEnemy;
	}
	CC_SAFE_DELETE(pEnemy);
	return nullptr;
}



void CEnemy::update(float delta)
{
	m_MapPath = CGameScene::getInstance()->getTiledMapCtrl()->m_MapPathPos;
	if(i < m_MapPath.size()) {
		Vec2 tile = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_MapPath[i]);
		Vec2 tileNex = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_MapPath[i+1]);
		if (tileNex.x - tile.x == 0) {
			m_nDir = Vec2((tileNex.x - tile.x), (tile.y - tileNex.y) / abs(tileNex.y - tile.y));
		}
		if (tileNex.y - tile.y == 0) {
			m_nDir = Vec2((tileNex.x - tile.x) / abs(tileNex.x - tile.x), (tileNex.y - tile.y));
		}
		if (m_nDir == Vec2(1,0)) {
			this->changeAnim(E_STATE_RIGHT);
		}
		else if (m_nDir == Vec2(-1, 0)) {
			this->changeAnim(E_STATE_LEFT);
		}
		float dis = abs(m_MapPath[i + 1].x - m_MapPath[i].x) + abs(m_MapPath[i + 1].y - m_MapPath[i].y);
			Vec2 pos = this->getPosition();
			pos.x += m_nSpeed * m_nDir.x*delta;
			pos.y += m_nSpeed * m_nDir.y*delta;
			fDis += abs(m_nSpeed * m_nDir.x*delta) + abs(m_nSpeed * m_nDir.y*delta);
			this->setPosition(pos);
			if (fDis > dis) {
				fDis = 0;
				dis = 0;
				m_nDir = Vec2(0, 0);
				i++;
				return;
			}
		}
	}

void CEnemy::onCollision(CBullet * pBullet)
{
	if (pBullet->m_nBulletID>=5010&&pBullet->m_nBulletID<=5012) {
		int Num = random() % 10;
		if (Num < 6) {
			m_nSpeed = 0;
		}
		this->scheduleOnce(CC_CALLBACK_1(CEnemy::resumeAction, this), 2, "resumeAction");
	}
	m_nHp -= pBullet->getDamage();
	if (m_nHp <= 0) {
		int nCoin = CDynamicDt::getInstance()->getMapGold();
		nCoin += m_pEnemyDt->nCoin;
		CDynamicDt::getInstance()->setMapGold(nCoin);
		this->removeFromParent();

		//this->changeAnim(E_STATE_DEATH);
		CGameScene::getInstance()->m_pCoinLabel->setString(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()));
	}
	Vector<Node*> VecBullet = CGameScene::getInstance()->getBulletMgr()->getChildren();
	for (Node*& pBNode : VecBullet) {
		CBullet* pBullet1 = static_cast<CBullet*>(pBNode);
		if (pBullet1->getTarget() == this) {
			pBullet1->removeFromParent();
		}
	}
}

void CEnemy::resumeAction(float delta)
{
	m_nSpeed = m_pEnemyDt->nSpeed;
}

void CEnemy::changeAnim(int nState)
{
	if (m_nState == nState)
	{
		return;
	}
	m_nState = nState;
	m_pImage->stopAllActions();
	if (E_STATE_RIGHT == nState) {
		Animate* pAnimateR = Animate::create(m_pAnimationR);
		RepeatForever* pRepeat = RepeatForever::create(pAnimateR);
		m_pImage->runAction(pRepeat);
	}
	else if (E_STATE_LEFT == nState) {
		Animate* pAnimateL = Animate::create(m_pAnimationL);
		RepeatForever* pRepeat = RepeatForever::create(pAnimateL);
		m_pImage->runAction(pRepeat);
	}
	else if (E_STATE_DEATH == nState){
		Animate* pAnimateDeath = Animate::create(m_pAnimationBoom);
		CallFunc* pCallFunc = CallFunc::create([&]()->void {
			this->removeFromParent();
		});
		m_pImage->runAction(Sequence::createWithTwoActions(pAnimateDeath, pCallFunc));
	}
}

void CEnemy::createAmins(SEnemyDt* pData)
{
	m_pAnimationL = Animation::create();
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	for (int i = 0; i < 2;i++) {
		SpriteFrame* pSpriteFrame = pCache->getSpriteFrameByName(StringUtils::format("ui_L_Monsters_%02d_%02d.png",pData->nID-2000,i+1));
		m_pAnimationL->addSpriteFrame(pSpriteFrame);
	}
	m_pAnimationL->setDelayPerUnit(0.2);
	Animate* pAnimateL = Animate::create(m_pAnimationL);
	RepeatForever* pRepeat = RepeatForever::create(pAnimateL);
	m_pImage->runAction(pRepeat);
	m_pAnimationL->retain();

	m_pAnimationR = Animation::create();
	for (int i = 0; i < 2; i++) {
		SpriteFrame* pSpriteFrame = pCache->getSpriteFrameByName(StringUtils::format("ui_R_Monsters_%02d_%02d.png", pData->nID - 2000, i + 1));
		m_pAnimationR->addSpriteFrame(pSpriteFrame);
	}
	m_pAnimationR->setDelayPerUnit(0.2);
	m_pAnimationR->retain();

	m_pAnimationBoom = Animation::create();
	for (int i = 0; i < 5; i++) {
		SpriteFrame* pSpriteFrame = pCache->getSpriteFrameByName(StringUtils::format("Death%d.png",i + 1));
		m_pAnimationBoom->addSpriteFrame(pSpriteFrame);
	}
	m_pAnimationBoom->setDelayPerUnit(0.05);
	m_pAnimationBoom->retain();
}
