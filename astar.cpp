// NOLINT(legal/copyright)
#include "./main.hpp"

std::vector<std::vector<AStar::Node>> grid;

std::list<AStar::Node*> toConsider;
// std::vector<AStar::Node*> considered;
// Not needed as nodes are stored in the grid.

ImVec4 col_none;
ImVec4 col_wall;
ImVec4 col_start;
ImVec4 col_end;
ImVec4 col_path;
ImVec4 col_considered;
ImVec4 col_toConsider;

ImVec2 grid_pos;
ImVec2 mouse_pos;
ImVec2 end_pos;
ImVec2 start_pos;

int grid_size = 10;
int grid_width = 30;
int grid_height = 30;
bool running = false;
bool paused = false;  // Necessary so we know not to call AStar::Setup() if we
// want to unpause because it messes up the toConsider & considered containers.
unsigned path_length = 0;

AStar::Node::Node(ImVec2 pos) {
        // The gimmick is that the program fills
        // the EXISTING nodes in on their extra data LATER.
        this->pos = pos;
        this->type = AStar::GridSquare_None;
        this->parent = NULL;
        this->generation = 0;
        this->distance = 0;
        this->score = 0;
}

double AStar::Node::ComputeDistanceToEnd() {
        // End is global
        ImVec2 distance = Utils::v_abs(this->pos - end_pos);
        distance *= distance;
        this->distance = sqrt(distance.x + distance.y);
        return this->distance;
}

double AStar::Node::ComputeScore() {
        // Side effect. Computes score
        this->score = ComputeDistanceToEnd() + this->generation;
        return this->score;
}

void AStar::Setup() {
        // May need to do more things here
        if (AStar::GetSquareAt(start_pos)->type != GridSquare_Start ||
                        AStar::GetSquareAt(end_pos)->type != GridSquare_End)
                return;
        running = true;
        paused = false;
        toConsider.push_back(AStar::GetSquareAt(start_pos));
        path_length = 0;
}

void AStar::Stop() {
        // Prepare for next session.
        running = false;
        paused = false;
        toConsider.clear();
        for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                        grid[i][j].parent = NULL;
                }
        }
}

void AStar::Tick() {
        // Manages everything necessary in one step of the astar algorithm
        if (toConsider.size() == 0) {
                // Nothing more to consider, therefore there is no path.
                // IDEA: Highlight closest node to the end
                // IDEA: (maybe with the path to that node?)
                Stop();
                return;
        }
        Node *thisConsider = toConsider.front();
        toConsider.erase(toConsider.begin());
        if (Utils::Equal(thisConsider->pos, end_pos)) {
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
        AStar::SetSquareAt(start_pos, GridSquare_Start);
        AStar::SetSquareAt(end_pos, GridSquare_End);
}

void AStar::CalculatePath(Node *from) {
        while (from != NULL) {
                // The start node will have a NULL parent. Then, we stop.
                if (from->type != AStar::GridSquare_Start && from->type != AStar::GridSquare_End) {
                        from->type = GridSquare_Path;
                        path_length++;
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
        return left->score < right;
}

void AStar::AddToConsider(AStar::Node *toAdd, AStar::Node *parent) {
        // Adds pointer `toAdd' to the toConsider list in the right position.
        toAdd->parent = parent;
        toAdd->generation = parent->generation + 1;
        toAdd->type = GridSquare_ToConsider;
        double score = toAdd->ComputeScore();
        std::function<bool(Node*, double)> comp = AStar::Comp;
        std::list<Node*>::const_iterator index = std::lower_bound(toConsider.cbegin(), toConsider.cend(), score, comp);
        toConsider.insert(index, toAdd);
}

bool AStar::InvalidPos(ImVec2 pos)                      {
        return pos.x < 0 || pos.x >= grid_width || pos.y < 0 || pos.y >= grid_height;
}

ImVec2 AStar::GetGridLocationUnderMouse() {
        ImVec2 v = (mouse_pos - grid_pos) / grid_size;
        return Utils::v_abs(ImVec2(static_cast<int>(v.x), static_cast<int>(v.y)));
}

AStar::Node *AStar::GetSquareAt(ImVec2 pos) { return &grid[pos.y][pos.x]; }
void AStar::SetSquareAtMouse(AStar::GridSquare type) { AStar::SetSquareAt(AStar::GetGridLocationUnderMouse(), type); }
void AStar::SetSquareAt(ImVec2 pos, AStar::GridSquare type) { grid[pos.y][pos.x].type = type; }
void AStar::DrawGrid() { AStar::DrawGrid(grid_pos, ImVec2(grid_size, grid_size)); }
void AStar::DrawGrid(ImVec2 pos) { AStar::DrawGrid(pos, ImVec2(grid_size, grid_size)); }
void AStar::DrawGrid(float size) { AStar::DrawGrid(grid_pos, ImVec2(size, size)); }
void AStar::DrawGrid(ImVec2 pos, float size) { AStar::DrawGrid(pos, ImVec2(size, size)); }

void AStar::DrawGrid(ImVec2 pos, ImVec2 size) {
        // Draws the grid to the current window, with the top-left corner at `pos'
        static ImU32 this_col;
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                        switch (grid[i][j].type) {
                                case GridSquare_None:           this_col = ImColor(col_none);
                                                                break;
                                case GridSquare_Wall:           this_col = ImColor(col_wall);
                                                                break;
                                case GridSquare_Start:          this_col = ImColor(col_start);
                                                                break;
                                case GridSquare_End:            this_col = ImColor(col_end);
                                                                break;
                                case GridSquare_Path:           this_col = ImColor(col_path);
                                                                break;
                                case GridSquare_Considered:     this_col = ImColor(col_considered);
                                                                break;
                                case GridSquare_ToConsider:     this_col = ImColor(col_toConsider);
                                                                break;
                        }
                        // Actually draw the square ;)
                        ImVec2 square_start = pos + ImVec2(size.x * j, size.y * i);
                        draw_list->AddRectFilled(square_start, square_start + size, this_col);
                }
        }
        ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + grid.size() * size.y + 4));
}

void AStar::FillGrid(double rate) {
        for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                        if (Utils::Random() <= static_cast<double>(rate) &&
                                        grid[i][j].type == AStar::GridSquare_None)
                                grid[i][j].type = AStar::GridSquare_Wall;
                }
        }
}

void AStar::ClearGrid() {
        for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                        if (grid[i][j].type == AStar::GridSquare_Wall)
                                grid[i][j].type = AStar::GridSquare_None;
                }
        }
}

size_t AStar::ClearGridOf(GridSquare toClear) {
        size_t count = 0;  // If this isn't enough, I'm not writing `unsigned long long' everywhere lol
        for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                        if (grid[i][j].type == toClear) {
                                grid[i][j].type = AStar::GridSquare_None;
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
        ImGui::Text("p: Pause (if running)");
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

        col_none                = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);  // #000000FF Black
        col_wall                = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // #FF0000FF Red
        col_start               = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);  // #FF00FFFF Purple
        col_end                 = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);  // #FFFF00FF Yellow
        col_path                = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);  // #0000FFFF Blue
        col_considered          = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);  // #FF7800FF Orange
        col_toConsider          = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // #00FF00FF Green

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

        if (ImGui::IsKeyPressed(ImGuiKey_P) && running)
                paused ^= 1;

        if (ImGui::IsKeyPressed(ImGuiKey_I))
        { AStar::Setup(); running = false; }

        if (!exclusivemode) {
                if (ImGui::TreeNode("Keybinds")) {
                        AStar::ShowKeybinds();
                        ImGui::TreePop();
                }

                if (ImGui::TreeNode("Config")) {
                        ImGui::PushID("Colors");

                        ImGui::ColorEdit4("##none", &col_none.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'none' color"))
                                col_none = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##wall", &col_wall.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'wall' color"))
                                col_wall = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##start", &col_start.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'start' color"))
                                col_start = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);

                        ImGui::ColorEdit4("##end", &col_end.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'end' color"))
                                col_end = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##path", &col_path.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'path' color"))
                                col_path = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);

                        ImGui::ColorEdit4("##considered", &col_considered.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'considered' color"))
                                col_considered = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);

                        ImGui::ColorEdit4("##toConsider", &col_toConsider.x);
                        ImGui::SameLine();
                        if (ImGui::Button("Reset 'toConsider' color"))
                                col_toConsider = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

                        ImGui::PopID();

                        ImGui::PushID("Other configs");

                        // Yes, you need to specify that the rate of an int is 1.
                        // No, I don't understand why there isn't an overload without the rate.
                        ImGui::DragInt("##width", &grid_width, 1, 1, 100, "%i");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset width to 30"))
                                grid_width = 30;

                        ImGui::DragInt("##height", &grid_height, 1, 1, 100, "%i");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset height to 30"))
                                grid_height = 30;

                        ImGui::DragFloat("##rate", &rate, 0.01f, 0.0f, 1.0f, "%.2f");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset rate to 0.25"))
                                rate = 0.25f;

                        ImGui::DragInt("##size", &grid_size, 1, 1, 20, "%i");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset size to 10"))
                                grid_size = 10;

                        ImGui::PopID();

                        ImGui::TreePop();
                }

                if (ImGui::Button("Fill grid"))
                        FillGrid(rate);
                ImGui::SameLine();
                if (ImGui::Button("Clear grid"))
                        ClearGridOf(GridSquare_Wall);
                ImGui::SameLine();
                if (running) {
                        if (!paused && ImGui::Button("Pause"))
                                paused = true;
                        if (paused && ImGui::Button("Resume"))
                                paused = false;
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

        // Note: ImGui guarantees (enough for me at least) that grid_height won't ever be >100.
        // I can add an assert or a check if really needed.
        if (static_cast<size_t>(grid_height) != grid.size()) {
                // Unfortunately I can't use .resize() here because we need a constructor for
                // the new nodes (that takes their position).
                if (static_cast<size_t>(grid_height) > grid.size()) {
                        std::vector<Node> tmp_vector;
                        for (int i = 0; i < grid_width; i++) {
                                tmp_vector.push_back(Node(ImVec2(i, 0)));
                        }
                        for (int i = grid.size(); i < grid_height; i++) {
                                // Starting at grid.size() is intentional, because we don't want to overwrite anything
                                // that the user or program placed.  Then again, we don't really need the index: we just
                                // need to loop the right amount of times.
                                for (size_t j = 0; j < tmp_vector.size(); j++) {
                                        // Make sure to update the Y coordinate.
                                        tmp_vector[j].pos.y = i;
                                }
                                grid.push_back(tmp_vector);
                        }
                } else {
                        // Starting at the intended final height, so that we can remove that value
                        // (start-at-zero stuff ;) At least we have .erase() here!
                        grid.erase(grid.begin() + grid_height, grid.end());
                }
        }
        if (static_cast<size_t>(grid_width) != grid[0].size()) {
                for (size_t i = 0; i < grid.size(); i++) {
                        if (static_cast<size_t>(grid_width) > grid.size()) {
                                for (int j = grid[i].size(); j < grid_width; j++) {
                                        grid[i].push_back(Node(ImVec2(j, i)));
                                }
                        } else {
                                grid[i].erase(grid[i].cbegin() + grid_width, grid[i].cend());
                        }
                }
        }

        grid_pos = ImGui::GetCursorScreenPos();
        mouse_pos = io.MousePos;
        ImVec2 under_mouse = GetGridLocationUnderMouse();
        if (io.MousePos.x > grid_pos.x && io.MousePos.x < grid_pos.x + grid_width * grid_size &&
                        io.MousePos.y > grid_pos.y && io.MousePos.y < grid_pos.y + grid_height * grid_size) {
                if (ImGui::IsMouseDown(0)) {
                        // Left clicked
                        if (startsetting) {
                                // Make sure there is only one start and end and update start_pos
                                AStar::ClearGridOf(AStar::GridSquare_Start);
                                AStar::SetSquareAtMouse(AStar::GridSquare_Start);
                                start_pos = under_mouse;
                        } else {
                                AStar::SetSquareAtMouse(AStar::GridSquare_Wall);
                        }
                } else if (ImGui::IsMouseDown(1)) {
                        // Right clicked
                        if (startsetting) {
                                // Make sure there is only one start and end and update start_pos
                                AStar::ClearGridOf(AStar::GridSquare_End);
                                AStar::SetSquareAtMouse(AStar::GridSquare_End);
                                end_pos = under_mouse;
                        } else {
                                AStar::SetSquareAtMouse(AStar::GridSquare_None);
                        }
                }
        }

        if (!AStar::InvalidPos(under_mouse) && ImGui::IsKeyDown(562)) {  // 562 = q
                AStar::Node *sq_under_mouse = AStar::GetSquareAt(under_mouse);
                if (sq_under_mouse->type == AStar::GridSquare_Path)
                        ImGui::SetTooltip("length: %u", path_length);
                if (sq_under_mouse->type == AStar::GridSquare_ToConsider ||
                                sq_under_mouse->type == AStar::GridSquare_Considered)
                        ImGui::SetTooltip("distance: %f, gen: %u",
                                        sq_under_mouse->distance, sq_under_mouse->generation);
        }

        AStar::DrawGrid();

        if (!exclusivemode && ImGui::Button("Close"))
                *open = false;

        ImGui::PopStyleVar();
        ImGui::End();
}

