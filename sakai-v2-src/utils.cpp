#include "utils.h"
// Include m_pDevice
#include "sdk/interfaces.h"
// Include menu funtions
#include "features/menu/menu.h"

namespace U
{
	namespace DATE
	{
		// std::string GetLocalTime() implementation.
		std::string GetLocalTime()
		{
			// Get our current time
			auto CurTime = time(NULL);
			// Implement timezone transition
			auto* TimeInfo = localtime(&CurTime);
			auto* Time = asctime(TimeInfo);

			if (!Time) // Check if we have a NULL string
				return std::string("");

			return Time;
		}

		// int GetLocalTime() implementation.
		template <ETimeStamp T = TS_HOURS> // Select timestamp we want to use
		int GetLocalTime()
		{
			// Get our current time
			auto CurTime = time(0);
			// Implement timezone transition
			auto* TimeInfo = localtime(&CurTime);
			
			// Dispatch timestamp we will return
			switch (T)
			{
			case TS_HOURS: return TimeInfo->tm_hour;
			case TS_MINUTES: return TimeInfo->tm_min;
			case TS_SECONDS: return TimeInfo->tm_sec;
			}
		}

		// std::string GetGMTTime() implementation.
		std::string GetGMTTime()
		{
			// Get our current time
			auto CurTime = time(0);
			// Implement timezone transition
			auto* TimeInfo = gmtime(&CurTime);
			auto* Time = asctime(TimeInfo);

			if (!Time) // Check if we have a NULL string
				return std::string("");

			return Time;
		}

		// int GetGMTTime() implementation.
		template <ETimeStamp T = TS_HOURS> // Select timestamp we want to use
		int GetGMTTime()
		{
			// Get our current time
			auto CurTime = time(0);
			// Implement timezone transition
			auto* TimeInfo = gmtime(&CurTime);

			// Dispatch timestamp we will return
			switch (T)
			{
			case TS_HOURS: return TimeInfo->tm_hour;
			case TS_MINUTES: return TimeInfo->tm_min;
			case TS_SECONDS: return TimeInfo->tm_sec;
			}
		}
	}

	/*
	* Key utilities such as keybinds, key states etc...
	*/
	namespace INP
	{
		// Define m_Binds
		std::unordered_map<std::uint32_t, std::function<void()>> m_Binds;
	}
}

namespace G
{
	// Define m_LocalTime
	int m_LocalTime;

	// Define m_GMTTime
	int m_GMTTime;

	// Define m_LocalTimeString
	std::string m_LocalTimeString;

	// Define m_GMTTimeString
	std::string m_GMTTimeString;

	// Define m_BuildTime
	std::string m_BuildTime;

	// Define m_CurrentProcess
	WNDPROC m_CurrentProcess;

	// Define m_CurrentWindow
	HWND m_CurrentWindow;

	// Define m_Direct3Device
	IDirect3DDevice9* m_Direct3Device;

	// Define m_UserName
	std::string m_UserName;

	void Init()
	{
		G::m_BuildTime = __DATE__;

		auto CP = D3DDEVICE_CREATION_PARAMETERS();
		G::m_CurrentWindow = CP.hFocusWindow;
		// Check if we actually initialized our device in I
		//	so we can just "copy-paste" it
#ifdef DEBUG
		assert(I::m_pDevice != NULL);
#else
		if (!I::m_pDevice)
			L::LogEvent(XOR("'Globals_Init()': Initialized G::m_Direct3Device before I::m_pDevice"), true); return;
#endif
		G::m_Direct3Device = I::m_pDevice;
		G::m_SystemEnv = std::getenv("SystemDrive");
		G::m_UserName = "r3pzz";

		U::INP::m_Binds[FNV("Menu toggle")] = []() {
			GUI::m_bIsOpened = !GUI::m_bIsOpened;
		};
	}
}