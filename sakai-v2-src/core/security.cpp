#include "security.h"

namespace SEC {

	// FnvHash() implementation
	std::uint32_t FnvHash(std::string Text) {

		// Output hash buffer with basis
		std::uint32_t Hash = 2166136261U;

		// Iterate through all symbols of given string
		for (auto it = 0; it != Text.length(); it++) {
			// Hash times prime
			Hash *= m_Prime;

			// XOR hash with symbol
			Hash ^= Text[it];
		}

		return Hash;
	}

	// RandomT() implementation
	template <ERandType T = RT_CHAR> // Select symbol type
	void* RandomT() {

		// Init pseudo-random symbol generator (time-based)
		srand(time(0));
		
		// Dispatch symbol type
		switch (T) {
		case RT_INT: return rand() % 10;
		case RT_CHAR: return 'a' + rand() % 26;
		case RT_UNSIGNED: return reinterpret_cast<uint32_t>(rand() % 10);
		default: return rand() % 10;
		}

		// If we fail we return zero to avoid runtime-errors
		return 0;
	}

	// GetHWID() implementation
	std::string GetHWID() {

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
	char* m_SystemEnv = getenv("SystemDrive");
}