#pragma once
// Include our sdk
#include "../../sdk.h"

class CChams
{
public:
	CChams() { Init(); }

public:
	// Call this in your DME hook
	void OnDME(const ModelRenderInfo_t& Info);

	bool SwapMaterials(IMaterial* To, bool IgnoreZ, Color4_t Col, bool Wireframe);
	bool Init();

private:
	// Helper function to create a material
	IMaterial* CreateMaterial(std::string_view Name, std::string_view Shader, std::string_view KeyValues);

	IMaterial* MaterialByIndex(int Index, bool Overlays);

public:
	// Default solid material
	IMaterial* m_pDefaultMat = NULL;
	// Just a flat material material
	IMaterial* m_pFlatMat = NULL;
	// Skeet-styled glass(plastic) material
	IMaterial* m_pGlassMat = NULL;
	// Like a glow but thin material
	IMaterial* m_pOutlineMat = NULL;
	// Default env_cubemap material
	IMaterial* m_pGlowMat = NULL;
	// Animated material like in Osiris
	IMaterial* m_pAnimatedMat = NULL;
};

extern CChams* g_pChams;