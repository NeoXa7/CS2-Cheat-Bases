#pragma once
#include <ImGui/imgui.h>
#include <Interface/Elements.hpp>

void RenderMenu__()
{
	ImGui::Begin("Test");
	ImGui::SetWindowSize(ImVec2(MIN_MENU_WIDTH, MIN_MENU_HEIGHT));
	ImGui::Text("Hello World");
	ImGui::End();
}