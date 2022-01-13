#pragma once
// Include ihandleentity
#include "../types/handle.h"
// Include client class defs
#include "../types/clientclass.h"

class IClientNetworkable;
class CBaseEntity;
class IClientRenderable;
class ICollideable;
class IClientEntity;
class IClientThinkable;
class IClientModelRenderable;
class IClientAlphaProperty;
class IClientUnknown;
class CMatrix3x4;
class CMatrix3x4a;
class CVector3;
class QAngle;
struct CMouthInfo;
struct Model_t;
class BfRead_t;

namespace U
{
	/*
	* 'Magic' number with which you can obtain shadow
	*	stuff.
	*/
	using ShadowHandle_t = std::uint16_t;

	/*
	* Some other model handles.
	*/
	using ModelHandle_t = std::uint16_t;
	using RenderHandle_t = std::uint16_t;

	/*
	* Think handle
	*/
	using ThinkHandle_t = std::uintptr_t*;
}

enum EShadowType : std::uint_fast8_t
{
	SHADOWS_NONE = 0,
	SHADOWS_SIMPLE,
	SHADOWS_RENDER_TO_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC,
	SHADOWS_RENDER_TO_DEPTH_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC_CUSTOM,
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable *		GetCollideable() = 0;
	virtual IClientNetworkable* GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual IClientEntity*		GetIClientEntity() = 0;
	virtual CBaseEntity*		GetBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
	virtual IClientAlphaProperty* GetClientAlphaProperty() = 0;
};

class IClientRenderable
{
public:
	virtual IClientUnknown *	GetIClientUnknown() = 0;
	virtual CVector3 const&		GetRenderOrigin() = 0;
	virtual QAngle const&		GetRenderAngles() = 0;
	virtual bool				ShouldDraw() = 0;
	virtual int					GetRenderFlags() = 0;
	virtual void				_0() {}
	virtual U::ShadowHandle_t	GetShadowHandle() const = 0;
	virtual U::RenderHandle_t&	RenderHandle() = 0;
	virtual const Model_t*		GetModel() const = 0;
	virtual int					DrawModel(int flags, const std::uint8_t& alpha) = 0;
	virtual int					GetBody() = 0;
	virtual void				GetColorModulation(float* color) = 0;
	virtual bool				LODTest() = 0;
	virtual bool				SetupBones(CMatrix3x4a* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void				SetupWeights(const CMatrix3x4* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void				DoAnimationEvents() = 0;
	virtual void*				GetPVSNotifyInterface() = 0;
	virtual void				GetRenderBounds(CVector3& mins, CVector3& maxs) = 0;
	virtual void				GetRenderBoundsWorldspace(CVector3& mins, CVector3& maxs) = 0;
	virtual void				GetShadowRenderBounds(CVector3& mins, CVector3& maxs, EShadowType shadowType) = 0;
	virtual bool				ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool				GetShadowCastDistance(float* pDist, EShadowType shadowType) const = 0;
	virtual bool				GetShadowCastDirection(CVector3* pDirection, EShadowType shadowType) const = 0;
	virtual bool				IsShadowDirty() = 0;
	virtual void				MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*	GetShadowParent() = 0;
	virtual IClientRenderable*	FirstShadowChild() = 0;
	virtual IClientRenderable*	NextShadowPeer() = 0;
	virtual EShadowType			GetShadowCastType() = 0;
	virtual void				_1() {}
	virtual void				CreateModelInstance() = 0;
	virtual U::ModelHandle_t	GetModelInstance() = 0;
	virtual const CMatrix3x4&	RenderableToWorldTransform() = 0;
	virtual int 				LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool 				GetAttachment(int number, CVector3& origin, QAngle& angles) = 0;
	virtual bool  				GetAttachment(int number, CMatrix3x4& matrix) = 0;
	virtual bool  				ComputeLightingOrigin(int nAttachmentIndex, CVector3 modelLightingCenter, const CMatrix3x4& matrix, CVector3& transformedLightingCenter) = 0;
	virtual float*				GetRenderClipPlane() = 0;
	virtual int					GetSkin() = 0;
	virtual void				OnThreadedDrawSetup() = 0;
	virtual bool				UsesFlexDelayedWeights() = 0;
	virtual void				RecordToolMessage() = 0;
	virtual bool				ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual std::uint8_t		OverrideAlphaModulation(std::uint8_t nAlpha) = 0;
	virtual std::uint8_t		OverrideShadowAlphaModulation(std::uint8_t nAlpha) = 0;
	virtual IClientModelRenderable* GetClientModelRenderable() = 0;
};

class IClientNetworkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				Release() = 0;
	virtual CClientClass*		GetClientClass() = 0;
	virtual void				NotifyShouldTransmit(int state) = 0;
	virtual void				OnPreDataChanged(int updateType) = 0;
	virtual void				OnDataChanged(int updateType) = 0;
	virtual void				PreDataUpdate(int updateType) = 0;
	virtual void				PostDataUpdate(int updateType) = 0;
	virtual void				OnDataUnchangedInPVS() = 0;
	virtual bool				IsDormant() const = 0;
	virtual int					GetIndex() const = 0;
	virtual void				ReceiveMessage(int classID, BfRead_t& msg) = 0;
	virtual void*				GetDataTableBasePtr() = 0;
	virtual void				SetDestroyedOnRecreateEntities() = 0;
};

class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual U::ThinkHandle_t	GetThinkHandle() = 0;
	virtual void				SetThinkHandle(U::ThinkHandle_t hThink) = 0;
	virtual void				Release() = 0;
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void				Release() = 0;
	virtual const CVector3& GetAbsOrigin() const = 0;
	virtual const QAngle& GetAbsAngles() const = 0;
	virtual CMouthInfo* GetMouth() = 0;
	virtual bool				GetSoundSpatialization(void*& info) = 0;
	virtual bool				IsBlurred() = 0;
};