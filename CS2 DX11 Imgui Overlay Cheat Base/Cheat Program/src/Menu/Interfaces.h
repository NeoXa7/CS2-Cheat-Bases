#pragma once
#include <ImGui/imgui.h>
#include <Menu/ImGuiCustomElements.h> 
#include <Globals/hGlobals.h>


void RenderMenu()
{
	ImGui::SetNextWindowSizeConstraints(ImVec2(400, 450), ImVec2(1366, 768));
	C_Elements::CustomizeMenuTitleBar();
	ImGui::Begin("Overlay Menu");
	
	if (ImGui::BeginTabBar("Cheats Type"))
	{
		if (ImGui::BeginTabItem("Skills"))
		{
			C_Elements::LeaveLine();
			C_Elements::Checkbox("Checkbox1", &Flags::checkBox1);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Visuals"))
		{
			C_Elements::LeaveLine();
			C_Elements::Checkbox("Checkbox2", &Flags::checkBox2);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();
}

