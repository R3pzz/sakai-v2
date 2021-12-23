#pragma once
// Include CALL_VIRTUAL, std stuff
#include "../platform.h"
// Include vec3d_t
#include "../types/vector.h"
// Include CGlobalVarsBase
#include "globalvars.h"

class C_BaseEntity;
class C_BasePlayer;

namespace U {
	/*
	* Handle to a specific entity.
	*/
	using EntityHandle_t = std::uint16_t;
}

struct CMoveData {
	bool			m_bFirstRunOfFunctions;
	bool			m_bGameCodeMovedPlayer;
	bool			m_bNoAirControl;
	U::EntityHandle_t m_nPlayerHandle;
	int				m_nImpulseCommand;
	ang_t			m_vecViewAngles;
	ang_t			m_vecAbsViewAngles;
	int				m_iButtons;
	int				m_iOldButtons;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;
	float			m_flMaxSpeed;
	float			m_flClientMaxSpeed;
	vec3d_t		m_vecVelocity;
	vec3d_t		m_vecTrailingVelocity;
	float			m_flTrailingVelocityTime;
	ang_t			m_vecAngles;
	ang_t			m_vecOldAngles;
	float			m_outStepHeight;
	vec3d_t		m_outWishVel;
	vec3d_t		m_outJumpVel;
	vec3d_t		m_vecConstraintCenter;
	float			m_flConstraintRadius;
	float			m_flConstraintWidth;
	float			m_flConstraintSpeedFactor;
	bool			m_bConstraintPastRadius;
	vec3d_t		m_vecAbsOrigin;
};

struct CUserCmd {
	int				m_nCommand;
	int				m_iTickCount;
	ang_t			m_angViewAngles;
	vec3d_t		m_vecAimDirection;
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
	ang_t			m_angHeadAngles;
	vec3d_t		m_vecHeadOffset;
};

class IGameMovement {
public:
	virtual	~IGameMovement() { }

	virtual void		ProcessMovement(C_BasePlayer* Player, CMoveData* Move) = 0;
	virtual void		Reset() = 0;
	virtual void		StartTrackPredictionErrors(C_BasePlayer* Player) = 0;
	virtual void		FinishTrackPredictionErrors(C_BasePlayer* Player) = 0;
};

class IMoveHelper {
public:
	CALL_VIRTUAL(1U,	SetHost(C_BaseEntity* Host),	void(__thiscall*)(void*, C_BaseEntity*), Host);
};

class IPrediction {
public:
	CALL_VIRTUAL(20U,	SetupMove(C_BasePlayer* Player, CUserCmd* Cmd, IMoveHelper* Helper, CMoveData* Data),
		void(__thiscall*)(void*, C_BasePlayer*, CUserCmd*, IMoveHelper*, CMoveData*),			Player, Cmd, Helper, Data);
	CALL_VIRTUAL(21U,	FinishMove(C_BasePlayer* Player, CUserCmd* Cmd, CMoveData* Data),
		void(__thiscall*)(void*, C_BasePlayer*, CUserCmd*, CMoveData*),							Player, Cmd, Data);

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