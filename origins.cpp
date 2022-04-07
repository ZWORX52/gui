#include <iostream>
#include <fstream>
#include "origins.hpp"

/*
const char *OriginsData::PowerToString(int type, OriginsData::PowerMode mode) {
	std::string result;
	return result.c_str();
}
*/

void Origins::UpdateWindow(bool *open) {
	static bool show_load_window = false;
	static bool show_save_window = false;
	static bool show_save_as_window = false;
	static bool show_new_window = false;

	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_None;
	WindowFlags |= ImGuiWindowFlags_MenuBar;
	WindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::Begin("Origins datapacks", open, WindowFlags);

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			ImGui::MenuItem("Open...", NULL, &show_load_window);
			ImGui::MenuItem("Save...", NULL, &show_save_window);
			ImGui::MenuItem("Save as...", NULL, &show_save_as_window);
			ImGui::MenuItem("New...", NULL, &show_new_window);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("Currently loaded datapacks:");

	ImGui::Text("Undone!");

	ImGui::End();
}

