#include "chams.h"
// Include globals
#include "../../additional/cl.h"
// Include config system
#include "../../additional/config.h"

CChams* g_pChams = new CChams();

IMaterial* CChams::CreateMaterial(std::string_view Name, std::string_view Shader, std::string_view KeyValues)
{
	auto* Kv = new CKeyValues();

	Kv->Init(Shader.data());
	Kv->FromBuffer(Name.data(), Shader.data());

	auto* Material = I::m_pMatSystem->CreateMaterial(Name.data(), Kv);

	return Material;
}

IMaterial* CChams::MaterialByIndex(int Index, bool Overlays)
{
	if (Overlays)
	{
		switch (Index)
		{
		case 0: return m_pGlassMat;
		case 1: return m_pOutlineMat;
		case 2: return m_pGlowMat;
		default: return m_pGlowMat;
		}
	}
	else
	{
		switch (Index)
		{
		case 0: return m_pDefaultMat;
		case 1: return m_pFlatMat;
		case 2: return m_pAnimatedMat;
		default: return m_pDefaultMat;
		}
	}

	return NULL;
}

bool CChams::Init()
{
	// @Credits: https://www.unknowncheats.me/forum/counterstrike-global-offensive/223578-decent-material-list-chams.html

	// Default material
	{
		m_pDefaultMat = I::m_pMatSystem->FindMaterial(XOR("debug/debugambientcube"), NULL);
	}

	// Flat material
	{
		m_pFlatMat = CreateMaterial(XOR("sakai_flat"), XOR("UnlitGeneric"), XOR(R"#( "UnlitGeneric"
			"$basetexture" "debug/debugdrawflat"
			"$ignorez"      "0"
			"$model"		"1"
			"$flat"			"1"
			"$nocull"		"1"
			"$selfillum"	"1"
			"$halflambert"	"1"
			"$nofog"		"1"
		)#"));
	}

	// Glass material
	{
		m_pGlassMat = CreateMaterial(XOR("sakai_glass"), XOR("VertexLitGeneric"), XOR(R"#( "VertexLitGeneric"
			"$basetexture"	"models/inventory_items/trophy_majors/gloss"
			"$ignorez"      "0"
			"$model"		"1"
			"$flat"			"0"
			"$nocull"		"1"
			"$selfillum"	"0"
			"$halflambert"	"1"
			"$nofog"		"1"
		)#"));
	}

	// Outline material
	{
		m_pOutlineMat = CreateMaterial(XOR("sakai_outline"), XOR("VertexLitGeneric"), XOR(R"#( "VertexLitGeneric"
			"$basetexture"	"vgui/achievements/glow"
			"$ignorez"      "0"
			"$envmap"		"env_cubemap"
			"$model"		"1"
			"$flat"			"0"
			"$nocull"		"1"
			"$selfillum"	"0"
			"$halflambert"	"1"
			"$nofog"		"1"
		)#"));
	}

	// Glow material
	{
		m_pGlowMat = CreateMaterial(XOR("sakai_glow"), XOR("VertexLitGeneric"), XOR(R"#( "VertexLitGeneric"
			"$basetexture"	"vgui/white"
			"$ignorez"      "0"
			"$envmap"		"env_cubemap"
			"$model"		"1"
			"$flat"			"0"
			"$nocull"		"1"
			"$selfillum"	"0"
			"$halflambert"	"1"
			"$nofog"		"1"
		)#"));
	}

	// Animated material
	{
		m_pGlowMat = CreateMaterial(XOR("sakai_glow"), XOR("VertexLitGeneric"), XOR(R"#( "VertexLitGeneric"
			"$basetexture"	"dev/zone_warning"
			"$ignorez"      "0"
			"$envmap"		"editor/cube_vertigo"
			"envmapcontrast" "1"
			"$model"		"1"
			"$flat"			"0"
			"$nocull"		"1"
			"$selfillum"	"0"
			"$halflambert"	"1"
			"$nofog"		"1"

			"proxies"
			{
				"texturescroll"
				{ 
					"texturescrollvar"		"$basetexturetransform"
					"texturescrollrate"		"0.6"
					"texturescrollangle"	"90"
				}
			}
		)#"));
	}

	if (!m_pAnimatedMat
		|| !m_pDefaultMat
		|| !m_pFlatMat
		|| !m_pGlassMat
		|| !m_pGlowMat
		|| !m_pOutlineMat)
		return false;

	return true;
}

bool CChams::SwapMaterials(IMaterial* To, bool IgnoreZ, Color4_t Col, bool Wireframe)
{
	if (!To || I::m_pModelRender->IsForcedMaterialOverride())
		return false;

	auto* Material = To;

	// We should override envmap's color for these
	if (Material == m_pGlowMat
		|| Material == m_pOutlineMat)
	{
		auto* Var = Material->FindVar("$envmaptint");
		Var->SetVector(CVector3(Col[1] / 255.f, Col[2] / 255.f, Col[3] / 255.f));
	}
	else
	{
		Material->ColorModulate(Col);
	}

	// Set the proper alpha
	Material->AlphaModulate(Col[4] / 255.f);

	Material->SetFlag(MATERIAL_VAR_IGNOREZ, IgnoreZ);
	Material->SetFlag(MATERIAL_VAR_WIREFRAME, Wireframe);

	I::m_pModelRender->ForcedMaterialOverride(Material, OVERRIDE_NORMAL);

	return true;
}

void CChams::OnDME(const ModelRenderInfo_t& Info)
{
	/*get dme fn*/

	auto* Ent = Info.m_pRenderable->GetIClientUnknown()->GetBaseEntity();
	if (!Ent)
		return;

	auto* Player = reinterpret_cast<CCSPlayer*>(Ent);
	if (!Player
		|| !Player->IsEnemy(g_Cl->m_pLocal))
		return;

	SwapMaterials(MaterialByIndex(g_pConfig->m_Chams_BaseMat, false), !g_pConfig->m_Chams_OnlyVisible, Color4_t{ 255.f, 0.f, 0.f, 255.f }, false);

	/*call original dme fn*/

	SwapMaterials(MaterialByIndex(g_pConfig->m_Chams_OverlayMat, true), !g_pConfig->m_Chams_OnlyVisible, Color4_t{ 255.f, 255.f, 255.f, 255.f }, true);
}