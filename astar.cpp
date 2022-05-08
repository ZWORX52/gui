// NOLINT(legal/copyright)
#include "./main.hpp"

namespace AStar {

std::vector<std::vector<AStar::Node>> astar_grid;
std::list<AStar::Node*> astar_toConsider;

ImVec4 astar_col_none;
ImVec4 astar_col_wall;
ImVec4 astar_col_start;
ImVec4 astar_col_end;
ImVec4 astar_col_path;
ImVec4 astar_col_considered;
ImVec4 astar_col_toConsider;

ImVec2 astar_grid_pos;
ImVec2 astar_mouse_pos;
ImVec2 astar_end_pos;
ImVec2 astar_start_pos;

int astar_grid_pixel_size = 10;
int astar_grid_width = 30;
int astar_grid_height = 30;
bool astar_running = true;
bool astar_paused = true;  // Necessary so we know not to call AStar::Setup() if we
// want to unpause because it messes up the toConsider & considered containers.
unsigned astar_path_length = 0;

AStar::Node::Node(ImVec2 new_pos) {
        this->pos = new_pos;
        this->type = AStar::GridSquare_None;
        this->parent = NULL;
        this->generation = 0;
        this->stored_distance = 0;
        this->stored_score = 0;
}

double AStar::Node::ComputeDistanceToEnd() {
        // End is global
        ImVec2 distance = Utils::v_abs(this->pos - astar_end_pos);
        distance *= distance;
        this->stored_distance = sqrt(distance.x + distance.y);
        return this->stored_distance;
}

double AStar::Node::ComputeScore() {
        // Side effect. Computes score
        this->stored_score = ComputeDistanceToEnd() + this->generation;
        return this->stored_score;
}

void AStar::Setup() {
        // May need to do more things here
        if (AStar::GetSquareAt(astar_start_pos)->type != GridSquare_Start ||
                        AStar::GetSquareAt(astar_end_pos)->type != GridSquare_End)
                return;
        astar_running = true;
        astar_paused = false;
        astar_toConsider.push_back(AStar::GetSquareAt(astar_start_pos));
        astar_path_length = 0;
}

void AStar::Stop() {
        // Prepare for next session.
        astar_running = false;
        astar_paused = false;
        astar_toConsider.clear();
        for (size_t i = 0; i < astar_grid.size(); i++) {
                for (size_t j = 0; j < astar_grid[i].size(); j++) {
                        astar_grid[i][j].parent = NULL;
                }
        }
}

void AStar::Tick() {
        // Manages everything necessary in one step of the astar algorithm
        if (astar_toConsider.size() == 0) {
                // Nothing more to consider, therefore there is no path.
                // IDEA: Highlight closest node to the end
                // IDEA: (maybe with the path to that node?)
                Stop();
                return;
        }
        Node *thisConsider = astar_toConsider.front();
        astar_toConsider.erase(astar_toConsider.begin());
        if (Utils::v_eq(thisConsider->pos, astar_end_pos)) {
                AStar::CalculatePath(thisConsider);
                AStar::Stop();
                return;
        }
        thisConsider->type = AStar::GridSquare_Considered;
        ImVec2 directions[] = {
                ImVec2(-1, -1), ImVec2(0, -1), ImVec2(1, -1),
                ImVec2(-1,  0),                ImVec2(1,  0),
                ImVec2(-1,  1), ImVec2(0,  1), ImVec2(1,  1)
        };
        // OR (for only up, down, left & right)
        /* 
        ImVec2 directions[] = {
                              ImVec2(0,-1),
                ImVec2(-1, 0),             ImVec2(1, 0),
                              ImVec2(0, 1)
        };
         */
        for (size_t i = 0; i < IM_ARRAYSIZE(directions); i++) {
                ImVec2 next_pos = thisConsider->pos + directions[i];
                if (AStar::InvalidPos(next_pos))
                        continue;
                if (AStar::GetSquareAt(next_pos)->type == AStar::GridSquare_None ||
                                AStar::GetSquareAt(next_pos)->type == AStar::GridSquare_End) {
                        Node *toAdd = AStar::GetSquareAt(next_pos);
                        // FIXME: variable for GetSquareAt(next_pos) as it's used 3 (no, 4) times
                        AStar::AddToConsider(toAdd, thisConsider);
                }
        }
        // Preservation
        AStar::SetSquareAt(astar_start_pos, GridSquare_Start);
        AStar::SetSquareAt(astar_end_pos, GridSquare_End);
}

void AStar::CalculatePath(Node *from) {
        while (from != NULL) {
                // The start node will have a NULL parent. Then, we stop.
                if (from->type != AStar::GridSquare_Start && from->type != AStar::GridSquare_End) {
                        from->type = GridSquare_Path;
                        astar_path_length++;
                }
                from = from->parent;
        }
}

void AStar::CalculateTempPath(Node *from) {
        // Computes the path like above, but writes to the virtual_type instead.
        while (from != NULL) {
                if (from->type != AStar::GridSquare_Start) {
                        from->virtual_type = GridSquare_Path;
                }
        }
}

bool AStar::Comp(AStar::Node *left, double right) {
        return left->stored_score < right;
}

void AStar::AddToConsider(AStar::Node *toAdd, AStar::Node *parent) {
        // Adds pointer `toAdd' to the toConsider list in the right position.
        toAdd->parent = parent;
        toAdd->generation = parent->generation + 1;
        toAdd->type = GridSquare_ToConsider;
        double score = toAdd->ComputeScore();
        std::function<bool(Node*, double)> comp = AStar::Comp;
        std::list<Node*>::const_iterator index = std::lower_bound(astar_toConsider.cbegin(),
                                                                  astar_toConsider.cend(), score, comp);
        astar_toConsider.insert(index, toAdd);
}

ImVec2 AStar::GetGridLocationUnderMouse() {
        ImVec2 v = (astar_mouse_pos - astar_grid_pos) / astar_grid_pixel_size;
        return Utils::v_abs(ImVec2(static_cast<int>(v.x), static_cast<int>(v.y)));
}

AStar::Node *AStar::GetSquareAt(ImVec2 pos) { return &astar_grid[pos.y][pos.x]; }
void AStar::SetSquareAtMouse(AStar::GridSquare type) { AStar::SetSquareAt(AStar::GetGridLocationUnderMouse(), type); }
void AStar::SetSquareAt(ImVec2 pos, AStar::GridSquare type) { astar_grid[pos.y][pos.x].type = type; }
void AStar::DrawGrid() { AStar::DrawGrid(astar_grid_pos, ImVec2(astar_grid_pixel_size, astar_grid_pixel_size)); }
void AStar::DrawGrid(ImVec2 pos) { AStar::DrawGrid(pos, ImVec2(astar_grid_pixel_size, astar_grid_pixel_size)); }
void AStar::DrawGrid(float size) { AStar::DrawGrid(astar_grid_pos, ImVec2(size, size)); }
void AStar::DrawGrid(ImVec2 pos, float size) { AStar::DrawGrid(pos, ImVec2(size, size)); }
bool AStar::InvalidPos(ImVec2 pos) { return
        pos.x < 0 || pos.x >= astar_grid_width || pos.y < 0 || pos.y >= astar_grid_height; }

void AStar::DrawGrid(ImVec2 pos, ImVec2 size) {
        // Draws the grid to the current window, with the top-left corner at `pos'
        static ImU32 this_col;
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        for (size_t i = 0; i < astar_grid.size(); i++) {
                for (size_t j = 0; j < astar_grid[i].size(); j++) {
                        switch (astar_grid[i][j].type) {
                                case GridSquare_None:           this_col = ImColor(astar_col_none);
                                                                break;
                                case GridSquare_Wall:           this_col = ImColor(astar_col_wall);
                                                                break;
                                case GridSquare_Start:          this_col = ImColor(astar_col_start);
                                                                break;
                                case GridSquare_End:            this_col = ImColor(astar_col_end);
                                                                break;
                                case GridSquare_Path:           this_col = ImColor(astar_col_path);
                                                                break;
                                case GridSquare_Considered:     this_col = ImColor(astar_col_considered);
                                                                break;
                                case GridSquare_ToConsider:     this_col = ImColor(astar_col_toConsider);
                                                                break;
                        }
                        // Actually draw the square ;)
                        ImVec2 square_start = pos + ImVec2(size.x * j, size.y * i);
                        draw_list->AddRectFilled(square_start, square_start + size, this_col);
                }
        }
        ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + astar_grid.size() * size.y + 4));
}

void AStar::FillGrid(double rate) {
        for (size_t i = 0; i < astar_grid.size(); i++) {
                for (size_t j = 0; j < astar_grid[i].size(); j++) {
                        if (Utils::Random() <= static_cast<double>(rate) &&
                                        astar_grid[i][j].type == AStar::GridSquare_None)
                                astar_grid[i][j].type = AStar::GridSquare_Wall;
                }
        }
}

void AStar::ClearGrid() {
        for (size_t i = 0; i < astar_grid.size(); i++) {
                for (size_t j = 0; j < astar_grid[i].size(); j++) {
                        if (astar_grid[i][j].type == AStar::GridSquare_Wall)
                                astar_grid[i][j].type = AStar::GridSquare_None;
                }
        }
}

size_t AStar::ClearGridOf(GridSquare toClear) {
        size_t count = 0;  // If this isn't enough, I'm not writing `unsigned long long' everywhere lol
        for (size_t i = 0; i < astar_grid.size(); i++) {
                for (size_t j = 0; j < astar_grid[i].size(); j++) {
                        if (astar_grid[i][j].type == toClear) {
                                astar_grid[i][j].type = AStar::GridSquare_None;
                                count++;
                        }
                }
        }
        return count;
}

void AStar::ShowKeybinds() {
        // Shows keybinds info.  Doesn't make a container -- use with at least a bit of caution
        // (i.e. will just dump text right where it's called).
        ImGui::Text("<S-e>:");
        if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                ImGui::SetTooltip("Shift + e");
        ImGui::SameLine();
        ImGui::Text("Toggle exclusive mode");

        ImGui::Text("<S-s>:");
        if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                ImGui::SetTooltip("Shift + s");
        ImGui::SameLine();
        ImGui::Text("Toggle setting start");

        ImGui::Text("<S-q>:");
        if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                ImGui::SetTooltip("Shift + q");
        ImGui::SameLine();
        ImGui::Text("Close");

        ImGui::Text("<S-r>:");
        if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                ImGui::SetTooltip("Shift + r");
        ImGui::SameLine();
        ImGui::Text("Reset algorithm");

        ImGui::Text("<S-h>:");
        if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                ImGui::SetTooltip("Shift + h");
        ImGui::SameLine();
        ImGui::Text("Pull up keybinds");

        ImGui::Text("c: Clear board");
        ImGui::Text("s: Start");
        ImGui::Text("f: Fill board");
        ImGui::Text("t: Tick (step)");
        ImGui::Text("p: Pause (if astar_running)");
        ImGui::Text("i: Initialize algorithm");
        ImGui::Text("q: Query (get info about tile)");
        ImGui::Text("d: Display path to tile");
}

void AStar::UpdateWindow(bool *open) {
        // FIXME: Use iterators!!! (Still partially in C habit, iterators are better!)
        // FIXME: Put global variables in namespace (mostly because they are very scattered right now)
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_NoDecoration;
        flags |= ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoResize;

        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGui::Begin("AStar", open, flags);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 4));

        // Width and height of the grid
        // static const int min = 1;
        // static const int max = 100;
        static float rate = 0.25f;

        static bool startsetting = false;
        static bool exclusivemode = false;
        // static bool auto = false;  // TODO

        astar_col_none                = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);  // #000000FF Black
        astar_col_wall                = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // #FF0000FF Red
        astar_col_start               = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);  // #FF00FFFF Purple
        astar_col_end                 = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);  // #FFFF00FF Yellow
        astar_col_path                = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);  // #0000FFFF Blue
        astar_col_considered          = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);  // #FF7800FF Orange
        astar_col_toConsider          = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // #00FF00FF Green

        ImGuiIO &io = ImGui::GetIO();
        if (ImGui::IsKeyPressed(ImGuiKey_E) && io.KeyShift)
                exclusivemode ^= 1;

        if (ImGui::IsKeyPressed(ImGuiKey_S) && io.KeyShift)
                startsetting ^= 1;

        if (ImGui::IsKeyPressed(ImGuiKey_Q) && io.KeyShift)
                *open = false;

        if (ImGui::IsKeyPressed(ImGuiKey_R) && io.KeyShift) {
                AStar::Stop();
                AStar::ClearGridOf(AStar::GridSquare_Path);
                AStar::ClearGridOf(AStar::GridSquare_Considered);
                AStar::ClearGridOf(AStar::GridSquare_ToConsider);
        }

        if (ImGui::IsKeyPressed(ImGuiKey_H) && io.KeyShift)
                ImGui::OpenPopup("Keybinds");

        if (ImGui::IsKeyPressed(ImGuiKey_C))
                AStar::ClearGrid();

        if (ImGui::IsKeyPressed(ImGuiKey_S) && !io.KeyShift)
                AStar::Setup();

        if (ImGui::IsKeyPressed(ImGuiKey_F))
                AStar::FillGrid(rate);

        if (ImGui::IsKeyPressed(ImGuiKey_T))
                AStar::Tick();

        if (ImGui::IsKeyPressed(ImGuiKey_P) && astar_running)
                astar_paused ^= 1;

        if (ImGui::IsKeyPressed(ImGuiKey_I))
        { AStar::Setup(); astar_running = false; }

        if (!exclusivemode) {
                if (ImGui::TreeNode("Keybinds")) {
                        AStar::ShowKeybinds();
                        ImGui::TreePop();
                }

                if (ImGui::TreeNode("Config")) {
                        ImGui::PushID("Colors");

                        ImGui::ColorEdit4("##none", &astar_col_none.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'none' color"))
                                astar_col_none = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##wall", &astar_col_wall.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'wall' color"))
                                astar_col_wall = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##start", &astar_col_start.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'start' color"))
                                astar_col_start = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);

                        ImGui::ColorEdit4("##end", &astar_col_end.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'end' color"))
                                astar_col_end = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##path", &astar_col_path.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'path' color"))
                                astar_col_path = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);

                        ImGui::ColorEdit4("##considered", &astar_col_considered.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'considered' color"))
                                astar_col_considered = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##toConsider", &astar_col_toConsider.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'toConsider' color"))
                                astar_col_toConsider = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

                        ImGui::PopID();

                        ImGui::PushID("Other configs");

                        // Yes, you need to specify that the rate of an int is 1.
                        // No, I don't understand why there isn't an overload without the rate.
                        ImGui::DragInt("##width", &astar_grid_width, 1, 1, 100, "%i");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset width to 30"))
                                astar_grid_width = 30;

                        ImGui::DragInt("##height", &astar_grid_height, 1, 1, 100, "%i");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset height to 30"))
                                astar_grid_height = 30;

                        ImGui::DragFloat("##rate", &rate, 0.01f, 0.0f, 1.0f, "%.3f");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset rate to 0.25"))
                                rate = 0.25f;

                        ImGui::DragInt("##size", &astar_grid_pixel_size, 1, 1, 20, "%i");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset size to 10"))
                                astar_grid_pixel_size = 10;

                        ImGui::PopID();

                        ImGui::TreePop();
                }

                if (ImGui::Button("Fill grid"))
                        FillGrid(rate);
                ImGui::SameLine();
                if (ImGui::Button("Clear grid"))
                        ClearGridOf(GridSquare_Wall);
                ImGui::SameLine();
                if (astar_running) {
                        if (!astar_paused && ImGui::Button("Pause"))
                                astar_paused = true;
                        if (astar_paused && ImGui::Button("Resume"))
                                astar_paused = false;
                        AStar::Tick();
                } else {
                        if (ImGui::Button("Start"))
                                AStar::Setup();
                }
                ImGui::SameLine();  // In each branch of the `if' above, we -- guaranteed -- have a button.
                if (ImGui::Button("Reset algorithm")) {
                        AStar::Stop();  // Handles most things, but in this case we also want to clear stuff.
                        AStar::ClearGridOf(AStar::GridSquare_Path);
                        AStar::ClearGridOf(AStar::GridSquare_Considered);
                        AStar::ClearGridOf(AStar::GridSquare_ToConsider);
                }
                ImGui::SameLine();
                ImGui::Checkbox("Setting start?", &startsetting);
        }

        if (ImGui::BeginPopup("Keybinds")) {
                AStar::ShowKeybinds();
                ImGui::EndPopup();
        }

        // Note: ImGui guarantees (enough for me at least) that astar_grid_height won't ever be >100.
        // I can add an assert or a check if really needed.
        if (static_cast<size_t>(astar_grid_height) != astar_grid.size()) {
                // Unfortunately I can't use .resize() here because we need a constructor for
                // the new nodes (that takes their position).
                if (static_cast<size_t>(astar_grid_height) > astar_grid.size()) {
                        std::vector<Node> tmp_vector;
                        for (int i = 0; i < astar_grid_width; i++) {
                                tmp_vector.push_back(Node(ImVec2(i, 0)));
                        }
                        for (int i = astar_grid.size(); i < astar_grid_height; i++) {
                                // Starting at grid.size() is intentional, because we don't want to overwrite anything
                                // that the user or program placed.  Then again, we don't really need the index: we just
                                // need to loop the right amount of times.
                                for (size_t j = 0; j < tmp_vector.size(); j++) {
                                        // Make sure to update the Y coordinate.
                                        tmp_vector[j].pos.y = i;
                                }
                                astar_grid.push_back(tmp_vector);
                        }
                } else {
                        // Starting at the intended final height, so that we can remove that value
                        // (start-at-zero stuff ;) At least we have .erase() here!
                        astar_grid.erase(astar_grid.begin() + astar_grid_height, astar_grid.end());
                }
        }
        if (static_cast<size_t>(astar_grid_width) != astar_grid[0].size()) {
                for (size_t i = 0; i < astar_grid.size(); i++) {
                        if (static_cast<size_t>(astar_grid_width) > astar_grid[i].size()) {  // Oops!
                                for (int j = astar_grid[i].size(); j < astar_grid_width; j++) {
                                        astar_grid[i].push_back(Node(ImVec2(j, i)));
                                }
                        } else {
                                astar_grid[i].erase(astar_grid[i].cbegin() + astar_grid_width, astar_grid[i].cend());
                        }
                }
        }

        astar_grid_pos = ImGui::GetCursorScreenPos();
        astar_mouse_pos = io.MousePos;
        ImVec2 under_mouse = GetGridLocationUnderMouse();
        if (io.MousePos.x > astar_grid_pos.x &&
            io.MousePos.x < astar_grid_pos.x + astar_grid_width * astar_grid_pixel_size &&
            io.MousePos.y > astar_grid_pos.y &&
            io.MousePos.y < astar_grid_pos.y + astar_grid_height * astar_grid_pixel_size) {
                if (ImGui::IsMouseDown(0)) {
                        // Left clicked
                        if (startsetting) {
                                // Make sure there is only one start and end and update start_pos
                                AStar::ClearGridOf(AStar::GridSquare_Start);
                                AStar::SetSquareAtMouse(AStar::GridSquare_Start);
                                astar_start_pos = under_mouse;
                        } else {
                                AStar::SetSquareAtMouse(AStar::GridSquare_Wall);
                        }
                } else if (ImGui::IsMouseDown(1)) {
                        // Right clicked
                        if (startsetting) {
                                // Make sure there is only one start and end and update start_pos
                                AStar::ClearGridOf(AStar::GridSquare_End);
                                AStar::SetSquareAtMouse(AStar::GridSquare_End);
                                astar_end_pos = under_mouse;
                        } else {
                                AStar::SetSquareAtMouse(AStar::GridSquare_None);
                        }
                }
        }

        if (!AStar::InvalidPos(under_mouse) && ImGui::IsKeyDown(562)) {  // 562 = q
                AStar::Node *sq_under_mouse = AStar::GetSquareAt(under_mouse);
                if (sq_under_mouse->type == AStar::GridSquare_Path)
                        ImGui::SetTooltip("length: %u", astar_path_length);
                if (sq_under_mouse->type == AStar::GridSquare_ToConsider ||
                                sq_under_mouse->type == AStar::GridSquare_Considered)
                        ImGui::SetTooltip("distance: %f, gen: %u",
                                        sq_under_mouse->stored_distance, sq_under_mouse->generation);
        }

        AStar::DrawGrid();

        if (!exclusivemode && ImGui::Button("Close"))
                *open = false;

        ImGui::PopStyleVar();
        ImGui::End();
}

};  // namespace AStar

