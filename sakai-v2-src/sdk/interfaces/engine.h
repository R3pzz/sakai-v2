#pragma once
// Std includes, CALL_VIRTUAL
#include "../platform.h"
// Include QAngle
#include "../types/angle.h"
// Include VMatrix
#include "../types/matrix.h"
// Include Ray_t, CBaseTrace, CGameTrace etc...
#include "../types/tracehelpers.h"

class INetChannelInfo;
class ISpatialQuery;
class ICollideable;
class INetChannel;
struct CPlayerInfo;

class IEngine {
public:
	// Things connected with local player:
	CALL_VIRTUAL(8U,	GetPlayerInfo(int Index, CPlayerInfo* Info), void(__thiscall*)(void*, int, CPlayerInfo*), Index, Info);
	CALL_VIRTUAL(9U,	GetPlayerForUID(int Index),	int(__thiscall*)(void*, int),			Index);
	CALL_VIRTUAL(12U,	GetPLocalPlayer(),			void(__thiscall*)(void*));
	CALL_VIRTUAL(20U,	GetMaxClients(),			int(__thiscall*)(void*));
	// Things connected with engine itself:
	CALL_VIRTUAL(14U,	GetLastTimeStamp(),			float(__thiscall*)(void*));
	CALL_VIRTUAL(36U,	GetGameDirectrory(),		const char* (__thiscall*)(void*));
	CALL_VIRTUAL(37U,	GetTransformScreenMatrix(),	VMatrix& (__thiscall*)(void*));
	CALL_VIRTUAL(38U,	GetTransformViewMatrix(),	VMatrix& (__thiscall*)(void*));
	CALL_VIRTUAL(43U,	GetBSPTreeQuery(),			ISpatialQuery* (__thiscall*)(void*)); // BSP Tree is a special way of splitting a map into peaces.
	CALL_VIRTUAL(78U,	GetNetChannelInfo(),		INetChannelInfo* (__thiscall*)(void*));
	CALL_VIRTUAL(104U,	GetEngineBuildNumber(),		uintptr_t* (__thiscall*)(void*));
	// Things connected with levels / maps:
	CALL_VIRTUAL(52U,	GetLevelName(),				const char* (__thiscall*)(void*));
	CALL_VIRTUAL(53U,	GetLevelNameShort(),		const char* (__thiscall*)(void*));
	// Things connected with view setup / position etc...:
	CALL_VIRTUAL(18U,	GetVAngles(QAngle& OutAngle), void(__thiscall*)(void*, QAngle&),	OutAngle);
	CALL_VIRTUAL(19U,	SetVAngles(QAngle& Angle),	void(__thiscall*)(void*, QAngle&),		Angle);
	// Things connected with client activities:
	CALL_VIRTUAL(26U,	IsInGame(),					bool(__thiscall*)(void*));
	CALL_VIRTUAL(27U,	IsConnected(),				bool(__thiscall*)(void*));
	CALL_VIRTUAL(82U,	IsPlayingDemo(),			bool(__thiscall*)(void*));
	CALL_VIRTUAL(83U,	IsRecordingDemo(),			bool(__thiscall*)(void*));
	CALL_VIRTUAL(90U,	IsPaused(),					bool(__thiscall*)(void*));
	CALL_VIRTUAL(92U,	IsTakingScreenshot(),		bool(__thiscall*)(void*));
	CALL_VIRTUAL(93U,	IsHLTV(),					bool(__thiscall*)(void*));
	// Things connected with events system:
	CALL_VIRTUAL(59U,	FireEvents(),				void(__thiscall*)(void*));
};

class IEngineTrace {
public:
	// Get mesh which contains certain point:
	virtual int			GetPointContents(const CVector3& Point, int Mask = MASK_ALL, IHandleEntity** Entities = NULL) = 0;
	virtual int			GetPointContents_WorldOnly(const CVector3& Position, int Mask = MASK_ALL) = 0;
	virtual int			GetPointContents_Collideable(ICollideable* Collideable, const CVector3& Pos) = 0;
	// Sets ray endpos to entity origin:
	virtual void		ClipRayToEntity(const Ray_t& Ray, uint32_t Mask, IHandleEntity* Entity, CGameTrace* Trace) = 0;
	virtual void		ClipRayToCollideable(const Ray_t& Ray, uint32_t Mask, ICollideable* Collideable, CGameTrace* Trace) = 0;
	// Traces a ray:
	virtual void		TraceRay(const Ray_t& Ray, uint32_t Mask, ITraceFilter* Filter, CGameTrace* Trace) = 0;
};

class IEngineSound {
public:

};

class IEngineEffects {
public:

};

class IDebugOverlay {
public:
	virtual void		AddEntityTextOverlay(int EntityIdx, int Offset, float Duration, Color4_t Color, const char* Format, ...) = 0;
	virtual void		AddBoxOverlay(const CVector3& Origin, const CVector3& Mins, const CVector3& Max, const QAngle& Orientation, Color4_t Color, float Duration) = 0;

	// You'll need to pass MATH_PI and MATH_THETA here
	virtual void		AddSphereOverlay(const CVector3& Origin, float Radius, int Math_Theta, int Math_Pi, Color4_t Color, float Duration) = 0;
	virtual void		AddTriangleOverlay(const CVector3& p1, const CVector3& p2, const CVector3& p3, Color4_t Color, bool NoDepthTest, float Duration) = 0;
	virtual void		AddLineOverlay(const CVector3& p1, const CVector3& p2, Color3_t Color, bool NoDepthTest, float Duration) = 0;
	virtual void		AddWorldTextOverlay(const CVector3& Origin, float Duration, const char* Format, ...) = 0;
	virtual void		AddWorldTextOverlay(const CVector3& Origin, int LineOffset, float Duration, const char* Format, ...) = 0;
	virtual void		AddScreenTextOverlay(const CVector2& Origin, float Duration, Color4_t Color, const char* Text) = 0;
};