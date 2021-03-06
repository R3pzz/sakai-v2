#pragma once
// Include CALL_VIRTUAL, std stuff
#include "../platform.h"
// Include CVector3
#include "../types/vector.h"
// Include CGlobalVarsBase
#include "globalvars.h"

class CBaseEntity;
class CBasePlayer;

namespace U
{
	/*
	* Handle to a specific entity.
	*/
	using EntityHandle_t = std::uint16_t;
}

struct CMoveData
{
	bool			m_bFirstRunOfFunctions;
	bool			m_bGameCodeMovedPlayer;
	bool			m_bNoAirControl;
	U::EntityHandle_t m_nPlayerHandle;
	int				m_nImpulseCommand;
	QAngle			m_vecViewAngles;
	QAngle			m_vecAbsViewAngles;
	int				m_iButtons;
	int				m_iOldButtons;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;
	float			m_flMaxSpeed;
	float			m_flClientMaxSpeed;
	CVector3		m_vecVelocity;
	CVector3		m_vecTrailingVelocity;
	float			m_flTrailingVelocityTime;
	QAngle			m_vecAngles;
	QAngle			m_vecOldAngles;
	float			m_outStepHeight;
	CVector3		m_outWishVel;
	CVector3		m_outJumpVel;
	CVector3		m_vecConstraintCenter;
	float			m_flConstraintRadius;
	float			m_flConstraintWidth;
	float			m_flConstraintSpeedFactor;
	bool			m_bConstraintPastRadius;
	CVector3		m_vecAbsOrigin;
};

struct CUserCmd
{
	int				m_nCommand;
	int				m_iTickCount;
	QAngle			m_angViewAngles;
	CVector3		m_vecAimDirection;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;
	int				m_iButtons;
	std::uint8_t	m_nImpulse;
	int				m_iWeapon;
	int				m_iWeaponSubType;
	int				m_iRandomSeed;
	short			m_iMouseX;
	short			m_iMouseY;
	bool			m_bHasBeenPredicted;
	QAngle			m_angHeadAngles;
	CVector3		m_vecHeadOffset;
};

struct CVerifiedUserCmd
{
	CUserCmd*		m_pCmd;
	std::uint32_t	m_CRC;
};

class IGameMovement
{
public:
	virtual	~IGameMovement() { }

	virtual void		ProcessMovement(CBasePlayer* Player, CMoveData* Move) = 0;
	virtual void		Reset() = 0;
	virtual void		StartTrackPredictionErrors(CBasePlayer* Player) = 0;
	virtual void		FinishTrackPredictionErrors(CBasePlayer* Player) = 0;
};

class IMoveHelper
{
public:
	CALL_VIRTUAL(1U,	SetHost(CBaseEntity* Host),		void(__thiscall*)(void*, CBaseEntity*), Host);
};

class IPrediction
{
public:
	CALL_VIRTUAL(20U,	SetupMove(CBasePlayer* Player, CUserCmd* Cmd, IMoveHelper* Helper, CMoveData* Data),
		void(__thiscall*)(void*, CBasePlayer*, CUserCmd*, IMoveHelper*, CMoveData*),			Player, Cmd, Helper, Data);
	CALL_VIRTUAL(21U,	FinishMove(CBasePlayer* Player, CUserCmd* Cmd, CMoveData* Data),
		void(__thiscall*)(void*, CBasePlayer*, CUserCmd*, CMoveData*),							Player, Cmd, Data);

public:
	std::int8_t		_0[8];
	// Is running prediction?
	bool			m_bInPrediction;
	// Is being first time predicted?
	bool			m_bIsFirstTimePredicted;
	// Is engine paused?
	bool			m_bEnginePaused;
	bool			m_bOldCLPredictValue;
	int				m_iPreviousStartFrame;
	int				m_nIncomingPacketNumber;
	float			m_flLastServerWorldTimeStamp;
	std::uint8_t	_1[104];
	// Saved global vars
	CGlobalVarsBase	m_SavedGlobals;
};