#include"GameOver.h"
#include"DynamicDt.h"
#include"GameScene.h"
CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
}

bool CGameOver::init()
{
	if (!Node::init()) {
		return false;
	}
	if (CGameScene::getInstance()->getOverOrEnd() == "Over") {
		this->createGameOver();
	}
	else if (CGameScene::getInstance()->getOverOrEnd() == "End") {
		this->createGameSuccess();
	}
	return true;
}

void CGameOver::createGameSuccess()
{
	Sprite* pBg = Sprite::createWithSpriteFrameName("ui_GameWinNew.png");
	this->addChild(pBg);

	Sprite* pJitui = Sprite::createWithSpriteFrameName("JiTui.png");
	pJitui->setPosition(this->getPositionX() - pJitui->getContentSize().width - 15, 23);
	this->addChild(pJitui);

	Label* m_pWaveLabel = Label::createWithTTF(StringUtils::format("0 %d", CDynamicDt::getInstance()->getWaveIndex()), "fonts/comicbd.ttf", 30);
	m_pWaveLabel->setPosition(this->getPositionX() - 5, 23);
	m_pWaveLabel->setColor(ccc3(255, 255, 224));
	this->addChild(m_pWaveLabel);

	Sprite* pGuaiWu = Sprite::createWithSpriteFrameName("GuaiWu.png");
	pGuaiWu->setPosition(this->getPositionX() + pGuaiWu->getContentSize().width+10, 23);
	this->addChild(pGuaiWu);

	Label* m_pCurLevel = Label::createWithTTF(StringUtils::format("%s:0%d", this->G2U("¹Ø¿¨"), CDynamicDt::getInstance()->getLevelID() - 1000), "fonts/msyhbd.ttc", 15);
	m_pCurLevel->setPosition(this->getPositionX() - 75, -17);
	this->addChild(m_pCurLevel);

	Sprite* pMaoXian = Sprite::createWithSpriteFrameName("DangQian.png");
	pMaoXian->setPosition(this->getPositionX() + 25, -17);
	this->addChild(pMaoXian);


	m_pLevelSel = Button::create("2.png", "0.png", "", Widget::TextureResType::PLIST);
	m_pLevelSel->setPosition(Vec2(this->getPositionX() - m_pLevelSel->getContentSize().width / 2 - 20, this->getPositionY() - 65));
	m_pLevelSel->addClickEventListener(CC_CALLBACK_1(CGameOver::click, this));
	this->addChild(m_pLevelSel);




	m_pTryAgain = Button::create("5.png", "3.png", "", Widget::TextureResType::PLIST);
	m_pTryAgain->setPosition(Vec2(this->getPositionX() + m_pLevelSel->getContentSize().width / 2 - 10, this->getPositionY() - 65));
	m_pTryAgain->addClickEventListener(CC_CALLBACK_1(CGameOver::click, this));
	this->addChild(m_pTryAgain);
	if (CDynamicDt::getInstance()->getRadishHp() == 10) {
		Sprite* pRadish = Sprite::createWithSpriteFrameName("Gold.png");
		pRadish->setPosition(this->getPositionX() - 5,100);
		this->addChild(pRadish);
	}
	else if (CDynamicDt::getInstance()->getRadishHp()<= 9&& CDynamicDt::getInstance()->getRadishHp()>=5) {
		Sprite* pRadish = Sprite::createWithSpriteFrameName("Sliver.png");
		pRadish->setPosition(this->getPositionX() - 5, 100);
		this->addChild(pRadish);
	}
	else if (CDynamicDt::getInstance()->getRadishHp() <= 4) {
		Sprite* pRadish = Sprite::createWithSpriteFrameName("Normal.png");
		pRadish->setPosition(this->getPositionX() - 5, 100);
		this->addChild(pRadish);
	}
}

void CGameOver::createGameOver()
{
	Sprite* pBg = Sprite::createWithSpriteFrameName("ui_GameOverNew.png");
	this->addChild(pBg);

	Sprite* pJitui = Sprite::createWithSpriteFrameName("JiTui.png");
	pJitui->setPosition(this->getPositionX()-pJitui->getContentSize().width-15,17);
	this->addChild(pJitui);

	Label* m_pWaveLabel = Label::createWithTTF(StringUtils::format("0 %d", CDynamicDt::getInstance()->getWaveIndex()), "fonts/comicbd.ttf", 30);
	m_pWaveLabel->setPosition(this->getPositionX()-15,17);
	m_pWaveLabel->setColor(ccc3(255, 255, 224));
	this->addChild(m_pWaveLabel);

	Sprite* pGuaiWu = Sprite::createWithSpriteFrameName("GuaiWu.png");
	pGuaiWu->setPosition(this->getPositionX() + pGuaiWu->getContentSize().width, 17);
	this->addChild(pGuaiWu);

	Label* m_pCurLevel = Label::createWithTTF(StringUtils::format("%s:0%d", this->G2U("¹Ø¿¨"), CDynamicDt::getInstance()->getLevelID()-1000), "fonts/msyhbd.ttc", 15);
	m_pCurLevel->setPosition(this->getPositionX() - 75, -20);
	this->addChild(m_pCurLevel);

	Sprite* pMaoXian = Sprite::createWithSpriteFrameName("DangQian.png");
	pMaoXian->setPosition(this->getPositionX()+25, -20);
	this->addChild(pMaoXian);


	m_pLevelSel = Button::create("2.png","0.png","",Widget::TextureResType::PLIST);
	m_pLevelSel->setPosition(Vec2(this->getPositionX()-m_pLevelSel->getContentSize().width/2-20,this->getPositionY()-65));
	m_pLevelSel->addClickEventListener(CC_CALLBACK_1(CGameOver::click,this));
	this->addChild(m_pLevelSel);




	m_pTryAgain = Button::create("5.png", "3.png", "", Widget::TextureResType::PLIST);
	m_pTryAgain->setPosition(Vec2(this->getPositionX() + m_pLevelSel->getContentSize().width / 2-10, this->getPositionY() - 65));
	m_pTryAgain->addClickEventListener(CC_CALLBACK_1(CGameOver::click, this));
	this->addChild(m_pTryAgain);
}

char * CGameOver::G2U(const char * gb2312)
{
	int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;

}

void CGameOver::click(Ref * pSender)
{
}
