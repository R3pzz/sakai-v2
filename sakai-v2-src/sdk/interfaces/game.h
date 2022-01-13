#pragma once
// Include CALL_VIRTUAL
#include "../platform.h"

class IGameUIFuncs
{
public:
	CALL_VIRTUAL(6U,	IsConnectedToVACServer(),	bool(__thiscall*)(void*));
};

class IGameTypes
{
public:
	CALL_VIRTUAL(8U,	GetGameType(),				int(__thiscall*)(void*));
	CALL_VIRTUAL(9U,	GetGameMode(),				int(__thiscall*)(void*));
	CALL_VIRTUAL(10U,	GetMapName(),				const char* (__thiscall*)(void*));
	CALL_VIRTUAL(11U,	GetGameTypeName(),			const char* (__thiscall*)(void*));
	CALL_VIRTUAL(12U,	GetGameModeName(),			const char* (__thiscall*)(void*));
};

enum class EGameModes : int
{
	Casual = 0,
	Competitive = 1,
	CompetitiveUnranked = 2,
	GunGameProgressive = 0,
	GunGameBomb = 1,
	GunGameDeathmatch = 2,
	Training = 0,
	Custom = 0,
	CooperativeGuardian = 0,
	CooperativeMission = 1,
};