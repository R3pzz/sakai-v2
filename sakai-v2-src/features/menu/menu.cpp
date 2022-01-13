#include "menu.h"
// Include input, security and render system
#include "../../utils.h"
// Include config system
#include "../../additional/config.h"

namespace GUI
{
	void Show()
	{
		if (!m_bIsOpened)
			return;

		U::INP::m_InputBlocked = true;

		auto& IO = *R::m_pIO;

		if (ImGui::Begin("Sakai-V2.dll", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse))
		{
			if (ImGui::BeginTabBar("##main", ImGuiTabBarFlags_NoTooltip | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton))
			{
				if (ImGui::BeginTabItem("Rage"))
				{
					m_iTab = 0;
					RenderRagebot();
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Visuals"))
				{
					m_iTab = 1;
					RenderVisuals();
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Misc"))
				{
					m_iTab = 2;
					RenderMisc();
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Config"))
				{
					m_iTab = 3;
					RenderConfig();
					ImGui::EndTabItem();
				}
			}
		}
	}

	void Style()
	{
		auto& Style = ImGui::GetStyle();

		Style.WindowRounding = 2.f;
		Style.ChildRounding = 1.f;
		Style.ChildBorderSize = 1;
		Style.ColorButtonPosition = ImGuiDir_Left;
		Style.DisplayWindowPadding.x = 8.f;
		Style.DisplayWindowPadding.y = 8.f;
		Style.WindowMinSize = ImVec2{ 750, 600 };
	}

	void RenderRagebot()
	{

	}

	void RenderVisuals()
	{
		ImGui::BeginChild("##main", { ImGui::GetWindowSize().x / 3.f, ImGui::GetWindowSize().y }, true, ImGuiWindowFlags_HorizontalScrollbar );
		ImGui::Checkbox("Enable chams", &g_pConfig->m_Chams_Enabled);
	}

	void RenderMisc()
	{

	}

	void RenderConfig()
	{

	}
}