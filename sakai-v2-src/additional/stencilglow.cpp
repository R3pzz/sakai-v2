#include "stencilglow.h"
// Include material system
#include "../sdk/interfaces.h"
// Include CBaseEntity
#include "../sdk/classes.h"
// Include config
#include "config.h"
// Include studio render flags
#include "../sdk/types/studiorender_defs.h"

void CStencilGlow::Init()
{
	// Base glow materials
	m_Materials.at(M_DOWNSAMPLE) = I::m_pMatSystem->FindMaterial("dev/glow_downsample", TEXTURE_GROUP_OTHER);
	m_Materials.at(M_BLUR_X) = I::m_pMatSystem->FindMaterial("dev/glow_blur_x", TEXTURE_GROUP_OTHER);
	m_Materials.at(M_BLUR_Y) = I::m_pMatSystem->FindMaterial("dev/glow_blur_y", TEXTURE_GROUP_OTHER);
	// Additive glow materials
	m_Materials.at(M_SHAPE) = I::m_pMatSystem->FindMaterial("dev/glow_color", TEXTURE_GROUP_OTHER);
	m_Materials.at(M_RIM_3D) = I::m_pMatSystem->FindMaterial("dev/glow_rim3d", TEXTURE_GROUP_OTHER);
	m_Materials.at(M_HALO) = I::m_pMatSystem->FindMaterial("dev/halo_add_to_screen", TEXTURE_GROUP_OTHER);
	m_Materials.at(M_EDGE_HIGHLIGHT) = I::m_pMatSystem->FindMaterial("dev/glow_edge_highlight", TEXTURE_GROUP_OTHER);
	// Fill glow textures
	m_Textures.at(M_Q_SIZE_0) = I::m_pMatSystem->FindTexture("_rt_SmallFB0", "RenderTargets");
	m_Textures.at(M_Q_SIZE_1) = I::m_pMatSystem->FindTexture("_rt_SmallFB1", "RenderTargets");
	m_Textures.at(M_FULL_FRAME) = I::m_pMatSystem->FindTexture("_rt_FullFrameFB", "RenderTargets");
}

void CStencilGlow::PushEntity(CBaseEntity* Entity, GlowEntity_t& Setup)
{
	Setup.first.m_Owner = Entity;
	Setup.second.m_Owner = Entity;

	Setup.first.m_Visible = true;
	Setup.second.m_Visible = false;

	m_Entities.push_back(Setup);
}

void CStencilGlow::OnDME(int W, int H)
{
	std::vector<GlowDef_t> GlowRim3D;
	std::vector<GlowDef_t> GlowOther;

	for (auto it = 0U; it != m_Entities.size(); it++)
	{
		if (m_Entities[it].first.m_Style == EGlowStyle::GLOW_RIM3D)
		{
			GlowRim3D.push_back(m_Entities[it].first);
		}
		else
		{
			GlowOther.push_back(m_Entities[it].first);
		}

		if (m_Entities[it].second.m_Style == EGlowStyle::GLOW_RIM3D)
		{
			GlowRim3D.push_back(m_Entities[it].second);
		}
		else
		{
			GlowOther.push_back(m_Entities[it].second);
		}
	}

	auto RimPulse = 0.5f + 0.5f * std::sinf(I::m_pGlobalVars->m_flCurTime * g_pConfig->m_Glow_Rim3DSpeed);
	auto* MatRim3D = m_Materials.at(M_RIM_3D);

	I::m_pModelRender->ForcedMaterialOverride(MatRim3D, OVERRIDE_NORMAL);

	for (auto& CurGlow : GlowRim3D)
	{
		auto* $envmaptint = MatRim3D->FindVar("$envmaptint");
		auto* $envmapfresnelminmaxexp = MatRim3D->FindVar("$envmapfresnelminmaxexp");

		if ($envmaptint)
		{
			auto $r = std::clamp(CurGlow.m_Alpha * CurGlow.m_Color[0], 0.f, 1.f);
			auto $g = std::clamp(CurGlow.m_Alpha * CurGlow.m_Color[1], 0.f, 1.f);
			auto $b = std::clamp(CurGlow.m_Alpha * CurGlow.m_Color[2], 0.f, 1.f);

			$envmaptint->SetVectorComponent($r, 0);
			$envmaptint->SetVectorComponent($g, 1);
			$envmaptint->SetVectorComponent($b, 2);
		}

		if ($envmapfresnelminmaxexp)
		{
			$envmapfresnelminmaxexp->SetVectorComponent(0, 0);
			$envmapfresnelminmaxexp->SetVectorComponent(1.5f, 1);
			$envmapfresnelminmaxexp->SetVectorComponent(3.0f + RimPulse * 2.0f, 2);
		}

		CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
	}

	I::m_pModelRender->ForcedMaterialOverride(NULL, OVERRIDE_NORMAL);

	if (!GlowOther.empty())
	{
		m_Context->PushRenderTargetAndViewport();

		CVector3 OrigCC;
		I::m_pRenderView->GetCC(OrigCC.Base());

		auto* OutMat = m_Textures.at(M_FULL_FRAME);
		m_Context->SetRenderTarget(OutMat);
		m_Context->Viewport(0, 0, W, H);

		auto* ShapeMat = m_Materials.at(M_SHAPE);
		I::m_pStudioRender->ForcedMaterialOverride(ShapeMat, OVERRIDE_NORMAL);

		I::m_pRenderView->SetBlend(1);

		auto CC = CVector3(1.f, 1.f, 1.f);
		I::m_pRenderView->SetCC(CC.Base());

		// Draw base glow model
		for (auto& CurGlow : GlowOther)
		{
			CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
		}

		I::m_pStudioRender->ForcedMaterialOverride(NULL, OVERRIDE_NORMAL);
		m_Context->PopRenderTargetAndViewport();

		auto* EdgeMat = m_Materials.at(M_EDGE_HIGHLIGHT);
		I::m_pStudioRender->ForcedMaterialOverride(EdgeMat, OVERRIDE_NORMAL);

		// Draw edge glow model
		for (auto& CurGlow : GlowOther)
		{
			auto $r = CurGlow.m_Alpha * CurGlow.m_Color[0] * 1.4f;
			auto $g = CurGlow.m_Alpha * CurGlow.m_Color[1] * 1.4f;
			auto $b = CurGlow.m_Alpha * CurGlow.m_Color[2] * 1.4f;

			auto Col = CVector3($r, $g, $b);

			if (CurGlow.m_Style == EGlowStyle::GLOW_EDGE_PULSE)
				Col *= RimPulse;

			I::m_pRenderView->SetCC(Col.Base());
			CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
		}

		I::m_pStudioRender->ForcedMaterialOverride(NULL, OVERRIDE_NORMAL);
	}
}

void CStencilGlow::Apply()
{
	auto* GlowMat = m_Materials.at(M_SHAPE);
	I::m_pStudioRender->ForcedMaterialOverride(GlowMat, OVERRIDE_NORMAL);

	ShaderStencilState_t DisableState;
	DisableState.m_Enable = false;

	auto OrigBlend = I::m_pRenderView->GetBlend();
	I::m_pRenderView->SetBlend(1);

	m_Context->OverrideDepthEnable(true, false);

	std::vector<GlowDef_t> OtherGlow;

	for (auto& CurGlow : m_Entities)
	{
		if (CurGlow.first.m_FullBloom != true)
		{
			OtherGlow.push_back(CurGlow.first);
		}

		if (CurGlow.second.m_FullBloom != true)
		{
			OtherGlow.push_back(CurGlow.second);
		}
	}

	for (auto& CurGlow : OtherGlow)
	{
		auto CID = CurGlow.m_Owner->GetClientClass()->m_nClassID;

		switch (CID)
		{
		case EClassID::CCSPlayer:
			if (!g_pConfig->m_Glow_PlayersEnabled)
				continue;

			if (CurGlow.m_Visible == true)
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 1;
				State.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
				State.m_PassOp = SHADER_STENCILOP_KEEP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}
			else
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 2;
				State.m_TestMask = 0x1;
				State.m_WriteMask = 0x3;
				State.m_CompareFunc = SHADER_STENCILFUNC_EQUAL;
				State.m_PassOp = SHADER_STENCILOP_INCREMENT_CLAMP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}

		case EClassID::CPlantedC4:
			if (!g_pConfig->m_Glow_C4Enabled)
				continue;

			if (CurGlow.m_Visible == true)
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 1;
				State.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
				State.m_PassOp = SHADER_STENCILOP_KEEP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}
			else
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 2;
				State.m_TestMask = 0x1;
				State.m_WriteMask = 0x3;
				State.m_CompareFunc = SHADER_STENCILFUNC_EQUAL;
				State.m_PassOp = SHADER_STENCILOP_INCREMENT_CLAMP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}

		case EClassID::CBaseDoor:
			if (!g_pConfig->m_Glow_DoorsEnabled)
				continue;

			if (CurGlow.m_Visible == true)
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 1;
				State.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
				State.m_PassOp = SHADER_STENCILOP_KEEP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}
			else
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 2;
				State.m_TestMask = 0x1;
				State.m_WriteMask = 0x3;
				State.m_CompareFunc = SHADER_STENCILFUNC_EQUAL;
				State.m_PassOp = SHADER_STENCILOP_INCREMENT_CLAMP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}

		case EClassID::CCSRagdoll:
			if (!g_pConfig->m_Glow_RagdollEnabled)
				continue;

			if (CurGlow.m_Visible == true)
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 1;
				State.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
				State.m_PassOp = SHADER_STENCILOP_KEEP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}
			else
			{
				ShaderStencilState_t State;
				State.m_Enable = true;
				State.m_RefValue = 2;
				State.m_TestMask = 0x1;
				State.m_WriteMask = 0x3;
				State.m_CompareFunc = SHADER_STENCILFUNC_EQUAL;
				State.m_PassOp = SHADER_STENCILOP_INCREMENT_CLAMP;
				State.m_FailOp = SHADER_STENCILOP_KEEP;
				State.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;

				m_Context->SetStencilState(State);

				CurGlow.m_Owner->DrawModel(STUDIO_RENDER | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS, CurGlow.m_Alpha * 255.f);
			}
		}
	}

	m_Context->OverrideDepthEnable(false, false);
	I::m_pRenderView->SetBlend(OrigBlend);
	m_Context->SetStencilState(DisableState);

	static auto s_FirstPass = true;

	m_Context->PushRenderTargetAndViewport();
	
	int ViewportWidth;
	int ViewportHeight;
	I::m_pSurface->GetScreenSize(ViewportWidth, ViewportHeight);

	m_Context->BeginPIXEvent(0xFFF5940F, "RenderGlowModels");
	OnDME(ViewportWidth, ViewportHeight);

	auto* MatDownsample = m_Materials.at(M_DOWNSAMPLE);
	auto* MatBlur_X = m_Materials.at(M_BLUR_X);
	auto* MatBlur_Y = m_Materials.at(M_BLUR_Y);

	auto* RT_QuarterSize0 = m_Textures.at(M_Q_SIZE_0);
	auto* RT_QuarterSize1 = m_Textures.at(M_Q_SIZE_1);

	if ((RT_QuarterSize0->GetActualWidth() != ViewportWidth / 4)
		|| (RT_QuarterSize0->GetActualHeight() != ViewportHeight / 4))
	{
		m_Context->SetRenderTarget(RT_QuarterSize0);
		m_Context->Viewport(0, 0, RT_QuarterSize0->GetActualWidth(), RT_QuarterSize0->GetActualHeight());
		m_Context->ClearColor3ub(0, 0, 0);
		m_Context->ClearBuffers(true, false, false);
	}

	m_Context->SetRenderTarget(RT_QuarterSize0);
	m_Context->Viewport(0, 0, ViewportWidth / 4, ViewportHeight / 4);

	auto* $bloomexp = MatDownsample->FindVar("$bloomexp");

	if ($bloomexp)
	{
		$bloomexp->SetFloat(2.5f);
	}

	auto* $bloomsaturation = MatDownsample->FindVar("$bloomsaturation");

	if ($bloomsaturation)
	{
		$bloomsaturation->SetFloat(1.f);
	}

	int FullFB_Width = ViewportWidth;
	int FullFB_Height = ViewportHeight;
	auto* FullFrame = m_Textures.at(M_FULL_FRAME);

	m_Context->DrawScreenSpaceRectangle(MatDownsample, 0, 0, ViewportWidth / 4, ViewportHeight / 4,
		0.f, 0.f, FullFB_Width - 4, FullFB_Height - 4,
		FullFrame->GetActualWidth(), FullFrame->GetActualHeight());

	if (s_FirstPass
		|| (RT_QuarterSize1->GetActualWidth() != ViewportWidth / 4)
		|| (RT_QuarterSize1->GetActualHeight() != ViewportHeight / 4))
	{
		s_FirstPass = false;
		m_Context->SetRenderTarget(RT_QuarterSize1);
		m_Context->Viewport(0, 0, RT_QuarterSize1->GetActualWidth(), RT_QuarterSize1->GetActualHeight());
		m_Context->ClearColor3ub(0, 0, 0);
		m_Context->ClearBuffers(true, false, false);
	}

	m_Context->SetRenderTarget(RT_QuarterSize1);
	m_Context->Viewport(0, 0, ViewportWidth / 4, ViewportHeight / 4);

	m_Context->DrawScreenSpaceRectangle(MatBlur_X, 0, 0, ViewportWidth / 4, ViewportHeight / 4,
		0, 0, ViewportWidth / 4 - 1, ViewportHeight / 4 - 1,
		RT_QuarterSize0->GetActualWidth(), RT_QuarterSize0->GetActualHeight());

	m_Context->SetRenderTarget(RT_QuarterSize0);
	m_Context->Viewport(0, 0, ViewportWidth / 4, ViewportHeight / 4);

	auto* $bloomamount = MatBlur_Y->FindVar("$bloomamount");
	$bloomamount->SetFloat(10.f);
	m_Context->DrawScreenSpaceRectangle(MatBlur_Y, 0, 0, ViewportWidth / 4, ViewportHeight / 4,
		0, 0, ViewportWidth / 4 - 1, ViewportHeight / 4 - 1,
		RT_QuarterSize1->GetActualWidth(), RT_QuarterSize1->GetActualHeight());

	m_Context->PopRenderTargetAndViewport();

	{
		auto* MatHalo = m_Materials.at(M_HALO);
		auto* $C0_X = MatHalo->FindVar("$C0_X");

		$C0_X->SetFloat(1.f);

		ShaderStencilState_t LastState;
		LastState.m_Enable = true;
		LastState.m_WriteMask = 0x0;
		LastState.m_TestMask = 0x3;
		LastState.m_RefValue = 0x0;
		LastState.m_CompareFunc = SHADER_STENCILFUNC_EQUAL;
		LastState.m_PassOp = SHADER_STENCILOP_KEEP;
		LastState.m_FailOp = SHADER_STENCILOP_KEEP;
		LastState.m_ZFailOp = SHADER_STENCILOP_KEEP;

		m_Context->SetStencilState(LastState);

		m_Context->DrawScreenSpaceRectangle(MatHalo, 0, 0, ViewportWidth, ViewportHeight,
			0.0f, -0.5f, ViewportWidth / 4 - 1, ViewportHeight / 4 - 1,
			RT_QuarterSize1->GetActualWidth(),
			RT_QuarterSize1->GetActualHeight(), nullptr, 0, 0);

		m_Context->SetStencilState(DisableState);
	}
}