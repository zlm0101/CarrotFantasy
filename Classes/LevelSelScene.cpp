#include"LevelSelScene.h"
#include"DynamicDt.h"
#include"GameScene.h"
#include"LoadingScene.h"
#include"ConfigMgr.h"
#include"GameMenu.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
CLevelSelScene::CLevelSelScene()
	:levelID(0)
{
}

CLevelSelScene::~CLevelSelScene()
{
}

bool CLevelSelScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* pBg = Sprite::createWithSpriteFrameName("ui_S_Bg.png");
	pBg->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	this->addChild(pBg);

	m_pPage = PageView::create();
	this->addChild(m_pPage);
	m_pPage->setDirection(ScrollView::Direction::HORIZONTAL);
	m_pPage->setPosition(Vec2(200,200));
	m_pPage->setSize(Size(500,350));
	//m_pPage->setIndicatorEnabled(true);

	for (int i = 0; i < 4;i++) {
		Layout* pLayout = Layout::create();
		pLayout->setSize(Size(500,350));
		ImageView* pImage = ImageView::create(StringUtils::format("ui_map_%02d.png",i+1),Widget::TextureResType::PLIST);
		pLayout->addChild(pImage);
		pImage->setAnchorPoint(Vec2(0,0));

		SselLevelDt* pConfig = static_cast<SselLevelDt*>(CConfigMgr::getInstance()->getData("SelLevelDtMgr")->getDataByID(i+1));

		for (int j = 0; j < pConfig->VecBatteryImg.size();j++) {
			Sprite* pBattery = Sprite::createWithSpriteFrameName(pConfig->VecBatteryImg[j]);
			pLayout->addChild(pBattery);
			pBattery->setPosition(Vec2(200+j*60,pBattery->getContentSize().height/2));
		}

		m_pPage->addChild(pLayout);
	}




	m_pStartButton = Button::create("Menu/startNor.png","Menu/startSel.png","",Widget::TextureResType::LOCAL);
	m_pStartButton->addTouchEventListener(CC_CALLBACK_1(CLevelSelScene::onButtonClick,this));
	this->addChild(m_pStartButton);
	m_pStartButton->setPosition(Vec2(origin.x + visibleSize.width / 2,120));



	m_pBackButton = Button::create("Menu/backNor.png", "Menu/backSel.png", "", Widget::TextureResType::LOCAL);
	m_pBackButton->addTouchEventListener(CC_CALLBACK_1(CLevelSelScene::onButtonClick, this));
	this->addChild(m_pBackButton);
	m_pBackButton->setPosition(Vec2(origin.x+m_pBackButton->getContentSize().width/2,origin.y+visibleSize.height-m_pBackButton->getContentSize().height/2));

	return true;
}

void CLevelSelScene::onButtonClick(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Menu/click.mp3", false);
	if (pSender == m_pStartButton) {
		CDynamicDt::getInstance()->setLevelID(m_pPage->getCurPageIndex() + 1001);
		auto scene = CLoadingScene::createWithData("Game");
		Director::getInstance()->replaceScene(scene);
	}
	else if (pSender == m_pBackButton) {
		//·µ»Ø²Ëµ¥
		Director::getInstance()->replaceScene(CCTransitionZoomFlipAngular::create(1, CGameMenu::create()));
	}
}
