// NOLINT(legal/copyright)
#include "./main.hpp"

namespace Images {

// Might eventually make this into a vector of chars or something.
// Would need to change the encoding. MAYBE vec<vec<char>> later?
// Not sure!
std::vector<std::vector<bool>> image;

char image_encoded[BUFFER_SIZE] = { 0 };

ImVec2 grid_pos          = ImVec2();
ImVec2 mouse_pos         = ImVec2();
ImVec2 disp_size_v       = ImVec2();
ImVec2 grid_size_v       = ImVec2();

int grid_width           = 30;
int grid_height          = 30;
int disp_size            = 10;

ImVec2 GetCoordsAtMouse() {
        ImVec2 v = (mouse_pos - grid_pos) / disp_size_v;
        return Utils::v_abs(ImVec2(static_cast<int>(v.x), static_cast<int>(v.y)));
}

bool InvalidPos(ImVec2 coords) {
        return coords.x < 0 || coords.x > grid_width || coords.y < 0 || coords.y > grid_width;
}

std::vector<bool>::reference GetAt(ImVec2 pos) { return image[pos.y][pos.x]; }

void Display() {
        // Uses draw list to put images on the screen.
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        for (size_t i = 0; i < image.size(); i++) {
                for (size_t j = 0; j < image[i].size(); j++) {
                        ImVec2 square_start = grid_pos + disp_size_v * ImVec2(j, i);
                        draw_list->AddRectFilled(square_start, square_start + disp_size_v,
                                        image[i][j] ? ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)) :
                                        ImColor(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)));
                }
        }
        ImGui::SetCursorScreenPos(ImVec2(grid_pos.x, grid_pos.y + grid_height * disp_size + 4));
}

void ClearImage() {
        for (size_t i = 0; i < image.size(); i++) {
                for (size_t j = 0; j < image[i].size(); j++) {
                        image[i][j] = false;
                }
        }
}

void Encode() { Encode(image_encoded); }
void Encode(char *buf) {
        // Encode the images_image into buf
        // For now just yeet the hex at buf
        Utils::ClearBuffer(buf);
        //static char hex_img[ARRAY_SIZE / 4] = { 0 };
        for (size_t i = 0; i < image.size(); i++) {
                for (size_t j = 0; j < image[i].size(); j++) {
                        buf[i * image[i].size() + j] = image[i][j] ? '1' : '0';
                }
        }
}

void UpdateWindow(bool *open) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_NoDecoration;
        flags |= ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoResize;

        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGuiIO &io = ImGui::GetIO();

        //static ImVec2 old_pos = ImVec2();
        static bool dragging_bit = false;

        disp_size_v = ImVec2(disp_size, disp_size);
        grid_size_v = ImVec2(grid_width, grid_height);

        ImGui::Begin("Images", open, flags);

        ImGui::SliderInt("Block size", &disp_size, 1, 20);

        ImGui::SliderInt("Grid width", &grid_width, 1, 100);
        ImGui::SliderInt("Grid height", &grid_height, 1, 100);

        if (ImGui::Button("Encode image")) {
                Encode();
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear image")) {
                ClearImage();
        }

        grid_pos = ImGui::GetCursorScreenPos();
        mouse_pos = io.MousePos;

        if (static_cast<size_t>(grid_height) != image.size()) {
                image.resize(grid_height, std::vector<bool>(grid_width, false));
        }
        if (static_cast<size_t>(grid_width) != image[0].size()) {
                for (size_t i = 0; i < image.size(); i++) {
                        image[i].resize(grid_width, false);
                }
        }

        ImVec2 mouse_coords = GetCoordsAtMouse();
        if (mouse_pos.x > grid_pos.x &&
            mouse_pos.x < grid_pos.x + grid_width * disp_size &&
            mouse_pos.y > grid_pos.y &&
            mouse_pos.y < grid_pos.y + grid_height * disp_size) {
                /*
                if ((ImGui::IsMouseDown(0) && !Utils::v_eq(mouse_coords, old_pos)) || ImGui::IsMouseClicked(0)) {
                        GetAt(mouse_coords).flip();
                        old_pos = mouse_coords;
                }
                */
                if (ImGui::IsMouseClicked(0)) {
                        // Starting a drag.
                        GetAt(mouse_coords).flip();
                        dragging_bit = static_cast<bool>(GetAt(mouse_coords));
                }
                if (ImGui::IsMouseDown(0)) {
                        // Dragging -- just set all the encountered squares to the dragging_bit
                        GetAt(mouse_coords) = dragging_bit;
                }
        }
        Display();

        ImGui::TextWrapped("%s", image_encoded);
        if (ImGui::Button("Close")) {
                *open = false;
        }

        ImGui::End();
}

}  // namespace Images
