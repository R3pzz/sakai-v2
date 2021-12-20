#include "../utils.h"

namespace RENDER {
	namespace IM {

		// RenderRectangle() implementation
		void RenderRectangle(ImVec2& Mins, ImVec2& Maxs, bool Fill, ImU32 Color, float Round, ImDrawFlags Flags, float Thickness) {
			Fill ? m_CurrentList->AddRectFilled(Mins, Maxs, Color, Round, Flags) : m_CurrentList->AddRect(Mins, Maxs, Color, Round, Flags, Thickness);
		}

		// RenderReRenderCirclectangle() implementation
		void RenderCircle(ImVec2& Pos, float Radius, bool Fill, ImU32 Color, float Thickness, float nSegments) {
			Fill ? m_CurrentList->AddCircleFilled(Pos, Radius, Color, nSegments) : m_CurrentList->AddCircle(Pos, Radius, Color, nSegments, Thickness);
		}

		// RenderTriangle() implementation
		void RenderTriangle(const ImVec2& Point1, const ImVec2& Point2, const ImVec2& Point3, ImU32 Color, float Thickness, bool Fill) {
			Fill ? m_CurrentList->AddTriangleFilled(Point1, Point2, Point3, Color) : m_CurrentList->AddTriangle(Point1, Point2, Point3, Color, Thickness);
		}

		// RenderTriangle() by points array implementation
		void RenderTriangle(const ImVec2 Points[3], ImU32 Color, float Thickness, bool Fill) {
			return RenderTriangle(Points[1], Points[2], Points[3], Color, Thickness, Fill);
		}

		// RenderNgon() implementation
		void RenderNgon(const ImVec2& Center, float Radius, ImU32 Color, int nVerts, float Thickness, bool Fill) {
			Fill ? m_CurrentList->AddNgonFilled(Center, Radius, Color, nVerts) : m_CurrentList->AddNgon(Center, Radius, Color, nVerts, Thickness);
		}

		// RenderText() implementation
		void RenderText(const char* Text, ImVec2& Pos, ImU32 Color, const ImFont* Font, float FontSize, EFontFlags Flags) {

			// Come up with shade color
			const ImVec4& ShadeCol = ImVec4(0, 0, 0, ImGui::ColorConvertU32ToFloat4(Color).w - 100.f);
			const ImU32 ShadeColU32 = ImGui::ColorConvertFloat4ToU32(ShadeCol);

			// Dispatch font render flags
			if (Flags & FF_CENTERED_X)
				Pos.x -= GetTextSize(Text, Font).x / 2.f; // Center horizontally

			if (Flags & FF_CENTERED_Y)
				Pos.y -= GetTextSize(Text, Font).y / 2.f; // Center vertically

			if (Flags & FF_DROPSHADOW) {
				m_CurrentList->AddText(Font, FontSize, Pos, Color, Text);

				// Add drop shadow
				m_CurrentList->AddText(Font, FontSize, ImVec2(Pos.x - 2, Pos.y), ShadeColU32, Text);
			} else if (Flags & FF_OUTLINE) {

				m_CurrentList->AddText(Font, FontSize, ImVec2(Pos.x + 1, Pos.y + 1), ShadeColU32, Text);
				m_CurrentList->AddText(Font, FontSize, ImVec2(Pos.x - 1, Pos.y - 1), ShadeColU32, Text);
				m_CurrentList->AddText(Font, FontSize, ImVec2(Pos.x + 1, Pos.y - 1), ShadeColU32, Text);
				m_CurrentList->AddText(Font, FontSize, ImVec2(Pos.x - 1, Pos.y + 1), ShadeColU32, Text);

			} else if (Flags & FF_NONE){
				m_CurrentList->AddText(Font, FontSize, Pos, Color, Text);
			}
		}

		std::unordered_map<uint32_t, ImFont*> m_Fonts;
	}

	// Init() implementation
	void Init() {

		// Create ImGui context (basically launch ImGui)
		ImGui::CreateContext();

		// Set up frameworks
		ImGui_ImplDX9_Init(G::m_Direct3Device);
		ImGui_ImplWin32_Init(G::m_CurrentWindow);

		// Get ImGui IO (probably ImGui settings etc...)
		auto& IO = ImGui::GetIO();
		// Get ImGui style parameters
		auto& Style = ImGui::GetStyle();

		// Get font directory
		const char* SegoeDir = strcat(G::m_SystemEnv, "\\Windows\\System32\\Fonts\\SegoeUI.ttf");

		// Setup font
		ImFontConfig Config;
		Config.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint;

		// Append fonts
		IM::m_Fonts[FNV("segoe_14")] = IO.Fonts->AddFontFromFileTTF(SegoeDir, 14.f, &Config);
	}

	// Begin() implementation
	void Begin() {
		
		// Flush current draw list
		m_CurrentList->Clear();
		m_CurrentList->PushClipRectFullScreen();

		// Swap lists
		m_Mutex.lock();

		*m_ReplaceList = *m_CurrentList;

		m_Mutex.unlock();
	}

	// Draw() implementation
	void Draw() {

		// Replace active ImGui list with our list
		if (m_Mutex.try_lock()) {
			*m_DrawingList = *m_ReplaceList;

			m_Mutex.unlock();
		}

		*ImGui::GetBackgroundDrawList() = *m_DrawingList;
	}

	// Cleanup() implementation
	void Cleanup() {
		m_CurrentList->Clear();

		m_Mutex.lock();

		*m_ReplaceList = *m_CurrentList;

		m_Mutex.unlock();
	}

	// Define m_CurrentList
	std::shared_ptr<ImDrawList> m_CurrentList;

	// Define m_DrawingList
	std::shared_ptr<ImDrawList> m_DrawingList;

	// Define m_ReplaceList
	std::shared_ptr<ImDrawList> m_ReplaceList;

	// Define m_Mutex
	std::mutex m_Mutex;
}