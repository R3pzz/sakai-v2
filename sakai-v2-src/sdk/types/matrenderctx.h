#pragma once
// Include std stuff
#include "../platform.h"
// Include vectors
#include "vector.h"
// Include vmatrix
#include "matrix.h"
// Include context defs
#include "matrenderctx_defs.h"

class IVertexBuffer;
class IIndexBuffer;
class IMaterial;
class ITexture;
class IMorph;
class IMesh;
struct ShaderStencilState_t;

class ITexture
{
public:
	virtual const char*		GetName() const = 0;
	virtual int				GetMappingWidth() const = 0;
	virtual int				GetMappingHeight() const = 0;
	virtual int				GetActualWidth() const = 0;
	virtual int				GetActualHeight() const = 0;
	virtual int				GetNumAnimationFrames() const = 0;
	virtual bool			IsTranslucent() const = 0;
	virtual bool			IsMipmapped() const = 0;
};

class IMatRenderContext
{
public:
	// Properly align VMT
	virtual void				_0() {}
	virtual void				_1() {}

	virtual void				BeginRender() = 0;
	virtual void				EndRender() = 0;
	virtual void				Flush(bool flushHardware = false) = 0;
	virtual void				BindLocalCubemap(ITexture* pTexture) = 0;
	virtual void				SetRenderTarget(ITexture* pTexture) = 0;
	virtual ITexture*			GetRenderTarget() = 0;
	virtual void				GetRenderTargetDimensions(int& width, int& height) const = 0;
	virtual void				Bind(IMaterial* material, void* proxyData = 0) = 0;
	virtual void				BindLightmapPage(int lightmapPageID) = 0;
	virtual void				DepthRange(float zNear, float zFar) = 0;
	virtual void				ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false) = 0;
	virtual void				ReadPixels(int x, int y, int width, int height, unsigned char* data, EImageFormat  dstFormat, ITexture* pRenderTargetTexture = NULL) = 0;
	virtual void				ReadPixelsAsync(int x, int y, int width, int height, unsigned char* data, EImageFormat  dstFormat, ITexture* pRenderTargetTexture = NULL, void* pPixelsReadEvent = NULL) = 0;
	virtual void				ReadPixelsAsyncGetResult(int x, int y, int width, int height, unsigned char* data, EImageFormat  dstFormat, void* pGetResultEvent = NULL) = 0;
	virtual void				SetLightingState(const MaterialLightingState_t& state) = 0;
	virtual void				SetLights(int nCount, const LightDesc_t* pLights) = 0;
	virtual void				SetAmbientLightCube(AmbientCube_t Cube) = 0;
	virtual void				CopyRenderTargetToTexture(ITexture* pTexture) = 0;
	virtual void				SetFrameBufferCopyTexture(ITexture* pTexture, int textureIndex = 0) = 0;
	virtual ITexture*			GetFrameBufferCopyTexture(int textureIndex) = 0;
	virtual void				MatrixMode(EMatrixMode matrixMode) = 0;
	virtual void				PushMatrix() = 0;
	virtual void				PopMatrix() = 0;
	virtual void				LoadMatrix(VMatrix const& matrix) = 0;
	virtual void				LoadMatrix(CMatrix3x4 const& matrix) = 0;
	virtual void				MultMatrix(VMatrix const& matrix) = 0;
	virtual void				MultMatrix(CMatrix3x4 const& matrix) = 0;
	virtual void				MultMatrixLocal(VMatrix const& matrix) = 0;
	virtual void				MultMatrixLocal(CMatrix3x4 const& matrix) = 0;
	virtual void				GetMatrix(EMatrixMode matrixMode, VMatrix* matrix) = 0;
	virtual void				GetMatrix(EMatrixMode matrixMode, CMatrix3x4* matrix) = 0;
	virtual void				LoadIdentity() = 0;
	virtual void				Ortho(double left, double top, double right, double bottom, double zNear, double zFar) = 0;
	virtual void				PerspectiveX(double fovx, double aspect, double zNear, double zFar) = 0;
	virtual void				PickMatrix(int x, int y, int width, int height) = 0;
	virtual void				Rotate(float angle, float x, float y, float z) = 0;
	virtual void				Translate(float x, float y, float z) = 0;
	virtual void				Scale(float x, float y, float z) = 0;
	virtual void				Viewport(int x, int y, int width, int height) = 0;
	virtual void				GetViewport(int& x, int& y, int& width, int& height) const = 0;
	virtual void				CullMode(EMatCullMode cullMode) = 0;
	virtual void				FlipCullMode() = 0;
	virtual void				BeginGeneratingCSMs() = 0;
	virtual void				EndGeneratingCSMs() = 0;
	virtual void				PerpareForCascadeDraw(int cascade, float fShadowSlopeScaleDepthBias, float fShadowDepthBias) = 0;
	virtual void				SetHeightClipMode(int nHeightClipMode) = 0;
	virtual void				SetHeightClipZ(float z) = 0;
	virtual void				FogMode(EMatFogMode fogMode) = 0;
	virtual void				FogStart(float fStart) = 0;
	virtual void				FogEnd(float fEnd) = 0;
	virtual void				SetFogZ(float fogZ) = 0;
	virtual EMatFogMode			GetFogMode() = 0;
	virtual void				FogColor3f(float r, float g, float b) = 0;
	virtual void				FogColor3fv(float const* rgb) = 0;
	virtual void				FogColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void				FogColor3ubv(unsigned char const* rgb) = 0;
	virtual void				GetFogColor(unsigned char* rgb) = 0;
	virtual void				SetNumBoneWeights(int numBones) = 0;
	virtual IMesh*				CreateStaticMesh(std::uint64_t fmt, const char* pTextureBudgetGroup, IMaterial* pMaterial = NULL, void* pStreamSpec = NULL) = 0;
	virtual void				DestroyStaticMesh(IMesh* mesh) = 0;
	virtual IMesh*				GetDynamicMesh(bool buffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0, IMaterial* pAutoBind = 0) = 0;
	virtual IVertexBuffer*		CreateStaticVertexBuffer(std::uint64_t fmt, int nVertexCount, const char* pTextureBudgetGroup) = 0;
	virtual IIndexBuffer*		CreateStaticIndexBuffer(int fmt, int nIndexCount, const char* pTextureBudgetGroup) = 0;
	virtual void				DestroyVertexBuffer(IVertexBuffer*) = 0;
	virtual void				DestroyIndexBuffer(IIndexBuffer*) = 0;
	virtual IVertexBuffer*		GetDynamicVertexBuffer(int streamID, std::uint64_t vertexFormat, bool bBuffered = true) = 0;
	virtual IIndexBuffer*		GetDynamicIndexBuffer() = 0;
	virtual void				BindVertexBuffer(int streamID, IVertexBuffer* pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount, std::uint64_t fmt, int nRepetitions = 1) = 0;
	virtual void				BindIndexBuffer(IIndexBuffer* pIndexBuffer, int nOffsetInBytes) = 0;
	virtual void				Draw(int primitiveType, int firstIndex, int numIndices) = 0;
	virtual int					SelectionMode(bool selectionMode) = 0;
	virtual void				SelectionBuffer(unsigned int* pBuffer, int size) = 0;
	virtual void				ClearSelectionNames() = 0;
	virtual void				LoadSelectionName(int name) = 0;
	virtual void				PushSelectionName(int name) = 0;
	virtual void				PopSelectionName() = 0;
	virtual void				ClearColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void				ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
	virtual void				OverrideDepthEnable(bool bEnable, bool bDepthWriteEnable, bool bDepthTestEnable = true) = 0;
	virtual void				DrawScreenSpaceQuad(IMaterial* pMaterial) = 0;
	virtual void				SyncToken(const char* pToken) = 0;
	virtual float				ComputePixelWidthOfSphere(const CVector3& origin, float flRadius) = 0;
	virtual void*				CreateOcclusionQueryObject() = 0;
	virtual void				DestroyOcclusionQueryObject(void* handle) = 0;
	virtual void				BeginOcclusionQueryDrawing(void* handle) = 0;
	virtual void				EndOcclusionQueryDrawing(void* handle) = 0;
	virtual int					OcclusionQuery_GetNumPixelsRendered(void* handle) = 0;
	virtual void				SetFlashlightMode(bool bEnable) = 0;
	virtual void				SetFlashlightState(const int& state, const VMatrix& worldToTexture) = 0;
	virtual bool				IsCascadedShadowMapping() const = 0;
	virtual void				SetCascadedShadowMapping(bool bEnable) = 0;
	virtual void				SetCascadedShadowMappingState(const int& state, ITexture* pDepthTextureAtlas) = 0;
	virtual int					GetHeightClipMode() = 0;
	virtual float				ComputePixelDiameterOfSphere(const CVector3& vecAbsOrigin, float flRadius) = 0;
	virtual void				EnableUserClipTransformOverride(bool bEnable) = 0;
	virtual void				UserClipTransform(const VMatrix& worldToView) = 0;
	virtual bool				GetFlashlightMode() const = 0;
	virtual bool				IsCullingEnabledForSinglePassFlashlight() const = 0;
	virtual void				EnableCullingForSinglePassFlashlight(bool bEnable) = 0;
	virtual void				ResetOcclusionQueryObject(void* handle) = 0;
	virtual IMorph*				CreateMorph(std::uint32_t format, const char* pDebugName) = 0;
	virtual void				DestroyMorph(IMorph* pMorph) = 0;
	virtual void				BindMorph(IMorph* pMorph) = 0;
	virtual void				SetFlexWeights(int nFirstWeight, int nCount, const MorphWeight_t* pWeights) = 0;
	virtual void*				LockRenderData(int nSizeInBytes) = 0;
	virtual void				UnlockRenderData(void* pData) = 0;
	virtual void				AddRefRenderData() = 0;
	virtual void				ReleaseRenderData() = 0;
	virtual bool				IsRenderData(const void* pData) const = 0;
	virtual void				ReadPixelsAndStretch(void* pSrcRect, void* pDstRect, unsigned char* pBuffer, EImageFormat  dstFormat, int nDstStride) = 0;
	virtual void				GetWindowSize(int& width, int& height) const = 0;
	virtual void				DrawScreenSpaceRectangle(IMaterial* pMaterial, int destx, int desty, int width, int height, float src_texture_x0, float src_texture_y0, float src_texture_x1, float src_texture_y1, int src_texture_width, int src_texture_height, void* pClientRenderable = NULL, int nXDice = 1, int nYDice = 1) = 0;
	virtual void				LoadBoneMatrix(int boneIndex, const CMatrix3x4& matrix) = 0;
	virtual void				PushRenderTargetAndViewport() = 0;
	virtual void 				PushRenderTargetAndViewport(ITexture* pTexture) = 0;
	virtual void 				PushRenderTargetAndViewport(ITexture* pTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;
	virtual void 				PushRenderTargetAndViewport(ITexture* pTexture, ITexture* pDepthTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;
	virtual void 				PopRenderTargetAndViewport() = 0;
	virtual void 				BindLightmapTexture(ITexture* pLightmapTexture) = 0;
	virtual void 				CopyRenderTargetToTextureEx(ITexture* pTexture, int nRenderTargetID, void* pSrcRect, void* pDstRect = NULL) = 0;
	virtual void 				CopyTextureToRenderTargetEx(int nRenderTargetID, ITexture* pTexture, void* pSrcRect, void* pDstRect = NULL) = 0;
	virtual void 				PerspectiveOffCenterX(double fovx, double aspect, double zNear, double zFar, double bottom, double top, double left, double right) = 0;
	virtual void 				SetFloatRenderingParameter(int parm_number, float value) = 0;
	virtual void 				SetIntRenderingParameter(int parm_number, int value) = 0;
	virtual void 				SetVectorRenderingParameter(int parm_number, CVector3 const& value) = 0;
	virtual void				SetStencilState(const ShaderStencilState_t& state) = 0;
	virtual void				ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value) = 0;
	virtual void 				SetRenderTargetEx(int nRenderTargetID, ITexture* pTexture) = 0;
	virtual void 				PushCustomClipPlane(const float* pPlane) = 0;
	virtual void 				PopCustomClipPlane() = 0;
	virtual void 				GetMaxToRender(IMesh* pMesh, bool bMaxUntilFlush, int* pMaxVerts, int* pMaxIndices) = 0;
	virtual int 				GetMaxVerticesToRender(IMaterial* pMaterial) = 0;
	virtual int 				GetMaxIndicesToRender() = 0;
	virtual void 				DisableAllLocalLights() = 0;
	virtual int 				CompareMaterialCombos(IMaterial* pMaterial1, IMaterial* pMaterial2, int lightMapID1, int lightMapID2) = 0;
	virtual IMesh*				GetFlexMesh() = 0;
	virtual void  				SetFlashlightStateEx(const int& state, const VMatrix& worldToTexture, ITexture* pFlashlightDepthTexture) = 0;
	virtual ITexture*			GetLocalCubemap() = 0;
	virtual void				ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth) = 0;
	virtual bool				EnableClipping(bool bEnable) = 0;
	virtual void				GetFogDistances(float* fStart, float* fEnd, float* fFogZ) = 0;
	virtual void				BeginPIXEvent(unsigned long color, const char* szName) = 0;
	virtual void				EndPIXEvent() = 0;
	virtual void				SetPIXMarker(unsigned long color, const char* szName) = 0;
	virtual void				BeginBatch(IMesh* pIndices) = 0;
	virtual void				BindBatch(IMesh* pVertices, IMaterial* pAutoBind = NULL) = 0;
	virtual void				DrawBatch(int primType, int firstIndex, int numIndices) = 0;
	virtual void				EndBatch() = 0;
	virtual void*				GetCallQueue() = 0;
	virtual void				GetWorldSpaceCameraPosition(CVector3* pCameraPos) = 0;
	virtual void				GetWorldSpaceCameraVectors(CVector3* pVecForward, CVector3* pVecRight, CVector3* pVecUp) = 0;
	virtual void				SetToneMappingScaleLinear(const CVector3& scale) = 0;
	virtual CVector3			GetToneMappingScaleLinear(void) = 0;
	virtual void				SetShadowDepthBiasFactors(float fSlopeScaleDepthBias, float fDepthBias) = 0;
	virtual void				PerformFullScreenStencilOperation() = 0;
	virtual void				SetLightingOrigin(CVector3 vLightingOrigin) = 0;
	virtual void				PushScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom) = 0;
	virtual void				PopScissorRect() = 0;
	virtual void				BeginMorphAccumulation() = 0;
	virtual void				EndMorphAccumulation() = 0;
	virtual void				AccumulateMorph(IMorph* pMorph, int nMorphCount, const MorphWeight_t* pWeights) = 0;
	virtual void				PushDeformation(const void* Deformation) = 0;
	virtual void				PopDeformation() = 0;
	virtual int					GetNumActiveDeformations() const = 0;
	virtual bool				GetMorphAccumulatorTexCoord(CVector2* pTexCoord, IMorph* pMorph, int nVertex) = 0;
	virtual IMesh*				GetDynamicMeshEx(std::uint64_t vertexFormat, bool bBuffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0, IMaterial* pAutoBind = 0) = 0;
	virtual void				FogMaxDensity(float flMaxDensity) = 0;
	virtual void                AntiAliasingHint(int nHint) = 0;
	virtual IMaterial*			GetCurrentMaterial() = 0;
	virtual int					GetCurrentNumBones() const = 0;
	virtual void*				GetCurrentProxy() = 0;
	virtual void				EnableColorCorrection(bool bEnable) = 0;
	virtual std::uintptr_t		AddLookup(const char* pName) = 0;
	virtual bool				RemoveLookup(std::uintptr_t handle) = 0;
	virtual void				LockLookup(std::uintptr_t handle) = 0;
	virtual void				LoadLookup(std::uintptr_t handle, const char* pLookupName) = 0;
	virtual void				UnlockLookup(std::uintptr_t handle) = 0;
	virtual void				SetLookupWeight(std::uintptr_t handle, float flWeight) = 0;
	virtual void				ResetLookupWeights() = 0;
	virtual void				SetResetable(std::uintptr_t handle, bool bResetable) = 0;
};

class CPIXEvent
{
public:
	CPIXEvent(IMatRenderContext* Ctx, const char* Name, unsigned long Col = PIX_VALVE_ORANGE)
	{
		m_pRenderContext = Ctx;
		m_pRenderContext->BeginPIXEvent(Col, Name);
	}

	~CPIXEvent()
	{
		m_pRenderContext->EndPIXEvent();
	}

public:
	IMatRenderContext* m_pRenderContext;
};