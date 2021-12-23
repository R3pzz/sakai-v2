#pragma once
// Include __forceinline macro
#include "../platform.h"
// Include vec3a_t
#include "vector.h"
// Include m3x4_t
#include "matrix.h"
// Include surface flags
#include "surfaceflags.h"

class IHandleEntity;
class C_BaseEntity;

namespace U {
	/*
	* Trace type for trace filter to know
	*	which entities to skip.
	*/
	enum ETraceType : int {
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,
		TRACE_ENTITIES_ONLY,
		TRACE_EVERYTHING_FILTER_PROPS
	};
}

/*
* This is a class to tell trace system which entities
*	to skip.
*/
class ITraceFilter {
public:
	virtual bool			ShouldHitEntity(IHandleEntity* Entity, int Mask) = 0;
	virtual U::ETraceType	GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter {
public:
	CTraceFilter() { }
	CTraceFilter(IHandleEntity* Skip, U::ETraceType Type = U::ETraceType::TRACE_EVERYTHING) : m_pSkip(Skip), m_iType(Type) { }

public:
	/*
	* Should current ray hit entity?
	*/
	__forceinline bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return Handle != m_pSkip; }
	__forceinline U::ETraceType GetTraceType() const { return m_iType; }

public:
	// Entity to skip
	IHandleEntity*		m_pSkip = NULL;
	// Type of trace
	U::ETraceType		m_iType = U::ETraceType::TRACE_EVERYTHING;
};

/*
* This is a filter for skipping two entities on a ray.
*/
class CTraceFilterSkipTwoEntities : public ITraceFilter {
public:
	CTraceFilterSkipTwoEntities() = default;
	CTraceFilterSkipTwoEntities(IHandleEntity* Skip1, IHandleEntity* Skip2) : m_pSkip1(Skip1), m_pSkip2(Skip2) { }

public:
	__forceinline bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return Handle != m_pSkip1 && Handle != m_pSkip2; }
	__forceinline U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_EVERYTHING; }

public:
	IHandleEntity* m_pSkip1 = NULL;
	IHandleEntity* m_pSkip2 = NULL;
};

/*
* Do not account hitting world entities and props.
*/
class CTraceFilterWorldOnly : public ITraceFilter {
public:
	__forceinline bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return false; }
	__forceinline U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_WORLD_ONLY; }
};

/*
* Do not account hitting world entities.
*/
class CTraceFilterWorldAndPropsOnly : public ITraceFilter {
public:
	__forceinline bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return false; }
	__forceinline U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_EVERYTHING; }
};

/*
* Do not account hitting players.
*/
class CTraceFilterNoPlayers : public CTraceFilter {
public:
	__forceinline bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) override { return false; }
};

/*
* Entity we did hit while tracing a ray.
*/
class CTraceEntity : public ITraceFilter {
public:
	CTraceEntity() { }
	CTraceEntity(IHandleEntity* Handle) { m_pHitEntity = Handle; }

	__forceinline bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return Handle == m_pHitEntity; }
	__forceinline U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_ENTITIES_ONLY; }

	IHandleEntity* m_pHitEntity = NULL;
};

/*
* Some structs for tracing.
*/
struct Surface_t {
	const char*		m_szName;
	std::int16_t	m_iSurfaceProps;
	std::uint16_t	m_iFlags;
};

struct Plane_t {
	vec3d_t		m_vecNormal;
	float			m_flDist;
	char			m_chType;
	char			m_chSignbits;
	char			_0[2];
};

struct Ray_t {
	Ray_t() : m_pWorldAxisTransform(NULL) {}

	__forceinline void Init(const vec3a_t& Start, const vec3a_t& End) {
		m_vecDelta = Start - End;
		m_bIsSwept = (m_vecDelta.LengthSqr() != 0);

		m_vecExtents.Zero();
		m_pWorldAxisTransform = NULL;
		m_bIsRay = true;

		m_vecStartOffset.Zero();
		std::memcpy(m_vecStart.Base(), Start.Base(), sizeof(vec3a_t));
	}

	vec3a_t		m_vecStart;
	vec3a_t		m_vecDelta;
	vec3a_t		m_vecStartOffset;
	vec3a_t		m_vecExtents;
	const m3x4_t* m_pWorldAxisTransform;
	bool			m_bIsRay;
	bool			m_bIsSwept;
};

class CBaseTrace {
public:
	CBaseTrace() {}

public:
	// Displacement flags tests.
	bool IsDispSurface() { return (m_iDispFlags & DISPSURF_FLAG_SURFACE) != 0; }
	bool IsDispSurfaceWalkable() { return (m_iDispFlags & DISPSURF_FLAG_WALKABLE) != 0; }
	bool IsDispSurfaceBuildable() { return (m_iDispFlags & DISPSURF_FLAG_BUILDABLE) != 0; }
	bool IsDispSurfaceProp1() { return (m_iDispFlags & DISPSURF_FLAG_SURFPROP1) != 0; }
	bool IsDispSurfaceProp2() { return (m_iDispFlags & DISPSURF_FLAG_SURFPROP2) != 0; }
	bool IsDispSurfaceProp3() { return (m_iDispFlags & DISPSURF_FLAG_SURFPROP3) != 0; }
	bool IsDispSurfaceProp4() { return (m_iDispFlags & DISPSURF_FLAG_SURFPROP4) != 0; }

public:
	// Start position
	vec3d_t		m_vecStartPos;
	// Final position
	vec3d_t		m_vecEndPos;
	// Plane at impact position if not solid
	Plane_t			m_Plane;
	// Time we completed our trace (1.0 if we did not hit anything)
	float			m_flFraction;
	// Contents on other side of surface hit
	int				m_iContents;
	// Displacement flags
	unsigned short	m_iDispFlags;
	// Did we hit solid props?
	bool			m_bWasHitSolid;
	// Did we start in solid area?
	bool			m_bDidStartInSolid;
};

class CGameTrace : public CBaseTrace {
public:
	CGameTrace() : m_pEnt(NULL) {}

public:
	/*
	* Did our ray hit world? (like walls, floor etc...)
	*/
	__forceinline bool DidHitWorld() const;

	/*
	* Did our ray hit something out of the world?
	*/
	__forceinline bool DidHitNonWorldEntity() const;
	/*
	* Get index of hit entity.
	*/
	__forceinline int GetEntityIndex() const;

	/*
	* Did we hit any entities?
	*/
	__forceinline bool DidHit() const;

public:
	// Time we left a solid world part
	float			m_flFractionLeftSolid;
	// Surface we did hit
	Surface_t		m_Surface;
	// Body part of an entity we hit
	int				m_iHitgroup;
	// Studio bone of an entity we hit
	short			m_nBone;
	// Index of surface we hit
	unsigned short	m_nWorldSurfaceIndex;
	// Entity we hit with our ray
	C_BaseEntity*	m_pEnt;
	// Studio hitbox we hit with our ray
	int				m_nHitbox;
};