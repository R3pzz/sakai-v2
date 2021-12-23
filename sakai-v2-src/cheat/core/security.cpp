#include "security.h"

namespace sec
{
	// fnv_main() implementation
	std::uint32_t
	fnv_main(
		std::string string
		)
	{
		// Output hash buffer with basis
		std::uint32_t hash = 2166136261U;

		// Iterate through all symbols of given string
		for (auto it = 0; it != string.length(); it++)
		{
			// Hash times prime
			hash *= fnv_prime;

			// XOR hash with symbol
			hash ^= string[it];
		}

		return hash;
	}

	// random() implementation
	template <e_random T> // Select symbol type
	void*
	random()
	{
		// Init pseudo-random symbol generator (time-based)
		srand(time(0));
		
		// Dispatch symbol type
		switch (T)
		{
		case RT_INT: return rand() % 10;
		case RT_CHAR: return 'a' + rand() % 26;
		case RT_UNSIGNED: return reinterpret_cast<uint32_t>(rand() % 10);
		default: return rand() % 10;
		}
	}

	// GetHWID() implementation
	std::string
	get_hwid()
	{
		// Init hardware info buffer
		HW_PROFILE_INFO info;

		// Get hardware information. If we fail return empty string
		auto succeed = GetCurrentHwProfile(&info);
		if (!succeed) // Check for failure
			return "";

		// Return profile GUID (same as HWID)
		return info.szHwProfileGuid;
	}
}

namespace G {
	// Define m_SystemEnv
	char* sys_env = std::getenv("SystemDrive");
}