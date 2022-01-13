#pragma once
// Include stdlib
#include "../platform.h"
// Includ CVector3
#include "vector.h"

struct StudioHdr_t;
struct StudioEvent_t;
struct StudioIkLock_t;
struct StudioAnimTag_t;
struct StudioAutoLayer_t;
struct StudioActivityModifier_t;
class CStudioHdr;

struct StudioSeqDesc_t
{
	int					m_iStudioOffset;
	int					m_iLabelOffset;
	int					m_iActivityNameOffset;
	int					m_iFlags;
	int					m_iActivity;
	int					m_iActivityWeight;
	int					m_nEvents;
	int					m_iEventIndex;
	CVector3			m_vecMins;
	CVector3			m_vecMaxs;
	int					m_nBlends;
	int					m_iAnimIndex;
	int					m_iMovementIndex;
	int					m_iGroupSize[2];
	int					m_iParamIndex[2];
	float				m_flParamStart[2];
	float				m_flParamEnd[2];
	int					m_iParamParent;
	float				m_flFadeinTime;
	float				m_flFadeoutTime;
	int					m_iLocalEntryNode;
	int					m_iLocalExitNode;
	int					m_iNodeFlags;
	float				m_flEntryPhase;
	float				m_flExitPhase;
	float				m_flLastFrame;
	int					m_iNextSequence;
	int					m_iPose;
	int					m_nIkRules;
	int					m_nAutoLayers;
	int					m_iAutoLayerIndex;
	int					m_iWeightListIndex;
	int					m_iPoseKeyIndex;
	int					m_nIkLocks;
	int					m_iIkLockIndex;
	int					m_iKeyValueIndex;
	int					m_iKeyValueSize;
	int					m_iCyclePoseIndex;
	int					m_iActModifierIndex;
	int					m_nActModifiers;
	int					m_iAnimTagIndex;
	int					m_nAnimTags;
	int					rootDriverIndex;
	int					_0[2];

	FORCEINLINE StudioHdr_t*	GetStudioHdr() { return reinterpret_cast<StudioHdr_t*>(reinterpret_cast<std::byte*>(this) + m_iStudioOffset); }
	FORCEINLINE char*			GetLabel() { return reinterpret_cast<char* const>(reinterpret_cast<std::byte*>(this) + m_iLabelOffset); }
	FORCEINLINE char*			GetActivityName() { return reinterpret_cast<char* const>(reinterpret_cast<std::byte*>(this) + m_iLabelOffset); }
	FORCEINLINE StudioEvent_t*	GetEvent(int Index) { return reinterpret_cast<StudioEvent_t*>(reinterpret_cast<std::byte*>(this) + m_iEventIndex + Index); }
	FORCEINLINE StudioAutoLayer_t* GetAutoLayer(int Index) { return reinterpret_cast<StudioAutoLayer_t*>(reinterpret_cast<std::byte*>(this) + m_iAutoLayerIndex + Index); }
	FORCEINLINE float*			GetBoneWeights(int Index) { return reinterpret_cast<float*>(reinterpret_cast<std::byte*>(this) + m_iWeightListIndex + Index); }
	FORCEINLINE float			GetWeight(int Index) { return *GetBoneWeights(Index); }
	FORCEINLINE StudioIkLock_t* GetIkLock(int Index) { return reinterpret_cast<StudioIkLock_t*>(reinterpret_cast<std::byte*>(this) + m_iIkLockIndex + Index); }
	FORCEINLINE const char*		KeyValueText() { return m_iKeyValueSize != 0 ? reinterpret_cast<char*>(this) + m_iKeyValueIndex : NULL; }
	FORCEINLINE StudioActivityModifier_t* GetActModifier(int Index) { return m_iActModifierIndex != 0 ? reinterpret_cast<StudioActivityModifier_t*>(reinterpret_cast<std::byte*>(this) + m_iActModifierIndex + Index) : NULL; }
	FORCEINLINE StudioAnimTag_t* GetAnimTag(int Index) { return reinterpret_cast<StudioAnimTag_t*>(reinterpret_cast<std::byte*>(this) + m_iAnimTagIndex + Index); }
};

