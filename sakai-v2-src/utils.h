#pragma once

// Localise everything in one header...

#include "includes.h"
// Include global cheat vars
#include "core/globals.h"
// Include Helpers
#include "core/helpers.h"
// Include Logging system
#include "core/logs.h"
// Include math stuff
#include "core/math.h"
// Include Memory system
#include "core/memory.h"
// Include Network system
#include "core/network.h"
// Include Renderer
#include "core/render.h"
// Include Security system
#include "core/security.h"

/*
* Utils which did not get class-specified.
*/
namespace U {

	/*
	* Swap encodings through multibyte and ANSI.
	* @UTF-8 stands for multibyte,
	*	ANSI stands for Unicode.
	*/

	// Swap to UTF-8
	FORCEINLINE std::string ToUTF8(std::wstring_view txt) {
		if (txt.empty()) // Check if our string is empty so we do not waste time
			return "";

		// Obtain out string size
		std::size_t Size = WideCharToMultiByte(CP_UTF8, 0, txt.data(), txt.size(), 0, 0, 0, 0);

		// Make an out string
		std::string Ret = std::string(Size, 0);

		// Swap to UTF-8
		WideCharToMultiByte(CP_UTF8, 0, txt.data(), txt.size(), Ret.data(), Size, 0, 0);

		return Ret;
	}

	// Swap to ANSI
	FORCEINLINE std::wstring ToANSI(std::string_view txt) {
		if (txt.empty()) // Check if our string is empty so we do not waste time
			return L"";

		// Obtain out string size
		std::size_t size = MultiByteToWideChar(CP_UTF8, 0, txt.data(), txt.size(), 0, 0);

		// Make an out string
		std::wstring ret = std::wstring(size, 0);

		// Swap to UTF-8
		MultiByteToWideChar(CP_UTF8, 0, txt.data(), txt.size(), ret.data(), size);

		return ret;
	}

	/*
	* Time utilities.
	* @this is I think the most easy way to implement
	*	getting time and date.
	*/
	namespace DATE {

		/*
		* Time stamp type:
		*	hours, minutes, seconds.
		*/
		enum ETimeStamp {
			TS_HOURS,
			TS_MINUTES,
			TS_SECONDS,
		};

		/*
		* Gets local time.
		* Type: std::string.
		*/
		std::string GetLocalTime();

		/*
		* Gets local time.
		* Type: int.
		*/
		template <ETimeStamp T = TS_HOURS>
		int GetLocalTime();

		/*
		* Gets GMT time.
		* Type: std::string.
		*/
		std::string GetGMTTime();

		/*
		* Gets GMT time.
		* Type: int.
		*/
		template <ETimeStamp T = TS_HOURS>
		int GetGMTTime();
	}

	namespace INP {

		/*
		* Key state to check behaviour
		*/
		enum EKeyState {
			KS_PRESSED,
			KS_HOLDED,
			KS_AWAY,
		};

		// Should we activate the mouse pointer?
		inline bool m_InputBlocked = false;

		// Map of binds corresponding to functions
		extern std::unordered_map<std::uint32_t, void*> m_Binds;

		/*
		* Gets key state by activation type.
		*/
		template <EKeyState T = KS_PRESSED>
		bool GetKeyState(std::int16_t key);
	}
}

/*
* Global cheat variables to store them in one place.
* @They can be inlined but leave it like that for now.
*/
namespace G {

	// Here we will store our local time as integer
	extern int m_LocalTime;

	// Here we will store our GMT-based time
	extern int m_GMTTime;

	// Same as m_LocalTime but written as a string
	extern std::string m_LocalTimeString;

	// Same as m_GMTTime but written as a string
	extern std::string m_GMTTimeString;

	// Here is the .dll build time. Stored as HH:MM:SS
	extern std::string m_BuildTime;

	// Here is the process we are attached (should be the CS:GO process)
	extern WNDPROC m_CurrentProcess;

	// Here is our current focused window
	extern HWND m_CurrentWindow;

	// We need to store the CS:GO's DirectX device to paint on CS' window
	extern IDirect3DDevice9* m_Direct3Device;

	// Current player username
	extern std::string m_UserName;
}