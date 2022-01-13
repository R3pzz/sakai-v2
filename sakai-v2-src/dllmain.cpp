#include "sdk.h"
// Include hooking library
#include "features/hooks/hooks.h"
// Include menu
#include "features/menu/menu.h"

DWORD APIENTRY Main(PVOID);
DWORD Shutdown();

BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(Module);

		if (auto Thread = CreateThread(0, 0, Main, Module, 0, 0))
		{
			CloseHandle(Thread);
			return TRUE;
		}
	}
	else if (Reason == DLL_PROCESS_DETACH)
	{
		return Reserved ? FALSE : Shutdown();
	}
}

DWORD APIENTRY Main(PVOID Module)
{
	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	} while (!GetModuleHandleA("serverbrowser.dll"));

	std::string HWID = SEC::GetHWID();
	std::ofstream HwidFile;

	if (!HwidFile.good())
		throw std::runtime_error(XOR("Unable to open HWID file!"));

	HwidFile.open(XOR("hwid.sc"));

#if (0)
	if (!SEC::ADBG::Check())
	{
		if (!HwidFile.is_open())
			throw std::runtime_error(XOR("Unable to open HWID file!"));
		
		HwidFile << XOR("HWID: ") << XOR(HWID.c_str()) << std::endl;
	}

	std::ifstream HwidIn;

	if (!HwidIn.good())
		throw std::runtime_error(XOR("Unable to open HWID file!"));

	HwidIn.open(XOR("hwid.sc"));

	std::string IsHWIDPresentStr;
	HwidIn >> IsHWIDPresentStr;
	if (IsHWIDPresentStr.find(std::string(XOR("HWID: ")) + HWID))
	{
		throw std::runtime_error(XOR("Banned for debugging!"));
	}
	
#endif

	HwidFile.close();

	// Register binds

	try {
		L::Init();
		// Initialize console
		HLP::InitConsole(XOR("Sakai DBG"));
		// Initialize interfaces
		I::Init();
		// Initialize globals
		G::Init();
		// Initialize render
		R::Init();
		// Stylize menu
		GUI::Style();
		// Initialize hooks
		H::Init();
	}
	catch (std::exception& except)
	{
		char Buf[256];
		std::sprintf(Buf, XOR("Exception thrown at %s"), except.what());
		L::LogEvent(Buf, true);
		delete[] Buf;
	}

	// Check if we want to unload our cheat
	while (!U::INP::GetKeyState<U::INP::EKeyState::KS_PRESSED>(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(Module), 0);
}

DWORD Shutdown() {
	return TRUE;
}