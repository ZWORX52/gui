// NOLINT(legal/copyright)
#include "./main.hpp"

namespace Images {

// Might eventually make this into a vector of chars or something.
// Would need to change the encoding. MAYBE vec<vec<char>> later?
// Not sure!
std::vector<std::vector<bool>> image;

char image_encoded[BUFFER_SIZE] = { 0 };
char image_encoded_in[LARGE_BUFFER_SIZE] = { 0 };

ImVec2 grid_pos          = ImVec2();
ImVec2 mouse_pos         = ImVec2();
ImVec2 disp_size_v       = ImVec2();
ImVec2 grid_size_v       = ImVec2();

int grid_width           = 30;
int grid_height          = 30;
int disp_size            = 10;

// The null terminator protects against strchr giving a segfault
const char hex_characters[16 + 1] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F', '\0'
};

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

void ResizeImage() {
        if (static_cast<size_t>(grid_height) != image.size()) {
                image.resize(grid_height, std::vector<bool>(grid_width, false));
        }
        if (static_cast<size_t>(grid_width) != image[0].size()) {
                for (size_t i = 0; i < image.size(); i++) {
                        image[i].resize(grid_width, false);
                }
        }
}

void Encode() { Encode(image_encoded); }
void Encode(char *dst) {
        // Yeet the image at dst
        Utils::ClearBuffer(dst);
        std::string image_str;
        std::bitset<4> hex_char_buf;
        for (size_t i = 0; i < image.size(); i++) {
                for (size_t j = 0; j < image[i].size(); j++) {
                        image_str.push_back(image[i][j] ? '1' : '0');
                }
        }
        while (image_str.size() % 4 != 0) {
                image_str.push_back('0');
        }
        std::string res;
        // Add size
        res.push_back(hex_characters[(grid_width & 0xf0) >> 4]);
        res.push_back(hex_characters[grid_width & 0x0f]);
        res.push_back(hex_characters[(grid_height & 0xf0) >> 4]);
        res.push_back(hex_characters[grid_height & 0x0f]);

        for (size_t i = 0; i < image_str.size(); i += 4) {
                hex_char_buf = std::bitset<4>(image_str.substr(i));
                uint16_t hex_char_buf_val = hex_char_buf.to_ulong();
                res.push_back(hex_characters[hex_char_buf_val]);
        }
        memcpy(dst, res.c_str(), res.size());
}

void Decode() { Decode(image_encoded_in); }
void Decode(char *src) {
        // Yeet the src at image
        // (with resizing)
        std::string image_str;
        std::bitset<4> hex_char_buf;
        std::string src_s(src);
        std::string width_s = src_s.substr(0, 2);
        std::string height_s = src_s.substr(2, 2);
        int width = std::stoi(width_s, nullptr, 16);
        int height = std::stoi(height_s, nullptr, 16);
        grid_width = width; grid_height = height;
        ResizeImage();

        src_s = src_s.substr(4);
        for (char c : src_s) {
                const char* loc_in_hex_str = strchr(hex_characters, c);
                if (!loc_in_hex_str) {
                        // Invalid character in input! Abort.
                        // TODO(ZWORX52): tell user why import failed
                        return;
                }
                uint16_t hex_val = loc_in_hex_str - hex_characters;
                hex_char_buf = std::bitset<4>(hex_val);
                image_str.append(hex_char_buf.to_string());
        }
        while (image_str.size() > image[0].size() * image.size()) {
                image_str.pop_back();
        }
        /*
        while (image_str.size() < image[0].size() * image.size()) {
                image_str.push_back('0');
        }
        */
        if (image_str.size() < image[0].size() * image.size()) {
                // Abort! User has entered a string which does not contain enough data!
                // If we want to assume we can pad the string with zeros, then we have to
                // tell the user that!
                return;
        }
        // Now the string has exactly as many chars as the image does pixels. Perfect! Write to the image!
        for (size_t i = 0; i < image.size(); i++) {
                for (size_t j = 0; j < image[i].size(); j++) {
                        image[i][j] = image_str.at(i * image[0].size() + j) == '1' ? true : false;
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

        static bool dragging_bit = false;

        disp_size_v = ImVec2(disp_size, disp_size);
        grid_size_v = ImVec2(grid_width, grid_height);

        ResizeImage();

        ImGui::Begin("Images", open, flags);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 4));

        ImGui::SliderInt("Grid width", &grid_width, 1, 100);
        if (ImGui::IsItemHovered())
                ImGui::SetTooltip("default: 30");

        ImGui::SliderInt("Grid height", &grid_height, 1, 100);
        if (ImGui::IsItemHovered())
                ImGui::SetTooltip("default: 30");

        ImGui::SliderInt("Block size", &disp_size, 1, 50);
        if (ImGui::IsItemHovered())
                ImGui::SetTooltip("default: 10");

        grid_pos = ImGui::GetCursorScreenPos();
        mouse_pos = io.MousePos;

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

        if (ImGui::BeginTable("image_i/o", 2)) {
                ImGui::TableNextColumn();
                if (ImGui::Button("Decode"))
                        Decode();
                if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("note: no more than 32767 characters please!\n"
                                          "otherwise there will be a segfault (most likely), and you will be sad");
                ImGui::SameLine();
                if (ImGui::Button("Clear image"))
                        ClearImage();
                /*
                // Oh ImGui! No wrapping for InputTextMultiline! :(
                ImGui::InputTextMultiline("##image_encoded", image_encoded_in, LARGE_BUFFER_SIZE,
                                ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetTextLineHeight() * 10),
                                ImGuiInputTextFlags_None);
                */  
                ImGui::BeginChild("left", ImVec2(ImGui::GetContentRegionAvail().x,
                                ImGui::GetTextLineHeight() * 7.5f), false, ImGuiWindowFlags_NoScrollbar);
                ImGui::TextWrapped("%s", image_encoded_in);
                ImGui::EndChild();
                ImGui::InputTextMultiline("##image_encoded", image_encoded_in, LARGE_BUFFER_SIZE,
                                ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetTextLineHeight() * 1.5),
                                ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase |
                                ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_AutoSelectAll);

                ImGui::TableNextColumn();
                if (ImGui::Button("Encode"))
                        Encode();
                ImGui::SameLine();
                if (ImGui::Button("Copy encoded image"))
                        ImGui::SetClipboardText(image_encoded);
                ImGui::BeginChild("right", ImVec2(ImGui::GetContentRegionAvail().x,
                                ImGui::GetTextLineHeight() * 10), false, ImGuiWindowFlags_NoScrollbar);
                ImGui::TextWrapped("%s", image_encoded);
                ImGui::EndChild();

                ImGui::EndTable();
        }

        if (ImGui::Button("Close")) {
                *open = false;
        }

        ImGui::PopStyleVar();
        ImGui::End();
}

}  // namespace Images
