#include "origins.hpp"

bool show_load_window = false;
bool show_save_window = false;
bool show_save_as_window = false;
bool show_new_window = false;

StringField::StringField(std::string name, std::string val) {
	this->name = name;
	this->val = val;
}

BoolField::BoolField(std::string name, bool val) {
	this->name = name;
	this->val = val;
}

IntField::IntField(std::string name, int val) {
	this->name = name;
	this->val = val;
}

void Origins::UpdateLoadWindow(bool *open) {
	return;
}

void Origins::UpdateWindow(bool *open) {
	ImGuiWindowFlags WindowFlags = 0;
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

	ImGui::Text("Currently made datapacks: (click one to load)");

	ImGui::End();
}

