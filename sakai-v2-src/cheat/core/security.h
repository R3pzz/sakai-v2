#pragma once

// Include std::string
#include <string>
// Include anti-debug system
#include "../../externs/antidbg/antidbg.h"

#ifdef _DEBUG
#define FNV(s) sec::fnv_main(s)
#define XOR(s) s
#define WXOR(s) s
#else
#define FNV(s) sec::fnv_main(s)
#define XOR(s) sec::xor_obf(s).get_org()
#define WXOR(s) sec::wide_xor_obf(s).get_org()
#endif

/*
* Utils for securing your .dll.
* @Anti-debug: https://github.com/HackOvert/AntiDBG/tree/master/antidbg.
*/
namespace sec
{
	/*
	* Anti-debug check implementation.
	*/
	namespace adbg
	{
		// Check for debugging
		__forceinline
		bool
		check()
		{
#ifdef _DEBUG
			return false;
#else
			if (adbg_BeingDebuggedPEB())
				return true;

			if (adbg_CheckRemoteDebuggerPresent())
				return true;

			if (adbg_CheckWindowClassName())
				return true;

			if (adbg_CheckWindowName())
				return true;

			if (adbg_ProcessFileName())
				return true;

			if (adbg_IsDebuggerPresent())
				return true;

			if (adbg_NtGlobalFlagPEB())
				return true;

			if (adbg_NtQueryInformationProcess())
				return true;

			if (adbg_NtSetInformationThread())
				return true;

			if (adbg_HardwareDebugRegisters())
				return true;

			if (adbg_MovSS())
				return true;

			if (adbg_RDTSC())
				return true;

			if (adbg_QueryPerformanceCounter())
				return true;

			if (adbg_GetTickCount())
				return true;

			if (adbg_CloseHandleException())
				return true;

			if (adbg_SingleStepException())
				return true;

			if (adbg_Int3())
				return true;

			if (adbg_Int2D())
				return true;

			if (adbg_PrefixHop())
				return true;

			adbg_CrashOllyDbg();

			return false;
#endif
		}
	}

	// Prime used for FNV hashing
	constexpr std::uint64_t fnv_prime = 0x811C9DC5;

	// Seed for xor hasing
	constexpr std::uint64_t xor_seed = 0x811C9DC5 / 100 * static_cast<int>(__TIME__[6]);

	/*
	* XOR string implemenation.
	* @This is used for encrypting strings so wee can't see what is actually written.
	* @Constructor of xor_obf xores string symbol with prime seed.
	*	get_org() function does the same thing but with encryped buffer.
	*/
	struct xor_obf
	{
		// Constructor encrypts the string
		xor_obf(
			std::string string
			)
		{
			// Iterate through all string symbols
			for (auto it = 0; it != string.length(); it++)
			{
				// XOR current symbol with seed
				encbuf[it] = string[it] ^ xor_seed;
			}
		}

		// get_org() decrypts the string
		__forceinline
		std::string
		get_org()
		{
			// Create a buffer to store string
			std::string buf;

			// Iterate through all string symbols
			for (auto it = 0; it != encbuf.length(); it++)
			{
				// XOR encrypted symbol with seed
				buf[it] = encbuf[it] ^ xor_seed;
			}

			return buf;
		}

		// Encrypted string buffer
		std::string encbuf;
	};
	
	struct wide_xor_obf
	{
		wide_xor_obf(
			std::wstring wstring
			)
		{
			for (auto it = 0; it != wstring.length(); it++)
			{
				encbuf[it] = wstring[it] ^ xor_seed;
			}
		}

		__forceinline
		std::string
		get_org()
		{
			std::string buf;

			for (auto it = 0; it != encbuf.length(); it++)
			{
				buf[it] = encbuf[it] ^ xor_seed;
			}

			return buf;
		}

		std::string encbuf;
	};

	/*
	* FNV hasher.
	* @FNV hash is one of the fastest ways to hash the string.
	*/
	std::uint32_t
	fnv_main(
		std::string string
		);

	/*
	* Get PC/Laptop HWID (hardware ID).
	*/
	std::string
	get_hwid();

	/*
	* Random symbol generator.
	* @This is a simple srand() random T generator.
	*/

	// Symbol type
	enum e_random {
		RT_INT,
		RT_CHAR,
		RT_UNSIGNED
	};

	// Random T generator
	template <e_random T = e_random::RT_CHAR>
	void*
	random();
}

namespace G {
	// System directory/enviroment
	extern char* sys_env;
}