#pragma once

// Include std::string
#include "../includes.h"
// Include anti-debug system
#include "../dependencies/antidbg/antidbg.h"

#ifdef _DEBUG
#define FNV(s) SEC::FnvHash(s)
#define XOR(s) s
#define WXOR(s) s
#else
#define FNV(s) SEC::FnvHash(s)
#define XOR(s) SEC::Xor_t(s).Decrypt()
#define WXOR(s) SEC::WXor_t(s).Decrypt()
#endif

/*
* Utils for securing your .dll.
* @Anti-debug: https://github.com/HackOvert/AntiDBG/tree/master/antidbg.
*/
namespace SEC
{
	/*
	* Anti-debug check implementation.
	*/
	namespace ADBG
	{
		// Check for debugging
		FORCEINLINE bool Check()
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
	constexpr std::uint64_t m_Prime = 0x811C9DC5;
	// Seed for xor hasing
	constexpr std::uint64_t m_XorSeed = 0x811C9DC5 / 100 * static_cast<int>(__TIME__[6]);

	/*
	* XOR string implemenation.
	* @This is used for encrypting strings so wee can't see what is actually written.
	* @Constructor of Xor_t xores string symbol with prime seed.
	*	Decrypt() function does the same thing but with encryped buffer.
	*/
	struct Xor_t
	{
		// Constructor encrypts the string
		Xor_t(std::string S)
		{
			// Iterate through all string symbols
			for (auto it = 0; it != S.length(); it++)
			{
				// XOR current symbol with seed
				m_Encrypted[it] = S[it] ^ m_XorSeed;
			}
		}

		// Decrypt() decrypts the string
		FORCEINLINE std::string Decrypt()
		{
			// Create a buffer to store string
			std::string Buffer;

			// Iterate through all string symbols
			for (auto it = 0; it != m_Encrypted.length(); it++)
			{
				// XOR encrypted symbol with seed
				Buffer[it] = m_Encrypted[it] ^ m_XorSeed;
			}

			return Buffer;
		}

		// Encrypted string buffer
		std::string m_Encrypted;
	};
	
	struct WXor_t
	{
		// Constructor encrypts the wstring
		WXor_t(std::wstring S)
		{
			// Iterate through all wstring symbols
			for (auto it = 0; it != S.length(); it++)
			{
				// XOR current symbol with seed
				m_Encrypted[it] = S[it] ^ m_XorSeed;
			}
		}

		// Decrypt() decrypts the wstring
		FORCEINLINE std::wstring Decrypt()
		{
			// Create a buffer to store wstring
			std::wstring Buffer;

			// Iterate through all wstring symbols
			for (auto it = 0; it != m_Encrypted.length(); it++)
			{
				// XOR encrypted symbol with seed
				Buffer[it] = m_Encrypted[it] ^ m_XorSeed;
			}

			return Buffer;
		}

		// Encrypted wstring buffer
		std::wstring m_Encrypted;
	};

	/*
	* FNV hasher.
	* @FNV hash is one of the fastest ways to hash the string.
	*/
	std::uint32_t FnvHash(std::string Text);

	/*
	* Get PC/Laptop HWID (hardware ID).
	*/
	std::string GetHWID();

	/*
	* Random symbol generator.
	* @This is a simple srand() random T generator.
	*/

	// Symbol type
	enum ERandType : int
	{
		RT_INT,
		RT_CHAR,
		RT_UNSIGNED
	};

	// Random T generator
	template <ERandType T = RT_CHAR>
	void* RandomT();
}

namespace G
{
	// System directory/enviroment
	extern char* m_SystemEnv;
}