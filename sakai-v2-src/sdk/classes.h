#pragma once
// Include IClientEntity
#include "interfaces/cliententity.h"
// Include CUserCmd
#include "interfaces/prediction.h"
// Include netvar macros
#include "platform.h"
// Include AnimLayer_t, ELifeState
#include "structs.h"

class CIkContext;
class CAnimState;

class CBaseEntity : public IClientEntity
{
public:
	// Prediction datamap
	CALL_VIRTUAL(17U,	GetPredDatamap(),		CDatamap* (__thiscall*)(void*));
	CALL_VIRTUAL(157U,	IsPlayer(),				bool(__thiscall*)(void*));
	CALL_VIRTUAL(161U,	IsNPC(),				bool(__thiscall*)(void*));
	CALL_VIRTUAL(162U,	IsSprite(),				bool(__thiscall*)(void*));
	CALL_VIRTUAL(163U,	IsProp(),				bool(__thiscall*)(void*));
	CALL_VIRTUAL(165U,	IsWeapon(),				bool(__thiscall*)(void*));

	CALL_SIG(SetAbsAngles(const QAngle& Angles),
		"client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1",
		void(__thiscall*)(void*, const QAngle&), Angles);

	CALL_SIG(SetAbsOrigin(const CVector3& Origin),
		"client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8 ? ? ? ? 8B 7D",
		void(__thiscall*)(void*, const CVector3&), Origin);

	CALL_SIG(IsBreakableProp(),
		"client.dll", "55 8B EC 51 56 8B F1 85 F6 74 68 83 BE",
		bool(__thiscall*)(void*));

	NETVAR_FLD(GetSimTime(),		float,	"DT_BaseEntity->m_flSimulationTime");
	NETVAR_FLD(GetOldSimTime(),		float,	"DT_BaseEntity->m_flSimulationTime", + 0x4);
	NETVAR_FLD(GetAnimTime(),		float,	"DT_BaseEntity->m_flAnimTime");
	NETVAR_FLD(GetOldAnimTime(),	float,	"DT_BaseEntity->m_flAnimTime", + 0x4);

	NETVAR_FLD(GetEffects(),		int,	"DT_BaseEntity->m_fEffects");
	NETVAR_FLD(GetRenderMode(),		int,	"DT_BaseEntity->m_nRenderMode");
	NETVAR_FLD(GetRenderFX(),		int,	"DT_BaseEntity->m_nRenderFX");
	NETVAR_FLD(GetElasticity(),		float,	"DT_BaseEntity->m_flElasticity");

	OFFSET_FLD(GetTeamNumber(),		int,	0xF4);
	OFFSET_FLD(GetLifeState(),		int,	0x25F);
	OFFSET_FLD(IsSpotted(),			bool,	0x93D);
	NETVAR_FLD(GetLastNoiseTime(),  float,	"DT_BaseEntity->m_flLastMadeNoiseTime");

	FORCEINLINE bool IsAlive() { return this->GetLifeState() == LIFE_ALIVE; }

	OFFSET_FLD(GetCollisionGroup(), int,	0x474);
	OFFSET_FLD(GetOwnerEntity(),	CBaseHandle, 0x14C);
	OFFSET_FLD(GetMoveType(),		int,	0x25C);
	NETVAR_FLD(GetEffectEntity(),	CBaseHandle, "DT_BaseEntity->m_hEffectEntity");
	NETVAR_FLD(GetMoveParent(),		int,	"DT_BaseEntity->moveparent");

	DATAMAP_FLD(GetAbsRotation(),	QAngle, "m_angAbsRotation",	*GetPredDatamap());
	DATAMAP_FLD(GetEFlags(),		int,	"m_iEFlags",		*GetPredDatamap());
	DATAMAP_FLD(GetFriction(),		float,	"m_flFriction",		*GetPredDatamap());
	OFFSET_FLD(GetFlags(),			int,	0x104);

	OFFSET_FLD(GetCoordinateFrame(), CMatrix3x4, 0x444);
	OFFSET_FLD(GetOrigin(),			CVector3, 0x138);
	OFFSET_FLD(GetVelocity(),		CVector3, 0x114);

	FORCEINLINE bool IsBreakable()
	{
		if (!this)
			return false;

		auto ClassID = this->GetClientClass()->m_nClassID;
		if (!static_cast<int>(ClassID))
			return false;

		if (ClassID == EClassID::CBreakableSurface
			|| ClassID == EClassID::CBaseDoor
			|| ClassID == EClassID::CFuncBrush)
			return true;

		return false;
	}
};

class CBaseAnimating : public CBaseEntity
{
public:
	OFFSET_FLD(GetStudioHdr(),		CStudioHdr*,	0x2950);
	OFFSET_FLD(GetSetupBonesPos(),	CVector3,		0xA6C);
	OFFSET_FLD(GetSetupBonesQuaternion(), CVector4, 0x1670);
	OFFSET_FLD(GetForceBone(),		int,			0x268C);
	P_OFFSET_FLD(GetBoneCache(),	BoneCache_t,	0x2914);
	PP_OFFSET_FLD(GetAnimLayers(),	AnimLayer_t,	0x2990);
	NETVAR_FLD(GetBoneAccessor(),	BoneAccessor_t, "DT_BaseAnimating->m_nBody", +0x8);
	P_NETVAR_FLD(GetPoseParameters(), float,		"DT_BaseAnimating->m_flPlaybackRate");

	OFFSET_FLD(GetLastSetupBonesFrameCount(), int,	0xA68);
	OFFSET_FLD(GetLastBoneSetupTime(), float,		0x2928);
	OFFSET_FLD(GetRecentMdlBoneCounter(), unsigned long, 0x2690);
	OFFSET_FLD(GetAccumBoneMask(),	int,			0x26A0);
	OFFSET_FLD(GetPrevBoneMask(),	int,			0x269C);

	OFFSET_FLD(GetIkContext(),		CIkContext*,	0x2670);
	
	NETVAR_FLD(GetFrozen(),			float,			"DT_BaseAnimating->m_flFrozen");
	NETVAR_FLD(GetPlaybackRate(),	float,			"DT_BaseAnimating->m_flPlaybackRate");
	NETVAR_FLD(GetSequence(),		int,			"DT_BaseAnimating->m_nSequence");

	NETVAR_FLD(GetHitboxSet(),		int,			"DT_BaseAnimating->m_nHitboxSet");
	NETVAR_FLD(GetModelScale(),		float,			"DT_BaseAnimating->m_flModelScale");
	NETVAR_FLD(GetAnimLODFlags(),	int,			"DT_BaseAnimating->m_nBody", + 0x8);
};

class CBaseFlex : public CBaseAnimating
{
public:
	P_NETVAR_FLD(GetFlexWeights(),	float,	"DT_BaseFlex->m_flexWeight");
	NETVAR_FLD(GetBlinkToggle(),	int,	"DT_BaseFlex->m_blinktoggle");
};

class CBaseCombatCharacter : public CBaseFlex
{
public:
	DATAMAP_FLD(GetNextAttack(),	float,	"m_flNextAttack",	*GetPredDatamap());
	DATAMAP_FLD(GetActiveWeapon(),	CBaseHandle, "m_hActiveWeapon",	*GetPredDatamap());
	
	NETVAR_FLD(GetLastHitgroup(),	int,	"DT_BaseCombatCharacter->m_LastHitGroup");
	NETVAR_FLD(GetTimeLastHurt(),	float,	"DT_BaseCombatCharacter->m_flTimeOfLastInjury");
	NETVAR_FLD(GetBloodColor(),		int,	"DT_BaseCombatCharacter->m_nRelativeDirectionOfLastInjury", + 0x4);
	P_NETVAR_FLD(GetWeapons(),		CBaseHandle, "DT_BaseCombatCharacter->m_hMyWeapons");
};

class CBasePlayer : public CBaseCombatCharacter
{
public:
	CALL_VIRTUAL(373U,	SetLocalViewAngles(const QAngle& Angles),	void(__thiscall*)(void*, const QAngle&),	Angles);

	CALL_SIG(PhysicsRunThink(int Index),
		"client.dll", "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87",
		bool(__thiscall*)(void*, int), Index);

	CALL_SIG(PhysicsPostThink(),
		"client.dll", "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 8B D9 56 57 83 BB",
		bool(__thiscall*)(void*));

	CALL_SIG(SimulateSimulatedEntities(),
		"client.dll", "56 8B F1 57 8B BE ? ? ? ? 83 EF 01 78 72",
		bool(__thiscall*)(void*));

	DATAMAP_FLD(GetGroundEntity(),	CBaseHandle,	"m_hGroundEntity",		*GetPredDatamap());
	NETVAR_FLD(GetVehichle(),		CBaseHandle,	"DT_BasePlayer->m_hVehicle");
	NETVAR_FLD(GetViewModel(),		CBaseHandle,	"DT_BasePlayer->m_hViewModel[0]");
	NETVAR_FLD(GetObserverTarget(), CBaseHandle,	"DT_BasePlayer->m_hObserverTarget");
	NETVAR_FLD(GetTonemapController(), CBaseHandle,	"DT_BasePlayer->m_hTonemapController");

	NETVAR_FLD(GetViewPunchAngle(), QAngle,			"DT_BasePlayer->m_viewPunchAngle");
	NETVAR_FLD(GetAimPunchAngle(),	QAngle,			"DT_BasePlayer->m_aimPunchAngle");
	NETVAR_FLD(GetAimPunchAngleVel(), CVector3,		"DT_BasePlayer->m_aimPunchAngleVel");
	NETVAR_FLD(GetViewOffset(),		CVector3,		"DT_BasePlayer->m_vecViewOffset[0]");

	OFFSET_FLD(GetFov(),			float,			0x31F4);
	OFFSET_FLD(GetDefaultFov(),		float,			0x333C);
	OFFSET_FLD(GetFovStart(),		float,			0x31F8);

	DATAMAP_FLD(GetCollisionState(), int,			"m_vphysicsCollisionState",	*GetPredDatamap());
	OFFSET_FLD(GetSpawnTime(),		float,			0x103C0);
	OFFSET_FLD(GetHealth(),			int,			0x100);
	NETVAR_FLD(GetFallVelocity(),	float,			"DT_BasePlayer->m_flFallVelocity");
	NETVAR_FLD(GetObserverMode(),	int,			"DT_BasePlayer->m_iObserverMode");
	NETVAR_FLD(GetWaterLevel(),		int,			"DT_BasePlayer->m_nWaterLevel");

	DATAMAP_FLD(GetImpulse(),		int,			"m_nImpulse",			*GetPredDatamap());
	DATAMAP_FLD(GetDuckAmount(),	float,			"m_flDuckAmount",		*GetPredDatamap());
	DATAMAP_FLD(GetButtons(),		std::uint32_t,	"m_nButtons",			*GetPredDatamap());
	DATAMAP_FLD(GetLastButtons(),	std::uint32_t,	"m_afButtonLast",		*GetPredDatamap());
	DATAMAP_FLD(GetPressedButtons(), std::uint32_t,	"m_afButtonPressed",	*GetPredDatamap());
	DATAMAP_FLD(GetReleasedButtons(), std::uint32_t, "m_afButtonReleased",	*GetPredDatamap());
	OFFSET_FLD(GetDisabledButtons(), std::uint32_t,	0x3330);
	OFFSET_FLD(GetForcedButtons(),	std::uint32_t,	0x3334);
	OFFSET_FLD(GetLastCmd(),		CUserCmd,		0x3298);
	NETVAR_FLD(GetCurCmd(),			CUserCmd*,		"DT_BasePlayer->m_hConstraintEntity", -0xC);
	NETVAR_FLD(GetDuckSpeed(),		float,			"DT_BasePlayer->m_flDuckSpeed");
	NETVAR_FLD(GetNextThinkTick(),	int,			"DT_BasePlayer->m_nNextThinkTick");
	NETVAR_FLD(GetTickBase(),		int,			"DT_BasePlayer->m_nTickBase");
};

// @Credits: https://github.com/lagcomp/wok-csgo-sdk-v2/blob/master/wok-csgo/sdk/_classes.h#L323
class CCSPlayer : public CBaseCombatCharacter
{
public:
	CALL_VIRTUAL(224U, UpdateClientSideAnimation(), void(__thiscall*)(void*));

	CALL_SIG(InvalidatePhysRecursive(int Bits),
		"client.dll", "55 8B EC 83 E4 F8 83 EC 0C 53 8B 5D 08 8B C3 56",
		void(__thiscall*)(void*, int), Bits);

	NETVAR_FLD(GetVelocityModifier(), float,		"DT_CSPlayer->m_flVelocityModifier");
	NETVAR_FLD(HasDefuser(),		bool,			"DT_CSPlayer->m_bHasDefuser");
	NETVAR_FLD(HasHelmet(),			bool,			"DT_CSPlayer->m_bHasHelmet");
	NETVAR_FLD(GetArmorValue(),		int,			"DT_CSPlayer->m_ArmorValue");
	NETVAR_FLD(HasHeavyArmor(),		bool,			"DT_CSPlayer->m_bHasHeavyArmor");
	NETVAR_FLD(GetEyeAngles(),		QAngle,			"DT_CSPlayer->m_angEyeAngles");
	NETVAR_FLD(IsScoped(),			bool,			"DT_CSPlayer->m_bIsScoped");
	NETVAR_FLD(HasImmunity(),		bool,			"DT_CSPlayer->m_bGunGameImmunity");
	NETVAR_FLD(IsGhost(),			bool,			"DT_CSPlayer->m_bIsPlayerGhost");
	NETVAR_FLD(GetHealthBoostTime(), float,			"DT_CSPlayer->m_flHealthShotBoostExpirationTime");
	NETVAR_FLD(GetLby(),			float,			"DT_CSPlayer->m_flLowerBodyYawTarget");
	NETVAR_FLD(GetFlashAlpha(),		float,			"DT_CSPlayer->m_flFlashMaxAlpha", -0x8);
	NETVAR_FLD(GetAnimState(),		CAnimState*,	"DT_CSPlayer->m_bIsScoped", -0x14);

	FORCEINLINE bool IsEnemy(CCSPlayer* To) const { return GetTeamNumber() != To->GetTeamNumber(); }
};

class CPlantedC4 : public CBaseEntity
{
	NETVAR_FLD(IsTicking(),			bool,		"DT_PlantedC4->m_bBombTicking");
	NETVAR_FLD(IsDefused(),			bool,		"DT_PlantedC4->m_bBombDefused");
	NETVAR_FLD(GetDefuser(),		CBaseHandle, "DT_PlantedC4->m_hBombDefuser");

	NETVAR_FLD(GetBombSite(),		int,		"DT_PlantedC4->m_nBombSite");

	NETVAR_FLD(GetBlowTime(),		float,		"DT_PlantedC4->m_flC4Blow");
	NETVAR_FLD(GetTimerLength(),	float,		"DT_PlantedC4->m_flTimerLength");
	NETVAR_FLD(GetDefuseLength(),	float,		"DT_PlantedC4->m_flDefuseLength");
	NETVAR_FLD(GetDefuseCountdown(), float,		"DT_PlantedC4->m_flDefuseCountDown");
};

class CInferno : public CBaseEntity
{
public:
	ARR_NETVAR_FLD(get_fire_x_delta(),	int,	64U,	"DT_Inferno->m_fireXDelta");
	ARR_NETVAR_FLD(get_fire_y_delta(),	int,	64U,	"DT_Inferno->m_fireYDelta");
	ARR_NETVAR_FLD(get_fire_z_delta(),	int,	64U,	"DT_Inferno->m_fireZDelta");
};

class CSmokeGrenadeProjectile : public CBaseEntity
{
public:
	NETVAR_FLD(DidSmokeEffect(),	bool,	"DT_SmokeGrenadeProjectile->m_bDidSmokeEffect");
};

class CEconItem : public CBaseEntity
{
public:
	NETVAR_FLD(GetOriginalOwnerXuidLow(),	std::uint32_t,	"DT_EconEntity->m_OriginalOwnerXuidLow");
	NETVAR_FLD(GetOriginalOwnerXuidHigh(),	std::uint32_t,	"DT_EconEntity->m_OriginalOwnerXuidHigh");
	NETVAR_FLD(GetFallbackPaintKit(),		std::uint32_t,	"DT_EconEntity->m_nFallbackPaintKit");
	NETVAR_FLD(GetFallbackSeed(),			std::uint32_t,	"DT_EconEntity->m_nFallbackSeed");
	NETVAR_FLD(GetFallbackWear(),			float,			"DT_EconEntity->m_flFallbackWear");
	NETVAR_FLD(GetFallbackStatTrack(),		int,			"DT_EconEntity->m_nFallbackStatTrak");
};