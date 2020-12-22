#ifndef __DynamicDt_H__
#define __DynamicDt_H__
#include"cocos2d.h"
class CDynamicDt
{
public:

	static CDynamicDt* getInstance();

	CC_SYNTHESIZE(int,m_nLevelID,LevelID);
	CC_SYNTHESIZE(int,m_nMapGold,MapGold);
	CC_SYNTHESIZE(int,m_nWaveIndex, WaveIndex);
	CC_SYNTHESIZE(int,m_nRadishHp, RadishHp);
private:
	CDynamicDt();
	~CDynamicDt();
	static CDynamicDt* m_pInstance;
};


#endif
