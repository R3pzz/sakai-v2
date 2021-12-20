#include "sdk.h"

#include "core/network.h"

void Globals_Init()
{
	G::m_BuildTime = __DATE__;
	G::m_CurrentWindow = IO_GetHwnd();
	// Check if we actually initialized our device in I
	//	so we can just "copy-paste" it
#ifdef DEBUG
	assert(I::m_pDevice != NULL);
#else
	if (!I::m_pDevice)
		L::LogEvent(XOR("'Globals_Init()': Initialized G::m_Direct3Device before I::m_pDevice"), L::EEventType::LOG_EVENT_FAILURE); return;
#endif
	G::m_Direct3Device = I::m_pDevice;
	G::m_SystemEnv = std::getenv("SystemDrive");
	G::m_UserName = NET::GetServerName();
}

HWND IO_GetHwnd()
{ 
	// Init our device so we can get HWND
	D3DDEVICE_CREATION_PARAMETERS Params = D3DDEVICE_CREATION_PARAMETERS();
	// Get HWND
	return Params.hFocusWindow;
}