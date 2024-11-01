#pragma once
#include <ImGui/imgui.h>
#include <Menu/Elements.hpp> 
#include <Globals/Globals.hpp>


void RenderMenu()
{
	ImGui::SetNextWindowSizeConstraints(ImVec2(400, 450), ImVec2(1366, 768));
	C_Elements::CustomizeMenuTitleBar();
	ImGui::Begin("Overlay Menu");

	if (ImGui::BeginTabBar("Cheats Type"))
	{
		if (ImGui::BeginTabItem("Visuals"))
		{
			C_Elements::LeaveLine();
			C_Elements::Checkbox("Enable Esp", &Flags::enableEsp);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();
}
