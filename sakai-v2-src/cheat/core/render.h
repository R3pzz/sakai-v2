#pragma once
// std::string_view
#include <string>
// std::unordered_map
#include <unordered_map>
// Include ImGui
#include "../../externs/imgui/imgui.h"
// Include ImGui font rasterizer
#include "../../externs/imgui/imgui_freetype.h"
// Include ImGui DirectX framework
#include "../../externs/imgui/imgui_impl_dx9.h"
// Include ImGui Win32 framework
#include "../../externs/imgui/imgui_impl_win32.h"
// Include vector3_t
#include "../../ingame/types/vector.h"

namespace render
{
	namespace imgui
	{
		/*calculate text size*/
		__forceinline ImVec2 text_size(std::string_view string, const ImFont* font)
		{
			// Check if the text is empty or font size is 0.f so we don't waste time on calculus
			if (string.empty()
				|| font->FontSize == 0)
				return ImVec2(0.f, 0.f); // Return empty vector

			// ImGui text size calculator
			return font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.f, string.data());
		}

		/*font flags*/
		enum e_ff
		{
			FF_NONE			 = 0x1,
			FF_CENTERED_X	 = 0x2,
			FF_CENTERED_Y	 = 0x4,
			FF_DROPSHADOW	 = 0x8,
			FF_OUTLINE		 = 0xF
		};

		/*add a simple rectangle*/
		void _cdecl draw_add_rect(
			vec2d_t& mins, vec2d_t& maxs,
			bool fill,
			uint32_t col,
			float round,
			int flags,
			float thickness
			);

		/*add a simple circle*/
		void _cdecl draw_add_circle(
			vec2d_t& pos,
			float rad,
			bool fill,
			uint32_t col,
			float thick,
			float seg
			);

		/*add a triangle by 3 pos*/
		void _cdecl draw_add_triangle(
			const vec2d_t& p1, const vec2d_t& p2, const vec2d_t& p3,
			uint32_t col,
			float thickness,
			bool fill
			);

		/*add a triangle by an array of pos*/
		void _cdecl draw_add_triangle(
			const vec2d_t pts[3],
			uint32_t col,
			float thick,
			bool fill
			);

		/*add a ngon*/
		void _cdecl draw_add_ngon(
			const ImVec2& center,
			float rad,
			uint32_t col,
			int verts,
			float thick,
			bool fill
			);

		/*add text with flags*/
		void _cdecl draw_add_text(
			const char* text,
			ImVec2& pos,
			ImU32 clr,
			const ImFont* font,
			float size,
			int flags = e_ff::FF_NONE
			);

		/*translate valve vector to imgui vector*/
		__forceinline ImVec2 pos_to_imvec(const vec2d_t& vec)
		{
			ImVec2 buf;
			buf.x = vec.x;
			buf.y = vec.y;
			return buf;
		}

		/*
		* Map of fonts we'll be using.
		* @Usage: m_Fonts[FNV("*YourFontName*")]
		*/
		extern std::unordered_map<uint32_t, ImFont*> fonts_map;
	}

	void _cdecl init_render_list(void);

	void _cdecl begin_render(void);

	void _cdecl draw_list(void);

	void _cdecl flush_list(void);

	/*variables for render only*/
	extern std::shared_ptr<ImDrawList> cur_list;

	extern std::shared_ptr<ImDrawList> drawing_list;

	extern std::shared_ptr<ImDrawList> repl_list;

	extern std::mutex draw_mutex;
}