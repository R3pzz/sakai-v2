#pragma once
// Include stdlib
#include "../../includes.h"
// Include Minhook lib
#include "../../dependencies/minhook/MinHook.h"
// Include sdk types
#include "../../sdk.h"

class CHook
{
public:
	CHook() { }

	CHook(void* TargetFn) : m_pTargetFn(TargetFn) {}

public:
	FORCEINLINE bool Setup(void* TargetFn, void* ReplaceFn)
	{
		if (!TargetFn || !ReplaceFn)
			return false;

		m_pTargetFn = TargetFn;
		m_pReplaceFn = ReplaceFn;

		if (MH_CreateHook(m_pTargetFn, m_pReplaceFn, &m_pOriginal) != MH_OK)
		{
			L::PushFontColor(L::EConsoleColor::CONSOLE_TEXT_RED);
			L::LogEvent(XOR("[CHook::Setup()] Failed to setup hook!"), true);
			L::PopFontColor();
			return false;
		}

		return true;
	}

	FORCEINLINE bool Enable()
	{
		if (!m_pTargetFn)
			return false;

		if (MH_EnableHook(m_pTargetFn) != MH_OK)
		{
			L::PushFontColor(L::EConsoleColor::CONSOLE_TEXT_RED);
			L::LogEvent(XOR("[CHook::Setup()] Failed to enable hook!"), true);
			L::PopFontColor();
			return false;
		}

		return true;
	}

	FORCEINLINE bool Disable()
	{
		if (MH_DisableHook(m_pTargetFn) != MH_OK)
		{
			L::PushFontColor(L::EConsoleColor::CONSOLE_TEXT_RED);
			L::LogEvent(XOR("[CHook::Setup()] Failed to disable hook!"), true);
			L::PopFontColor();
			return false;
		}

		return true;
	}

	FORCEINLINE bool Remove()
	{
		if (!Disable())
			return false;

		if (MH_RemoveHook(m_pTargetFn) != MH_OK)
		{
			L::PushFontColor(L::EConsoleColor::CONSOLE_TEXT_RED);
			L::LogEvent(XOR("[CHook::Setup()] Failed to disable hook!"), true);
			L::PopFontColor();
			return false;
		}

		return true;
	}

	template <typename T>
	FORCEINLINE T GetOriginal() { return reinterpret_cast<T>(m_pOriginal); }

private:
	// Pointer to function we want to replace
	void* m_pTargetFn = NULL;
	// Pointer to a function with which we'll replace
	void* m_pReplaceFn = NULL;
	// Pointer to an original function
	void* m_pOriginal = NULL;
};

/*
* Cheat's hooking library.
*/
namespace H
{
	/*
	* Setup all hooks and activate them.
	*/
	bool Init();

	/*
	* Remove all hooks.
	*/
	bool Shutdown();

	/*
	* Here are functions to replace with.
	*/
	namespace FN
	{
#pragma region fn_model_render
		using DrawModelExecuteFn = void(__thiscall*)(void*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t&, CMatrix3x4*);
		// Detour for IVModelRender::DrawModelExecute()
		void __fastcall DrawModelExecute(void* Thisptr,
			IMatRenderContext* Context,
			const DrawModelState_t& State,
			const ModelRenderInfo_t& Info,
			CMatrix3x4* CustomBoneToWorld);
#pragma endregion

#pragma region fn_d3device
		using D3DevicePresentFn = HRESULT(__stdcall*)(void*, const RECT*, const RECT*, HWND, const RGNDATA*);
		// Detour for IDirect3DDevice9::Present()
		HRESULT __stdcall Present( void* _thisptr,
			const RECT* SourceRect,
			const RECT* DestRect,
			HWND DestWindow,
			const RGNDATA* DirtyRegion);

		using D3DeviceResetFn = HRESULT(__stdcall*)(void*, D3DPRESENT_PARAMETERS*);
		// Detour for IDirect3DDevice9::Reset()
		HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* Params);
#pragma endregion
	}

	namespace HK
	{
#pragma region hook_d3device
		inline CHook m_hD3DevicePresent;
		inline CHook m_hD3DeviceReset;
#pragma endregion
		inline CHook m_hDrawModelExecute;
	}
}