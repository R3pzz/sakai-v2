#pragma once
// Include FORCEINLINE macro
#include "../platform.h"
// Include CVector3a
#include "vector.h"
// Include CMatrix3x4
#include "matrix.h"
// Include surface flags
#include "surfaceflags.h"

class IHandleEntity;
class CBaseEntity;

namespace U
{
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
class ITraceFilter
{
public:
	virtual bool			ShouldHitEntity(IHandleEntity* Entity, int Mask) = 0;
	virtual U::ETraceType	GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	CTraceFilter() { }
	CTraceFilter(IHandleEntity* Skip, U::ETraceType Type = U::ETraceType::TRACE_EVERYTHING) : m_pSkip(Skip), m_iType(Type) { }

public:
	/*
	* Should current ray hit entity?
	*/
	FORCEINLINE bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return Handle != m_pSkip; }
	FORCEINLINE U::ETraceType GetTraceType() const { return m_iType; }

public:
	// Entity to skip
	IHandleEntity*		m_pSkip = NULL;
	// Type of trace
	U::ETraceType		m_iType = U::ETraceType::TRACE_EVERYTHING;
};

/*
* This is a filter for skipping two entities on a ray.
*/
class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
	CTraceFilterSkipTwoEntities() = default;
	CTraceFilterSkipTwoEntities(IHandleEntity* Skip1, IHandleEntity* Skip2) : m_pSkip1(Skip1), m_pSkip2(Skip2) { }

public:
	FORCEINLINE bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return Handle != m_pSkip1 && Handle != m_pSkip2; }
	FORCEINLINE U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_EVERYTHING; }

public:
	IHandleEntity* m_pSkip1 = NULL;
	IHandleEntity* m_pSkip2 = NULL;
};

/*
* Do not account hitting world entities and props.
*/
class CTraceFilterWorldOnly : public ITraceFilter
{
public:
	FORCEINLINE bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return false; }
	FORCEINLINE U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_WORLD_ONLY; }
};

/*
* Do not account hitting world entities.
*/
class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:
	FORCEINLINE bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return false; }
	FORCEINLINE U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_EVERYTHING; }
};

/*
* Do not account hitting players.
*/
class CTraceFilterNoPlayers : public CTraceFilter
{
public:
	FORCEINLINE bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) override { return false; }
};

/*
* Entity we did hit while tracing a ray.
*/
class CTraceEntity : public ITraceFilter
{
public:
	CTraceEntity() { }
	CTraceEntity(IHandleEntity* Handle) { m_pHitEntity = Handle; }

public:
	FORCEINLINE bool		ShouldHitEntity(IHandleEntity* Handle, int Mask) { return Handle == m_pHitEntity; }
	FORCEINLINE U::ETraceType GetTraceType() const { return U::ETraceType::TRACE_ENTITIES_ONLY; }

public:
	IHandleEntity* m_pHitEntity = NULL;
};

/*
* Some structs for tracing.
*/
struct Surface_t
{
	const char*		m_szName;
	std::int16_t	m_iSurfaceProps;
	std::uint16_t	m_iFlags;
};

struct Plane_t
{
	CVector3		m_vecNormal;
	float			m_flDist;
	char			m_chType;
	char			m_chSignbits;
	char			_0[2];
};

struct Ray_t
{
	Ray_t() : m_pWorldAxisTransform(NULL) {}

	FORCEINLINE void Init(const CVector3a& Start, const CVector3a& End) {
		m_vecDelta = Start - End;
		m_bIsSwept = (m_vecDelta.LengthSqr() != 0);

		m_vecExtents.Zero();
		m_pWorldAxisTransform = NULL;
		m_bIsRay = true;

		m_vecStartOffset.Zero();
		std::memcpy(m_vecStart.Base(), Start.Base(), sizeof(CVector3a));
	}

	CVector3a		m_vecStart;
	CVector3a		m_vecDelta;
	CVector3a		m_vecStartOffset;
	CVector3a		m_vecExtents;
	const CMatrix3x4* m_pWorldAxisTransform;
	bool			m_bIsRay;
	bool			m_bIsSwept;
};

class CBaseTrace
{
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
	CVector3		m_vecStartPos;
	// Final position
	CVector3		m_vecEndPos;
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

class CGameTrace : public CBaseTrace
{
public:
	CGameTrace() : m_pEnt(NULL) {}

public:
	/*
	* Did our ray hit world? (like walls, floor etc...)
	*/
	FORCEINLINE bool DidHitWorld() const;

	/*
	* Did our ray hit something out of the world?
	*/
	FORCEINLINE bool DidHitNonWorldEntity() const;
	/*
	* Get index of hit entity.
	*/
	FORCEINLINE int GetEntityIndex() const;

	/*
	* Did we hit any entities?
	*/
	FORCEINLINE bool DidHit() const;

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
	CBaseEntity*	m_pEnt;
	// Studio hitbox we hit with our ray
	int				m_nHitbox;
};