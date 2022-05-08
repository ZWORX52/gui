// NOLINT(legal/copyright)
#include "./main.hpp"

// Might eventually make this into a vector of chars or something.
// Would need to change the encoding. MAYBE vec<vec<char>> later?
// Not sure!
std::vector<std::vector<bool>> images_image;

char images_image_encoded[BUFFER_SIZE] = { 0 };

ImVec2 images_grid_pos          = ImVec2();
ImVec2 images_mouse_pos         = ImVec2();
ImVec2 images_disp_size_v       = ImVec2();
ImVec2 images_grid_size_v       = ImVec2();

int images_grid_width           = 30;
int images_grid_height          = 30;
int images_disp_size            = 10;

ImVec2 Images::GetCoordsAtMouse() {
        ImVec2 v = (images_mouse_pos - images_grid_pos) / images_disp_size_v;
        return Utils::v_abs(ImVec2(static_cast<int>(v.x), static_cast<int>(v.y)));
}

bool Images::InvalidPos(ImVec2 coords) {
        return coords.x < 0 || coords.x > images_grid_width || coords.y < 0 || coords.y > images_grid_width;
}

std::vector<bool>::reference Images::GetAt(ImVec2 pos) { return images_image[pos.y][pos.x]; }

void Images::Display() {
        // Uses draw list to put images on the screen.
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        for (size_t i = 0; i < images_image.size(); i++) {
                for (size_t j = 0; j < images_image[i].size(); j++) {
                        ImVec2 square_start = images_grid_pos + images_disp_size_v * ImVec2(j, i);
                        draw_list->AddRectFilled(square_start, square_start + images_disp_size_v,
                                        images_image[i][j] ? ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)) :
                                        ImColor(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)));
                }
        }
        ImGui::SetCursorScreenPos(ImVec2(images_grid_pos.x, images_grid_pos.y + images_grid_height * images_disp_size + 4));
}

void Images::ClearImage() {
        for (size_t i = 0; i < images_image.size(); i++) {
                for (size_t j = 0; j < images_image[i].size(); j++) {
                        images_image[i][j] = false;
                }
        }
}

void Images::Encode() { Images::Encode(images_image_encoded); }
void Images::Encode(char *buf) {
        // Encode the images_image into buf
        // For now just yeet the hex at buf
        Utils::ClearBuffer(buf);
        //static char hex_img[ARRAY_SIZE / 4] = { 0 };
        for (size_t i = 0; i < images_image.size(); i++) {
                for (size_t j = 0; j < images_image[i].size(); j++) {
                        buf[i * images_image[i].size() + j] = images_image[i][j] ? '1' : '0';
                }
        }
}

void Images::UpdateWindow(bool *open) {
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

        images_disp_size_v = ImVec2(images_disp_size, images_disp_size);
        images_grid_size_v = ImVec2(images_grid_width, images_grid_height);

        ImGui::Begin("Images", open, flags);

        ImGui::SliderInt("Block size", &images_disp_size, 1, 20);

        ImGui::SliderInt("Grid width", &images_grid_width, 1, 100);
        ImGui::SliderInt("Grid height", &images_grid_height, 1, 100);

        if (ImGui::Button("Encode image")) {
                Images::Encode();
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear image")) {
                Images::ClearImage();
        }

        images_grid_pos = ImGui::GetCursorScreenPos();
        images_mouse_pos = io.MousePos;

        if (static_cast<size_t>(images_grid_height) != images_image.size()) {
                images_image.resize(images_grid_height, std::vector<bool>(images_grid_width, false));
        }
        if (static_cast<size_t>(images_grid_width) != images_image[0].size()) {
                for (size_t i = 0; i < images_image.size(); i++) {
                        images_image[i].resize(images_grid_width, false);
                }
        }

        ImVec2 mouse_coords = Images::GetCoordsAtMouse();
        if (images_mouse_pos.x > images_grid_pos.x &&
            images_mouse_pos.x < images_grid_pos.x + images_grid_width * images_disp_size &&
            images_mouse_pos.y > images_grid_pos.y &&
            images_mouse_pos.y < images_grid_pos.y + images_grid_height * images_disp_size) {
                /*
                if ((ImGui::IsMouseDown(0) && !Utils::v_eq(mouse_coords, old_pos)) || ImGui::IsMouseClicked(0)) {
                        Images::GetAt(mouse_coords).flip();
                        old_pos = mouse_coords;
                }
                */
                if (ImGui::IsMouseClicked(0)) {
                        // Starting a drag.
                        Images::GetAt(mouse_coords).flip();
                        dragging_bit = static_cast<bool>(Images::GetAt(mouse_coords));
                }
                if (ImGui::IsMouseDown(0)) {
                        // Dragging -- just set all the encountered squares to the dragging_bit
                        Images::GetAt(mouse_coords) = dragging_bit;
                }
        }
        Images::Display();

        ImGui::TextWrapped("%s", images_image_encoded);
        if (ImGui::Button("Close")) {
                *open = false;
        }

        ImGui::End();
}

