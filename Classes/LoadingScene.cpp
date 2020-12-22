#include"LoadingScene.h"
#include"ResDtMgr.h"
#include"GameMenu.h"
#include"SimpleAudioEngine.h"
#include"LevelSelScene.h"
#include"GameScene.h"
#include"DynamicDt.h"
#include"ConfigMgr.h"
using namespace CocosDenshion;
CLoadingScene::CLoadingScene()
	:m_nState(0)
	, m_nCurIndex(0)
	,m_nCount(0)
	,m_nResTotalCount(0)
	,isCommonFinish(false)
	,isMenuFinish(false)
{
}

CLoadingScene::~CLoadingScene()
{
}

bool CLoadingScene::initWithData(string strSceneName)
{
	if (!Scene::init()) {
		return false;
	}
	strNextSceneName = strSceneName;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_pComDt = CResDtMgr::getInstance()->getData("Common");
	m_pSceneDt = CResDtMgr::getInstance()->getData(strSceneName);

	m_nResTotalCount += (m_pComDt->m_VecPng.size() + m_pComDt->m_VecPlist.size() + m_pComDt->m_VecAudio.size());
	m_nResTotalCount += (m_pSceneDt->m_VecPng.size() + m_pSceneDt->m_VecPlist.size() + m_pSceneDt->m_VecAudio.size());
	Sprite* pBg = Sprite::create("Default-Landscape_ipad.png");
	pBg->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	this->addChild(pBg);

	Sprite* pProgressBg = Sprite::create("Common/ui_ProgressBar_01.png");
	pProgressBg->setPosition(origin.x + visibleSize.width / 2, origin.y +pProgressBg->getContentSize().height/2+50);
	this->addChild(pProgressBg);


	m_pProgress = ProgressTimer::create(Sprite::create("Common/ui_ProgressBar_02.png"));
	m_pProgress->setPosition(origin.x + visibleSize.width / 2, origin.y +pProgressBg->getContentSize().height/2+50);
	this->addChild(m_pProgress);
	m_pProgress->setType(ProgressTimer::Type::BAR);
	m_pProgress->setMidpoint(Vec2(0, 0.5));
	m_pProgress->setBarChangeRate(Vec2(1,0));
	this->scheduleUpdate();
	return true;
}

CLoadingScene * CLoadingScene::createWithData(string strSceneName)
{
	CLoadingScene* pLoadingScene = new CLoadingScene();
	if (pLoadingScene&&pLoadingScene->initWithData(strSceneName)) {
		pLoadingScene->autorelease();
		return pLoadingScene;
	}
	CC_SAFE_DELETE(pLoadingScene);
	return nullptr;
}

void CLoadingScene::update(float delta)
{
	if (m_nCount<m_nResTotalCount) {
		if (!isCommonFinish) {
			this->loadRes(m_pComDt);
		}
		else {
			this->loadRes(m_pSceneDt);
		}
		float fPercent = (float)m_nCount*100 / m_nResTotalCount;
		m_pProgress->setPercentage(fPercent);
	}
	else{
		this->unscheduleUpdate();
		if ("Menu" == strNextSceneName) {
			Director::getInstance()->replaceScene(CCTransitionZoomFlipAngular::create(1, CGameMenu::create()));
		}
		if ("Game" == strNextSceneName) {
			CGameScene::destory();
			Director::getInstance()->replaceScene(CCTransitionZoomFlipAngular::create(1, CGameScene::getInstance()));
		}
	}
}

void CLoadingScene::loadRes(SResDt * pDt)
{
	if (0 == m_nState) {
		if (m_nCurIndex>=pDt->m_VecPng.size()) {
			m_nCurIndex = 0;
			m_nState = 1;//加载plist的状态
			return;
		}
		string strPath = pDt->m_VecPng[m_nCurIndex];
		//纹理
		TextureCache* pCache = Director::getInstance()->getTextureCache();
		pCache->addImage(strPath);
		m_nCurIndex++;
		m_nCount++;

	}
	if (1 == m_nState) {
		if (m_nCurIndex >= pDt->m_VecPlist.size()) {
			m_nCurIndex = 0;
			m_nState = 2;//加载Audio的状态
			return;
		}
		SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
		pCache->addSpriteFramesWithFile(pDt->m_VecPlist[m_nCurIndex]);
		m_nCurIndex++;
		m_nCount++;

	}
	if (2 == m_nState) {
		if (m_nCurIndex >= pDt->m_VecAudio.size()) {
			m_nCurIndex = 0;
			m_nState = 0;//加载Audio的状态
			isCommonFinish = true;
			return;
		}
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(pDt->m_VecAudio[m_nCurIndex].c_str());
		m_nCurIndex++;
		m_nCount++;

	}
}
