#include "hooks.h"
// Include all features we have to hook them
#include "../chams/chams.h"
// Include menu for rendering
#include "../menu/menu.h"

namespace H
{
	bool Init()
	{
		if (MH_Initialize() != MH_OK)
		{
			L::PushFontColor(L::EConsoleColor::CONSOLE_TEXT_RED);
			L::LogEvent(XOR("[CHook::Setup()] Failed to initialize hook!"), true);
			L::PopFontColor();
			return false;
		}

		if (!HK::m_hDrawModelExecute.Setup(MEM::CallVirtual<FN::DrawModelExecuteFn>(I::m_pModelRender, 21U), &FN::DrawModelExecute))
			return false;

		if (!HK::m_hD3DevicePresent.Setup(MEM::CallVirtual<FN::D3DevicePresentFn>(I::m_pDevice, 17U), &FN::Present))
			return false;

		HK::m_hDrawModelExecute.Enable();

		HK::m_hD3DevicePresent.Enable();

		return true;
	}

	bool Shutdown()
	{
		if (!HK::m_hDrawModelExecute.Remove())
			return false;

		if (!HK::m_hD3DevicePresent.Remove())
			return false;

		return true;
	}

	namespace FN
	{
		void __fastcall DrawModelExecute(void* Thisptr,
			IMatRenderContext* Context,
			const DrawModelState_t& State,
			const ModelRenderInfo_t& Info,
			CMatrix3x4* CustomBoneToWorld)
		{
			static auto Original = HK::m_hDrawModelExecute.GetOriginal<::H::FN::DrawModelExecuteFn>();
			
			// Override model
			g_pChams->OnDME(Info);

			// Render original model
			Original(Thisptr, Context, State, Info, CustomBoneToWorld);

			// Override with null material to remove original model
			I::m_pModelRender->ForcedMaterialOverride(NULL, OVERRIDE_NORMAL);
		}

		HRESULT __stdcall Present(void* _thisptr,
			const RECT* SourceRect,
			const RECT* DestRect,
			HWND DestWindow,
			const RGNDATA* DirtyRegion)
		{
			static auto Original = HK::m_hD3DevicePresent.GetOriginal<::H::FN::D3DevicePresentFn>();

			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();

			ImGui::NewFrame();

			if (U::INP::GetKeyState(VK_HOME))
			{
				U::INP::m_Binds[FNV("Menu toggle")]();
			}

			GUI::Show();

			ImGui::EndFrame();
			ImGui::Render();

			return Original(_thisptr, SourceRect, DestRect, DestWindow, DirtyRegion);
		}
	}
}