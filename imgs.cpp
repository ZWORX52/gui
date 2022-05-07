// NOLINT(legal/copyright)
#include "./main.hpp"
// Please don't use this
// This is a mess. :(

// Might eventually make this into a vector of chars or something.
// Would need to change the encoding. MAYBE vec<vec<char>> later?
std::vector<std::vector<bool>> image;

ImVec2 images_grid_pos;
ImVec2 images_mouse_pos;
ImVec2 images_grid_size;
ImVec2 images_disp_size;

ImVec2 Images::GetCoordsAtMouse() {
        ImVec2 v = (images_mouse_pos - images_grid_pos) / images_grid_size;
        return Utils::v_abs(ImVec2(static_cast<int>(v.x), static_cast<int>(v.y)));
}

std::vector<bool>::reference Images::GetAt(ImVec2 pos) { return image[pos.y][pos.x]; }

void Images::Display() {
        // Uses draw list to put images on the screen.
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        for (size_t i = 0; i < image.size(); i++) {
                for (size_t j = 0; j < image[i].size(); j++) {
                        ImVec2 square_start = images_grid_pos + ImVec2(images_grid_size.x * j, images_grid_size.y * i);
                        draw_list->AddRectFilled(square_start, square_start + images_disp_size,
                                        image[i][j] ? ImColor(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)) :
                                        ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)));
                }
        }
        ImGui::SetCursorScreenPos(ImVec2(images_grid_pos.x, images_grid_pos.y + image.size() * images_disp_size.y + 4));
}

void Images::UpdateWindow(bool *open) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_AlwaysAutoResize;

        ImGuiIO &io = ImGui::GetIO();

        ImGui::Begin("Images", open, flags);

        int images_disp_size_x = static_cast<int>(images_disp_size.x);
        int images_disp_size_y = static_cast<int>(images_disp_size.y);

        ImGui::SliderInt("Size (x)", &images_disp_size_x, 1, 20);
        ImGui::SliderInt("Size (y)", &images_disp_size_y, 1, 20);

        images_disp_size.x = images_disp_size_x; images_disp_size.y = images_disp_size_y;

        images_grid_pos = ImGui::GetCursorScreenPos();
        images_mouse_pos = io.MousePos;
        if (ImGui::IsMouseDown(0))
                Images::GetAt(Images::GetCoordsAtMouse()) = true;
        else if (ImGui::IsMouseDown(1))
                Images::GetAt(Images::GetCoordsAtMouse()) = false;
        Images::Display();

        ImGui::End();
}

