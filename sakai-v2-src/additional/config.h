#pragma once
// Include CRT stuff
#include "../includes.h"
// Include base defs
#include "../sdk/platform.h"

class CConfig
{
public:
	/*Start of glow section*/
	bool m_Glow_PlayersEnabled = true;
	bool m_Glow_ChickensEnabled = false;
	bool m_Glow_C4Enabled = true;
	bool m_Glow_DoorsEnabled = false;
	bool m_Glow_RagdollEnabled = true;

	float m_Glow_Rim3DSpeed = 12.f;
	/*End of glow section*/

	bool m_Chams_Enabled = false;
	// Base mat [ -1 - 2 ] [ None - Default - Flat - Animated ]
	int m_Chams_BaseMat = -1;
	// Overlay mat [ -1 - 2 ] [ None - Glass - Outline - Glow ]
	int m_Chams_OverlayMat = 2;
	bool m_Chams_OnlyVisible = false;
	float* m_Chams_BaseColor = Color4_t{ 23.f, 0.f, 200.f, 255.f };
	float* m_Chams_OverlayColor = Color4_t{ 0.f, 230.f, 45.f, 255.f };
	bool m_Chams_WireframeBase = false;
	bool m_Chams_WireframeOverlay = true;
};

extern CConfig* g_pConfig;