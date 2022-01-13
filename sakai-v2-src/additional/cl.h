#pragma once

class CCSPlayer;
class CMatrix3x4;
struct CUserCmd;

class CCl
{
public:
	// Pointer to our local player
	CCSPlayer* m_pLocal;
	// Pointer to our usercmd
	CUserCmd* m_pCMD;
	// Should we send packet?
	bool* m_bSendPacket;
	// Our real (server) bone matrix
	CMatrix3x4* m_pRealMatrix;
	// Our fake (client) bone matrix
	CMatrix3x4* m_pFakeMatrix;
};

extern CCl* g_Cl;