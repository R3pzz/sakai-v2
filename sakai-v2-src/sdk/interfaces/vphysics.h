#pragma once
// Include stdlib
#include "../platform.h"

struct SurfacePhysParams_t
{
	float			m_flFriction;
	float			m_flElasticity;
	float			m_flDensity;
	float			m_flThickness;
	float			m_flDampening;
};

struct SurfaceAudioParams_t
{
	float			m_flReflectivity;
	float			m_flHardnessFactor;
	float			m_flRoughnessFactor;
	float			m_flRoughThreshold;
	float			m_flHardThreshold;
	float			m_flHardVelocityThreshold;
};

struct SurfaceSoundNames_t
{
	std::uint16_t	m_uWalkStepLeft;
	std::uint16_t	m_uWalkStepRight;
	std::uint16_t	m_uRunStepLeft;
	std::uint16_t	m_uRunStepRight;
	std::uint16_t	m_uImpactSoft;
	std::uint16_t	m_uImpactHard;
	std::uint16_t	m_uScrapeSmooth;
	std::uint16_t	m_uScrapeRough;
	std::uint16_t	m_uBulletImpact;
	std::uint16_t	m_uRolling;
	std::uint16_t	m_uBreakSound;
	std::uint16_t	m_uStrainSound;
};

struct SurfaceSoundHandles_t
{
	std::uint32_t	m_iWalkStepLeft;
	std::uint32_t	m_iWalkStepRight;
	std::uint32_t	m_iRunStepLeft;
	std::uint32_t	m_iRunStepRight;
	std::uint32_t	m_iImpactSoft;
	std::uint32_t	m_iImpactHard;
	std::uint32_t	m_iScrapeSmooth;
	std::uint32_t	m_iScrapeRough;
	std::uint32_t	m_iBulletImpact;
	std::uint32_t	m_iRolling;
	std::uint32_t	m_iBreakSound;
	std::uint32_t	m_iStrainSound;
};

struct SurfaceGameProps_t
{
	float			m_flMaxSpeedFactor;
	float			m_flJumpFactor;
	float			m_flPenetrationModifier;
	float			m_flDamageModifier;
	std::uint16_t	m_uMaterial;
	std::uint8_t	m_uClimbable;
	pad_t			_0[1];
};

struct SurfaceData_t
{
	SurfacePhysParams_t		m_Physics;
	SurfaceAudioParams_t	m_Audio;
	SurfaceSoundNames_t		m_Sounds;
	SurfaceGameProps_t		m_Game;
	SurfaceSoundHandles_t	m_SoundHandles;
};

class IPhysicsSurfaceProps
{
public:
	// VMT alignment
	virtual void _0() { }

	virtual int				ParseSurfaceData(const char* File, const char* TextFile) = 0;
	virtual int				SurfacePropCount() const = 0;
	virtual int				GetSurfaceIndex(const char* PropName) const = 0;
	virtual void			GetPhysicsProperties(int SurfaceDataIndex, float* Density, float* Thickness, float* Friction, float* Elasticity) const = 0;
	virtual SurfaceData_t*	GetSurfaceData(int SurfaceDataIndex) = 0;
	virtual const char*		GetString(std::uint16_t StringTableIndex) const = 0;
	virtual const char*		GetPropName(int SurfaceDataIndex) const = 0;
	virtual void			SetWorldMaterialIndexTable(int* MapArr, int MapSize) = 0;
	virtual void			GetPhysicsParameters(int SurfaceDataIndex, SurfacePhysParams_t* ParamsOut) const = 0;
	virtual void*			GetMaterialIndexDataOps() const = 0;
};