#pragma once
// Std includes, CALL_VIRTUAL
#include "../platform.h"
// Include ang_t
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
	CALL_VIRTUAL(18U,	GetVAngles(ang_t& OutAngle), void(__thiscall*)(void*, ang_t&),	OutAngle);
	CALL_VIRTUAL(19U,	SetVAngles(ang_t& Angle),	void(__thiscall*)(void*, ang_t&),		Angle);
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
	virtual int			GetPointContents(const vec3d_t& Point, int Mask = MASK_ALL, IHandleEntity** Entities = NULL) = 0;
	virtual int			GetPointContents_WorldOnly(const vec3d_t& Position, int Mask = MASK_ALL) = 0;
	virtual int			GetPointContents_Collideable(ICollideable* Collideable, const vec3d_t& Pos) = 0;
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
	virtual void		AddBoxOverlay(const vec3d_t& Origin, const vec3d_t& Mins, const vec3d_t& Max, const ang_t& Orientation, Color4_t Color, float Duration) = 0;

	// You'll need to pass MATH_PI and MATH_THETA here
	virtual void		AddSphereOverlay(const vec3d_t& Origin, float Radius, int Math_Theta, int Math_Pi, Color4_t Color, float Duration) = 0;
	virtual void		AddTriangleOverlay(const vec3d_t& p1, const vec3d_t& p2, const vec3d_t& p3, Color4_t Color, bool NoDepthTest, float Duration) = 0;
	virtual void		AddLineOverlay(const vec3d_t& p1, const vec3d_t& p2, Color3_t Color, bool NoDepthTest, float Duration) = 0;
	virtual void		AddWorldTextOverlay(const vec3d_t& Origin, float Duration, const char* Format, ...) = 0;
	virtual void		AddWorldTextOverlay(const vec3d_t& Origin, int LineOffset, float Duration, const char* Format, ...) = 0;
	virtual void		AddScreenTextOverlay(const vec2d_t& Origin, float Duration, Color4_t Color, const char* Text) = 0;
};