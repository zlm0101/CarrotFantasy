#include"DynamicDt.h"

CDynamicDt * CDynamicDt::m_pInstance = nullptr;
CDynamicDt::CDynamicDt()
	:m_nLevelID(0)
	,m_nMapGold(0)
	,m_nWaveIndex(1),
	m_nRadishHp(0)
{
}

CDynamicDt::~CDynamicDt()
{
}



CDynamicDt * CDynamicDt::getInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CDynamicDt();
	}
	return m_pInstance;
}