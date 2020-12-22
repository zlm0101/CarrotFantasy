#ifndef __TiledMapCtrl_H__
#define __TiledMapCtrl_H__

#include "cocos2d.h"
#include"DataClass.h"
using namespace std;
USING_NS_CC;
class CTiledMapCtrl:public Node
{
public:
	CTiledMapCtrl();
	~CTiledMapCtrl();
	bool initWithData(SLevelDt* pData);

	Vec2 getTiledByPos(const Vec2& pos);
	Vec2 getPosByTiled(const Vec2& tiled);
	static CTiledMapCtrl* createWithData(SLevelDt* pData);
public:
	bool isObstacles(const Vec2& tile);//判断该点是否是障碍物
	map<int, Vec2> m_MapObPos;//存储障碍物位置信息
	map<int, Vec2> m_MapPathPos;//存储路径信息
	bool isNullTile(const Vec2& tile);//判断鼠标点击点是否是空
private:
	void initMap(SLevelDt* pData);
	void initObjGroup();
private:
	TMXObjectGroup* m_pPathObjGroup;
	TMXObjectGroup* m_pObstacles;
	TMXTiledMap* m_pTiledMap;
	TMXLayer* m_pPath;
};
#endif
