#include "utils.h"

namespace U {
	namespace DATE {

		// std::string GetLocalTime() implementation.
		std::string GetLocalTime() {

			// Get our current time
			const std::int64_t CurTime = time(0);

			// Implement timezone transition
			const tm* TimeInfo = localtime(&CurTime);

			char* Time = asctime(TimeInfo);
			if (!Time) // Check if we have a NULL string
				return std::string("");

			return Time;
		}

		// int GetLocalTime() implementation.
		template <ETimeStamp T = TS_HOURS> // Select timestamp we want to use
		int GetLocalTime() {

			// Get our current time
			const std::int64_t CurTime = time(0);

			// Implement timezone transition
			const tm* TimeInfo = localtime(&CurTime);
			
			// Dispatch timestamp we will return
			switch (T) {
			case TS_HOURS: return TimeInfo->tm_hour;
			case TS_MINUTES: return TimeInfo->tm_min;
			case TS_SECONDS: return TimeInfo->tm_sec;
			}
		}

		// std::string GetGMTTime() implementation.
		std::string GetGMTTime() {

			// Get our current time
			const std::int64_t CurTime = time(0);

			// Implement timezone transition
			const tm* TimeInfo = gmtime(&CurTime);

			char* Time = asctime(TimeInfo);
			if (!Time) // Check if we have a NULL string
				return std::string("");

			return Time;
		}

		// int GetGMTTime() implementation.
		template <ETimeStamp T = TS_HOURS> // Select timestamp we want to use
		int GetGMTTime() {

			// Get our current time
			const std::int64_t CurTime = time(0);

			// Implement timezone transition
			const tm* TimeInfo = gmtime(&CurTime);

			// Dispatch timestamp we will return
			switch (T) {
			case TS_HOURS: return TimeInfo->tm_hour;
			case TS_MINUTES: return TimeInfo->tm_min;
			case TS_SECONDS: return TimeInfo->tm_sec;
			}
		}
	}

	/*
	* Key utilities such as keybinds, key states etc...
	*/
	namespace INP {

		// Define m_Binds
		std::unordered_map<std::uint32_t, void*> m_Binds;

		template <EKeyState T = KS_PRESSED> // Select key state to check key behaviour
		bool GetKeyState(std::int16_t Key) {

			// Get key state (not dispatched)
			SHORT State = GetAsyncKeyState(Key);

			// Dispatch key state
			switch (T) {
			case KS_PRESSED: return HIWORD(State);
			case KS_HOLDED: return LOWORD(State);
			case KS_AWAY: return !HIWORD(State);
			}

			// If we fail then return false
			return false;
		}
	}
}

namespace G {
	
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
}