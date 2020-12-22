#include"TiledMapCtrl.h"
using namespace std;
CTiledMapCtrl::CTiledMapCtrl()
{
}

CTiledMapCtrl::~CTiledMapCtrl()
{
}

bool CTiledMapCtrl::initWithData(SLevelDt* pData)
{
	if (!Node::init()) {
		return false;
	}
	this->initMap(pData);
	this->initObjGroup();
	return true;
}

CTiledMapCtrl * CTiledMapCtrl::createWithData(SLevelDt* pData)
{
	CTiledMapCtrl* pMap = new CTiledMapCtrl();
	if (pMap&&pMap->initWithData(pData)) {
		pMap->autorelease();
		return pMap;
	}
	CC_SAFE_DELETE(pMap);
	return nullptr;
}

bool CTiledMapCtrl::isObstacles(const Vec2 & tile)
{
	for (int i = 0; i < m_MapObPos.size();i++) {
		Vec2 obPos = this->getTiledByPos(m_MapObPos[i]);
		if (tile == obPos) {
			return false;
		}
	}
}


void CTiledMapCtrl::initMap(SLevelDt* pData)
{
	m_pTiledMap = TMXTiledMap::create(pData->strMapName);
	this->addChild(m_pTiledMap);

	m_pPath = m_pTiledMap->getLayer("path");
}

void CTiledMapCtrl::initObjGroup()
{
	m_pPathObjGroup = m_pTiledMap->getObjectGroup("pathObject1");
	ValueVector PathObjs = m_pPathObjGroup->getObjects();
	for (cocos2d::Value& PathObj:PathObjs) {
		ValueMap valueMap = PathObj.asValueMap();
		Vec2 pos;
		pos.x = valueMap["x"].asFloat();
		pos.y = valueMap["y"].asFloat();
		m_MapPathPos.insert(pair<int, Vec2>(valueMap["name"].asInt(), pos));//得到该地图上所有的位置方向变换信息，也就是拐弯点


	}


	//得到该关卡的障碍物对象
	m_pObstacles = m_pTiledMap->getObjectGroup("obstacles");
	ValueVector obstaclesObjs = m_pObstacles->getObjects();
	for (cocos2d::Value& obstanlesObj : obstaclesObjs) {
		ValueMap valueMap = obstanlesObj.asValueMap();
		Vec2 pos;
		pos.x = valueMap["x"].asFloat();
		pos.y = valueMap["y"].asFloat();
		m_MapObPos.insert(pair<int, Vec2>(valueMap["name"].asInt(),pos));
	}
}

bool CTiledMapCtrl::isNullTile(const Vec2 & tile)
{
	unsigned int GID = m_pPath->getTileGIDAt(tile);
	if (GID == 0) {
		return true;
	}
	return false;
}

Vec2 CTiledMapCtrl::getTiledByPos(const Vec2 & pos)
{
	Size TileSize = m_pTiledMap->getTileSize();
	Size MapSize = m_pTiledMap->getMapSize();
	int TiledX = pos.x / TileSize.width;

	int TiledY = (MapSize.height*TileSize.height - pos.y) / TileSize.height;
	return Vec2(TiledX, TiledY);
}

Vec2 CTiledMapCtrl::getPosByTiled(const Vec2 & tiled)
{
	//获取每个格子的大小
	Size sizeTiled = m_pTiledMap->getTileSize();
	//获取地图大小
	Size sizeMap = m_pTiledMap->getMapSize();

	Vec2 pos;
	pos.x = tiled.x*sizeTiled.width + sizeTiled.width / 2;

	pos.y = (sizeMap.height - tiled.y)*sizeTiled.height - sizeTiled.height / 2;

	return pos;
}
