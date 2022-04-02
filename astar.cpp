#include "main.hpp"

void AStar::UpdateWindow(bool *open) {
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	flags |= ImGuiWindowFlags_NoDecoration;
	flags |= ImGuiWindowFlags_NoMove;
	flags |= ImGuiWindowFlags_NoResize;

	const ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);

	ImGui::Begin("AStar", open, flags);

	static float size = 10.0f;
	static ImVec4 colf = ImVec4(1.0f, 0.4f, 0.0f, 1.0f);

	ImGui::ColorEdit4("Color", &colf.x);
	ImGui::DragFloat("Size", &size, 1.0f, 1.0f, 1000.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

	if (ImGui::Button("Close"))
		*open = false;

	ImDrawList *draw_list = ImGui::GetWindowDrawList();

	const ImVec2 pos = ImGui::GetCursorScreenPos();
	const ImU32 col = ImColor(colf);

	draw_list->AddRectFilled(pos, ImVec2(pos.x + size, pos.y + size), col);

	ImGui::End();
}

