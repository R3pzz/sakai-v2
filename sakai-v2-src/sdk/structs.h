#pragma once
// Include StudioSeqDesc_t
#include "types/studio.h"

#define MAXSTUDIOTRIANGLES	65536
#define MAXSTUDIOVERTS		65536
#define	MAXSTUDIOFLEXVERTS	10000
#define MAXSTUDIOSKINS		32
#define MAXSTUDIOBONES		256
#define MAXSTUDIOFLEXDESC	1024
#define MAXSTUDIOFLEXCTRL	96
#define MAXSTUDIOPOSEPARAM	24
#define MAXSTUDIOBONECTRLS	4
#define MAXSTUDIOANIMBLOCKS 256

#define MAXSTUDIOBONEBITS	8

#define MODELFLAG_MATERIALPROXY					0x0001
#define MODELFLAG_TRANSLUCENT					0x0002
#define MODELFLAG_VERTEXLIT						0x0004
#define MODELFLAG_TRANSLUCENT_TWOPASS			0x0008
#define MODELFLAG_FRAMEBUFFER_TEXTURE			0x0010
#define MODELFLAG_HAS_DLIGHT					0x0020
#define MODELFLAG_VIEW_WEAPON_MODEL				0x0040
#define MODELFLAG_RENDER_DISABLED				0x0080
#define MODELFLAG_STUDIOHDR_USES_FB_TEXTURE		0x0100
#define MODELFLAG_STUDIOHDR_USES_BUMPMAPPING	0x0200
#define MODELFLAG_STUDIOHDR_USES_ENV_CUBEMAP	0x0400
#define MODELFLAG_STUDIOHDR_AMBIENT_BOOST		0x0800
#define MODELFLAG_STUDIOHDR_DO_NOT_CAST_SHADOWS	0x1000
#define MODELFLAG_STUDIOHDR_IS_STATIC_PROP		0x2000
#define MODELFLAG_STUDIOHDR_BAKED_VERTEX_LIGHTING_IS_INDIRECT_ONLY	0x4000

class CKeyValues;
class CBaseAnimating;
class IClientRenderable;
struct StudioHdr_t;
struct StudioHWData_t;

class CIkContext
{
public:
	CALL_SIG(Create(),
		"client.dll", "53 8B D9 F6 C3 03 74 0B FF 15 ?? ?? ?? ?? 84 C0 74 01 CC C7 83 ?? ?? ?? ?? ?? ?? ?? ?? 8B CB",
		void(__thiscall*)(void*));

	CALL_SIG(Term(),
		"client.dll", "56 8B F1 57 8D 8E ?? ?? ?? ?? E8 ?? ?? ?? ?? 8D 8E ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 BE ?? ?? ?? ?? ??",
		void(__thiscall*)(void*));

	CALL_SIG(Init(CStudioHdr* Studio, QAngle& Angles, CVector3& Origin, float Time, int Framecount, int Mask),
		"client.dll", "55 8B EC 83 EC ? 8B 45 ? 56 57 8B F9 8D 8F ? ? ? ?",
		void(__thiscall*)(void*, CStudioHdr*, QAngle&, CVector3&, float, int, int),
		Studio, Angles, Origin, Time, Framecount, Mask);

	CALL_SIG(AddDependencies(StudioSeqDesc_t& SeqDesc, int Sequence, float Cycle, float* PoseParamsArr, float Weight), "client.dll",
		"55 8B EC 81 EC ? ? ? ? 53 56 57 8B F9 0F 28 CB F3 0F 11 4D ? 8B 8F ? ? ? ? 8B 01",
		void(__thiscall*)(void*, StudioSeqDesc_t&, int, float, float*, float), SeqDesc, Sequence, Cycle, PoseParamsArr, Weight);

	CALL_SIG(UpdateTargets(CVector3* Pos, CVector4* Quat, CMatrix3x4* BonesArr, std::uint8_t* Out),
		"client.dll", "55 8B EC 83 E4 ? 81 EC ? ? ? ? 33 D2",
		void(__thiscall*)(void*, CVector3*, CVector4*, CMatrix3x4*, std::uint8_t*), Pos, Quat, BonesArr, Out);

	CALL_SIG(SolveDependencies(CVector3* Pos, CVector4* Quat, CMatrix3x4* BonesArr, std::uint8_t* Out),
		"client.dll", "55 8B EC 83 E4 ? 81 EC ? ? ? ? 8B 81 ? ? ? ? 56",
		void(__thiscall*)(void*, CVector3*, CVector4*, CMatrix3x4*, uint8_t*), Pos, Quat, BonesArr, Out);
	
	FORCEINLINE void ClearTargets()
	{
		auto Target = reinterpret_cast<int*>(reinterpret_cast<std::uintptr_t>(this) + 0xD0);

		for (auto i = 0; i < *reinterpret_cast<int*>(reinterpret_cast<std::uintptr_t>(this) + 0xFF0); i++)
		{
			*Target = -9999;
			Target += 85;
		}
	}
};

struct AnimLayer_t
{
	float			m_flAnimationTime;
	float			m_flFadeOut;
	CStudioHdr*		m_pStudioHdr;
	int				m_nDispatchedSrc;
	int				m_nDispatchedDst;
	int				m_iOrder;
	int				m_nSequence;
	float			m_flPrevCycle;
	float			m_flWeight;
	float			m_flWeightDeltaRate;
	float			m_flPlaybackRate;
	float			m_flCycle;
	CBaseAnimating* m_pOwner;
	int				m_nInvalidatePhysicsBits;
};

struct DrawModelState_t
{
	StudioHdr_t*	m_pStudioHdr;
	StudioHWData_t* m_pStudioHWData;
	IClientRenderable* m_pRenderable;
	const CMatrix3x4* m_pModelToWorld;
	std::uintptr_t*	m_pDecals;
	int				m_iDrawFlags;
	int				m_iLod;
};

struct Model_t
{
	void*			m_pHandle;
	char			m_szPathName[MAX_OSPATH];
	int				m_nLoadFlags;
	int				m_nServerCount;
	int				m_iType;
	int				m_iFlags;
	CVector3		m_vecMins;
	CVector3		m_vecMaxs;
	float			m_flRadius;
	CKeyValues*		m_pKeyValues;
};

struct ModelRenderInfo_t
{
	CVector3			m_vecOrigin;
	QAngle				m_angAngles;
	IClientRenderable*	m_pRenderable;
	const Model_t*		m_pModel;
	const CMatrix3x4*	m_pModelToWorld;
	const CMatrix3x4*	m_pLightingOffset;
	const CVector3*		m_pLightingOrigin;
	int					m_iFlags;
	int					m_iEntityIndex;
	int 				m_iSkin;
	int 				m_iBody;
	int 				m_iHitboxSet;
	std::uintptr_t*		m_pInstance;
};

struct BoneCache_t
{
	CMatrix3x4*		m_pCachedBones;
	pad_t			_0[8];
	uint32_t		m_iBonesCount;
};

struct BoneAccessor_t
{
	pad_t			_0[4];
	CMatrix3x4*		m_pBones;
	int				m_iReadableBones;
	int				m_iWritableBones;
};

enum ELifeState : int
{
	LIFE_ALIVE = 0,
	LIFE_DYING = 1,
	LIFE_DEAD = 2,
	LIFE_RESPAWNABLE = 3,
	LIFE_DISCARDBODY = 4,
};

enum EBloodColor : int
{
	DONT_BLEED = -1,
	BLOOD_COLOR_RED = 0,
	BLOOD_COLOR_YELLOW,
	BLOOD_COLOR_GREEN,
	BLOOD_COLOR_MECH,
	BLOOD_COLOR_BRIGHTGREEN,
};

enum EEflags : int
{
	EFL_KILLME = (1 << 0),
	EFL_DORMANT = (1 << 1),
	EFL_NOCLIP_ACTIVE = (1 << 2),
	EFL_SETTING_UP_BONES = (1 << 3),
	EFL_KEEP_ON_RECREATE_ENTITIES = (1 << 4),
	EFL_DIRTY_SHADOWUPDATE = (1 << 5),
	EFL_NOTIFY = (1 << 6),
	EFL_FORCE_CHECK_TRANSMIT = (1 << 7),
	EFL_BOT_FROZEN = (1 << 8),
	EFL_SERVER_ONLY = (1 << 9),
	EFL_NO_AUTO_EDICT_ATTACH = (1 << 10),
	EFL_DIRTY_ABSTRANSFORM = (1 << 11),
	EFL_DIRTY_ABSVELOCITY = (1 << 12),
	EFL_DIRTY_ABSANGVELOCITY = (1 << 13),
	EFL_DIRTY_SURROUNDING_COLLISION_BOUNDS = (1 << 14),
	EFL_DIRTY_SPATIAL_PARTITION = (1 << 15),
	EFL_HAS_PLAYER_CHILD = (1 << 16),
	EFL_IN_SKYBOX = (1 << 17),
	EFL_USE_PARTITION_WHEN_NOT_SOLID = (1 << 18),
	EFL_TOUCHING_FLUID = (1 << 19),
	EFL_IS_BEING_LIFTED_BY_BARNACLE = (1 << 20),
	EFL_NO_ROTORWASH_PUSH = (1 << 21),
	EFL_NO_THINK_FUNCTION = (1 << 22),
	EFL_NO_GAME_PHYSICS_SIMULATION = (1 << 23),
	EFL_CHECK_UNTOUCH = (1 << 24),
	EFL_DONTBLOCKLOS = (1 << 25),
	EFL_DONTWALKON = (1 << 26),
	EFL_NO_DISSOLVE = (1 << 27),
	EFL_NO_MEGAPHYSCANNON_RAGDOLL = (1 << 28),
	EFL_NO_WATER_VELOCITY_CHANGE = (1 << 29),
	EFL_NO_PHYSCANNON_INTERACTION = (1 << 30),
	EFL_NO_DAMAGE_FORCES = (1 << 31),
};

enum EInvalidatePhysBits : int
{
	POSITION_CHANGED = 0x1,
	ANGLES_CHANGED = 0x2,
	VELOCITY_CHANGED = 0x4,
	ANIMATION_CHANGED = 0x8,
	BOUNDS_CHANGED = 0x10,
	SEQUENCE_CHANGED = 0x20,																
};

enum EMaterialVarFlags : int
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_PSEUDO_TRANSLUCENT = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_AOPREPASS = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_MULTIPLY = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
	MATERIAL_VAR_VERTEXFOG = (1 << 31),
};