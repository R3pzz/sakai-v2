#pragma once

/*
* CSGO's global vars.
*/
class CGlobalVarsBase {
public:
	float			m_flRealTime;
	int				m_iFrameCount;
	float			m_flAbsFrameTime;
	float			m_flAbsFrameStartTime;
	float			m_flCurTime;
	float			m_flFrameTime;
	int				m_iMaxClients;
	int				m_iTickCount;
	float			m_flIntervalPerTick;
	float			m_flInterpolationAmount;
	int				m_iSimTicksThisFrame;
	int				m_iNetworkProtocol;
	void*			m_pSaveData;
	bool			m_bClient;
	bool			m_bRemoteClient;
	int				m_nTimestampNetworkingBase;
	int				m_nTimestampRandomizeWindow;
};