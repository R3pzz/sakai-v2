#pragma once
// Include stdlib
#include "../platform.h"

using GetSymbolProcFn = bool(__cdecl*)(const char*);

class CKeyValues
{
public:
	CALL_SIG(Init(const char* Key),
		"client.dll", "55 8B EC 51 33 C0 C7 45",
		void(__thiscall*)(void*, const char*), Key);

	CALL_SIG(FromBuffer(const char* ResourceName, const char* Buf, void* FileSys = NULL, const char* PathId = NULL, void* Unk1 = NULL, void* Unk2 = NULL),
		"client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89",
		void(__thiscall*)(void*, const char*, const char*, void*, const char*, void*, void*), ResourceName, Buf, FileSys, PathId, Unk1, Unk2);

	CALL_SIG(FindKey(const char* Name, bool Create),
		"client.dll", "55 8B EC 83 EC 1C 53 8B D9 85 DB",
		CKeyValues* (__thiscall*)(void*, const char*, bool), Name, Create);

	FORCEINLINE void SetInt(const char* Name, int Value)
	{
		const auto Key = FindKey(Name, true);
		if (!Key)
			return;

		*reinterpret_cast<char*>(reinterpret_cast<std::uintptr_t>(Key) + 0x10) = 2;
		*reinterpret_cast<int*>(reinterpret_cast<std::uintptr_t>(Key) + 0xC) = Value;
	}

	FORCEINLINE void set_string(const char* Name, const char* Value)
	{
		auto Key = FindKey(Name, true);
		if (!Key)
			return;

		static auto Fn = SIG("client.dll", "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01").Get<void(__thiscall*)(void*, const char*)>();

		Fn(Key, Value);
	}

private:
	pad_t			_0[0x4];
	char*			m_szValue;
	wchar_t*		m_wszValue;
	int				m_iValue;
	float			m_flValue;
	void*			m_pValue;
	Color4_t		m_iColor[4];
	char			m_iType;
	bool			m_bHasEscapeSequences;
	std::uint16_t	m_iKeyNameCaseSensitive;
	CKeyValues*		m_pPeer;
	CKeyValues*		m_pSub;
	CKeyValues*		m_pChain;
	GetSymbolProcFn	m_pExpressionGetSymbolProc;
};