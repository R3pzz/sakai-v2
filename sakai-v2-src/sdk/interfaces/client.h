#pragma once
// Include CALL_VIRTUAL, std stuff
#include "../platform.h"
// Include CVector3
#include "../types/vector.h"

class INetChannel;
class INetChannelInfo;
class CClientClass;
class CStandardRecvProxies;
class CEventInfo;

class IClientDLL {
public:
	// Gets all client classes to parse a recv table
	CALL_VIRTUAL(8U,	GetAllClasses(),			CClientClass* (__thiscall*)(void*));

	// Update all hud elements (called "thinking")
	CALL_VIRTUAL(11U,	HUD_Update(bool Active),	void(__thiscall*)(void*, bool),			Active);

	// Can we hear a specified player?
	CALL_VIRTUAL(32U,	PlayerAudible(int Index),	bool(__thiscall*)(void*, int),			Index);

	// Get standard recv proxies for hooking
	CALL_VIRTUAL(45U,	GetStandardRecvProxies(),	CStandardRecvProxies* (__thiscall*)(void*));
};

class CClientState {
public:
	pad_t				_0[0x9C];				// 0x0000
	INetChannel*		m_pNetChannel;			// 0x009C
	int					m_iChallengeNr;			// 0x00A0
	pad_t				_1[0x64];				// 0x00A4
	int					m_iSignonState;			// 0x0108
	pad_t				_2[0x8];				// 0x010C
	float				m_flNextCmdTime;		// 0x0114
	int					m_nServerCount;			// 0x0118
	int					m_iCurrentSequence;		// 0x011C
	pad_t				_3[0x54];				// 0x0120
	int					m_iDeltaTick;			// 0x0174
	bool				m_bPaused;				// 0x0178
	pad_t				_4[0x7];				// 0x0179
	int					m_iViewEntity;			// 0x0180
	int					m_iPlayerSlot;			// 0x0184
	char				m_szLevelName[MAX_PATH];// 0x0188
	char				m_szLevelNameShort[80];	// 0x028C
	char				m_szMapGroupName[80];	// 0x02DC
	char				m_szLastLevelNameShort[80]; // 0x032C
	pad_t				_5[0xC];				// 0x037C
	int					m_nMaxClients;			// 0x0388 
	pad_t				_6[0x498C];				// 0x038C
	float				m_flLastServerTickTime;	// 0x4D18
	bool				m_bInSimulation;		// 0x4D1C
	pad_t				_7[0x3];				// 0x4D1D
	int					m_iOldTickcount;		// 0x4D20
	float				m_flTickRemainder;		// 0x4D24
	float				m_flFrameTime;			// 0x4D28
	int					m_iLastOutgoingCommand;	// 0x4D2C
	int					m_nChokedCommands;		// 0x4D30
	int					m_iLastCommandAck;		// 0x4D34
	int					m_iCommandAck;			// 0x4D38
	int					m_iSoundSequence;		// 0x4D3C
	pad_t				_8[0x50];				// 0x4D40
	QAngle				m_angViewPoint;			// 0x4D90
	pad_t				_9[0xD0];				// 0x4D9C
	CEventInfo*			m_pEvents;				// 0x4E6C
};

// CS:GO Client state pointer
extern CClientState* g_pClientState;

/*
* Get our net channel
*/
INetChannel* GetNetChannel() { return g_pClientState ? g_pClientState->m_pNetChannel : NULL; }

class IEffects {
public:
	// Just paddings to align the VMT
	virtual void		_0() {}
	virtual void		_1() {}
	// Effects:
	virtual void		Smoke(const CVector3& Origin, int Index, float Scale, float Framerate) = 0;
	virtual void		Sparks(const CVector3& Position, int Magnitude = 1, int TrailLength = 1, const CVector3* Direction = NULL) = 0;
	virtual void		Dust(const CVector3& Position, const CVector3& Direction, float Size, float Speed) = 0;
	virtual void		MuzzleFlash(const CVector3& Origin, const QAngle& Angles, float Scale, int Type) = 0;
	virtual void		MetalSparks(const CVector3& Position, const CVector3& Direction) = 0;
	virtual void		EnergySplash(const CVector3& Position, const CVector3& Direction, bool Explosive = false) = 0;
	virtual void		Ricochet(const CVector3& Position, const CVector3& Direction) = 0;

	// Suppress all sounds emitted by effects
	CALL_VIRTUAL(11U,	SuppressSound(bool Suppress), void(__thiscall*)(void*, bool),			Suppress);
};

class CEventInfo {
public:
	short				m_nClassID;
	float				m_flFireDelay;
	const void*			m_pSendTable;
	const CClientClass* m_pClientClass;
	void*				m_pData;
	std::intptr_t		m_iPackedBits;
	int					m_iFlags;
	pad_t				_0[0x16];
};