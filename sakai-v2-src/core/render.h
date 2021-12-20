#pragma once
// Common includes
#include "../includes.h"
// Include ImGui
#include "../dependencies/imgui/imgui.h"
// Include ImGui font rasterizer
#include "../dependencies/imgui/imgui_freetype.h"
// Include ImGui DirectX framework
#include "../dependencies/imgui/imgui_impl_dx9.h"
// Include ImGui Win32 framework
#include "../dependencies/imgui/imgui_impl_win32.h"

/*
* Utilities used for rendering.
*/
namespace RENDER {

	/*
	* ImGui wrappers.
	*/
	namespace IM {

		/*
		* Calculate text size based on font.
		*/
		FORCEINLINE ImVec2 GetTextSize(std::string_view Text, const ImFont* Font) {

			// Check if the text is empty or font size is 0.f so we don't waste time on calculus
			if (Text.empty()
				|| Font->FontSize == 0)
				return ImVec2(0.f, 0.f); // Return empty vector

			// ImGui text size calculator
			return Font->CalcTextSizeA(Font->FontSize, FLT_MAX, 0.f, Text.data());
		}

		/*
		* Font flags for font renderer.
		*/
		enum EFontFlags {
			FF_NONE			 = 0x1,
			FF_CENTERED_X	 = 0x2,
			FF_CENTERED_Y	 = 0x4,
			FF_DROPSHADOW	 = 0x8,
			FF_OUTLINE		 = 0xF
		};

		/*
		* Here are mostly wrappers to make render procedure easier.
		* @Name of functions is exactly what they'll render.
		*/
		void RenderRectangle(ImVec2& mins, ImVec2& maxs, bool fill = false, ImU32 col = 0x000000, float round = 0.f, ImDrawFlags flags = 0, float thickness = 1.f);
		void RenderCircle(ImVec2& Pos, float Radius, bool Fill, ImU32 Color, float Thickness, float nSegments);
		void RenderTriangle(const ImVec2& Point1, const ImVec2& Point2, const ImVec2& Point3, ImU32 Color, float Thickness, bool Fill);
		void RenderTriangle(const ImVec2 Points[3], ImU32 Color, float Thickness, bool Fill);
		void RenderNgon(const ImVec2& Center, float Radius, ImU32 Color, int nVerts, float Thickness, bool Fill);
		void RenderText(const char* Text, ImVec2& Pos, ImU32 Color, const ImFont* Font, float FontSize = 14.f, EFontFlags Flags = FF_NONE);

		/*
		* Map of fonts we'll be using.
		* @Usage: m_Fonts[FNV("*YourFontName*")]
		*/
		extern std::unordered_map<uint32_t, ImFont*> m_Fonts;
	}

	/*
	* Here are ImGui "hooking" functions.
	* Basically all they do is just replace ImGui draw list with our own.
	*/

	// Init our render list
	void Init();

	// Swap lists
	void Begin();

	// Draw scheduled objects
	void Draw();

	// Flush the draw list
	void Flush();

	// Current ImGui draw list we are adding items to
	extern std::shared_ptr<ImDrawList> m_CurrentList;

	// ImGui draw list we will be relacing with
	extern std::shared_ptr<ImDrawList> m_DrawingList;

	// ImGui draw list which we will replace
	extern std::shared_ptr<ImDrawList> m_ReplaceList;

	// Mutex to avoid race-conditional "bug". Yeah ik I am a bit retarder by calling this thing a race-conditional bug :poggers:
	extern std::mutex m_Mutex;
}