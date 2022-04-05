#include "main.hpp"

std::vector<std::vector<AStar::GridSquare>> grid;

std::vector<AStar::Node> toConsider;
std::list<AStar::Node> considered;
// std::vector<AStar::Node> finalPath;  // Unnessary (for now)

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

float grid_size = 10;
int grid_width = 30;
int grid_height = 30;
bool running = false;
unsigned path_length = 0;

AStar::Node::Node(ImVec2 pos, Node *parent) {
	this->pos = pos;
	this->parent = parent;
	this->generation = (parent == NULL) ? 0 : parent->generation + 1;
}

double AStar::Node::ComputeDistanceToEnd() {
	// End is global
	ImVec2 distance = Utils::v_abs(pos - end_pos);
	distance *= distance;
	this->distance = distance.x + distance.y;
	return this->distance;
}

double AStar::Node::ComputeScore() {
	// Side effect. Computes score
	this->score = ComputeDistanceToEnd() + this->generation;
	return this->score;
}

bool AStar::Node::operator<(double other) {
	return this->score < other;
}

void AStar::Setup() {
	// May need to do more things here
	running = true;
	toConsider.push_back(Node(start_pos, NULL));
	path_length = 0;
}

void AStar::Stop() {
	// Prepare for next session.
	running = false;
	toConsider.clear();
	considered.clear();
}

void AStar::Tick() {
	// Manages everything necessary in one step of the astar algorithm
	if (toConsider.size() == 0) {
		// Nothing more to consider, therefore there is no path.
		// IDEA: Highlight closest node to the end (maybe with the path to that node?)
		Stop();
		return;
	}
	// FIXME: Use pop_back instead of front and, using math, reverse the insertions (effectively reversing the list, putting the best element last)
	// FIXME: Quick fix (and a bit dirty) would be to change the toConsider object from a vector to a list, as that would increase front removal times.
	// FIXME: But, a list is slower than a vector (src: https://stackoverflow.com/questions/2209224/vector-vs-list-in-stl#comment20988874_2209224).
	// FIXME: If I have time, the aforementioned "maths" should take care of everything. Wow, Java doesn't have ANY of these problems!
	Node thisConsider = toConsider.front();
	toConsider.erase(toConsider.begin());
	if (Utils::Equal(thisConsider.pos, end_pos)) {
		CalculatePath(&thisConsider);
		Stop();
		return;
	}
	considered.push_back(thisConsider);  // Because we know that we want to consider it, put it in the array now.
	SetSquareAt(thisConsider.pos, GridSquare_Considered);
	ImVec2 directions[] = {
		ImVec2(-1,-1),ImVec2(0,-1),ImVec2(1,-1),
		ImVec2(-1, 0),		   ImVec2(1, 0),
		ImVec2(-1, 1),ImVec2(0, 1),ImVec2(1, 1)
	};
	// OR (for only up, down, left & right)
	/* 
	ImVec2 directions[] = {
			      ImVec2(0,-1),
		ImVec2(-1, 0),		   ImVec2(1, 0),
			      ImVec2(0, 1)
	};
	 */
	for (size_t i = 0; i < IM_ARRAYSIZE(directions); i++) {
		ImVec2 next_pos = thisConsider.pos + directions[i];
		if (InvalidPos(next_pos))
			continue;
		if (GetSquareAt(next_pos) == GridSquare_None || GetSquareAt(next_pos) == GridSquare_End)
			// Pointers O.O
			// The funny thing below is intentional. If we store a reference to thisConsider
			// then when it gets deleted (alongside some other stuff) we actually have a
			// stale reference. Update: This would work... except we are using vectors!
			// ARRGH! Ah well, at least I have STL (cough cough C) and all I need to do is
			// change a word or two... hopefully!
			AddToConsider(Node(next_pos, &considered.back()));
	}
	// Preservation
	SetSquareAt(start_pos, GridSquare_Start);
	SetSquareAt(end_pos, GridSquare_End);
}

void AStar::CalculatePath(Node *from) {
	while (from != NULL) {
		// The start node will have a NULL parent. Then, we stop.
		GridSquare there = GetSquareAt(from->pos);
		if (there != GridSquare_Start && there != GridSquare_End) {
			SetSquareAt(from->pos, GridSquare_Path);
			path_length++;
		}
		from = from->parent;
	}
	return;
}

void AStar::AddToConsider(AStar::Node toAdd) {
	double score = toAdd.ComputeScore();
	std::vector<Node>::iterator index = std::lower_bound(toConsider.begin(), toConsider.end(), score);
	SetSquareAt(toAdd.pos, GridSquare_ToConsider);
	toConsider.insert(index, toAdd);
}

bool AStar::InvalidPos(ImVec2 pos) 			{ return pos.x < 0 || pos.x >= grid_width || pos.y < 0 || pos.y >= grid_height; }

ImVec2 AStar::GetGridLocationUnderMouse() 		{ ImVec2 v = (mouse_pos - grid_pos) / grid_size; return ImVec2((int) v.x, (int) v.y); }

AStar::GridSquare AStar::GetSquareAt(ImVec2 pos) 	{ return grid[pos.y][pos.x]; }

void AStar::SetSquareAtMouse(AStar::GridSquare type) 	{ SetSquareAt(GetGridLocationUnderMouse(), type); }

void AStar::SetSquareAt(ImVec2 pos, AStar::GridSquare type) {
	// Pos is the PIXEL COORDINATE in the grid. Small checks for whether it's actually in the grid are in order, though.
	if (pos.x > grid_width || pos.y > grid_height)
		return;
	grid[pos.y][pos.x] = type;
}

void AStar::DrawGrid() 					{ DrawGrid(grid_pos, ImVec2(grid_size, grid_size)); }

void AStar::DrawGrid(ImVec2 pos) 			{ DrawGrid(pos, ImVec2(grid_size, grid_size)); }

void AStar::DrawGrid(float size) 			{ DrawGrid(grid_pos, ImVec2(size, size)); }

void AStar::DrawGrid(ImVec2 pos, float size) 		{ DrawGrid(pos, ImVec2(size, size)); }

void AStar::DrawGrid(ImVec2 pos, ImVec2 size) {
	// Draws the grid to the current window, with the top-left corner at `pos'
	static ImU32 this_col;
	ImDrawList *draw_list = ImGui::GetWindowDrawList();
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			switch (grid[i][j]) {
				case GridSquare_None:		this_col = ImColor(col_none);
								break;
				case GridSquare_Wall:		this_col = ImColor(col_wall);
								break;
				case GridSquare_Start:		this_col = ImColor(col_start);
								break;
				case GridSquare_End:		this_col = ImColor(col_end);
								break;
				case GridSquare_Path:		this_col = ImColor(col_path);
								break;
				case GridSquare_Considered:	this_col = ImColor(col_considered);
								break;
				case GridSquare_ToConsider:	this_col = ImColor(col_toConsider);
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
			if (Utils::Random() <= (double) rate && grid[i][j] == GridSquare_None)
				grid[i][j] = GridSquare_Wall;
		}
	}
}

void AStar::ClearGrid() {
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == GridSquare_Wall)
				grid[i][j] = GridSquare_None;
		}
	}
}

size_t AStar::ClearGridOf(GridSquare toClear) {
	size_t count;  // If this isn't enough, I'm not writing `unsigned long long' everywhere lol
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == toClear) {
				grid[i][j] = GridSquare_None;
				count++;
			}
		}
	}
	return count;
}

void AStar::UpdateWindow(bool *open) {
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
	//static const int min = 1;
	//static const int max = 100;
	static float rate = 0.25f;

	static bool startsetting = false;
	static bool exclusivemode = false;
	// static bool auto = false;  // TODO

	col_none		= ImVec4(0.0f, 0.0f, 0.0f, 1.0f);  // #000000FF Black
	col_wall		= ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // #FF0000FF Red
	col_start		= ImVec4(1.0f, 0.0f, 1.0f, 1.0f);  // #FF00FFFF Purple
	col_end			= ImVec4(1.0f, 1.0f, 0.0f, 1.0f);  // #FFFF00FF Yellow
	col_path		= ImVec4(0.0f, 0.0f, 1.0f, 1.0f);  // #0000FFFF Blue
	col_considered		= ImVec4(1.0f, 0.5f, 0.0f, 1.0f);  // #FF7800FF Orange
	col_toConsider		= ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // #00FF00FF Green

	ImGuiIO &io = ImGui::GetIO();
	if (ImGui::IsKeyPressed(550) && io.KeyShift)	// 550 = e
		exclusivemode ^= 1;

	if (ImGui::IsKeyPressed(564) && io.KeyShift)	// 564 = s
		startsetting ^= 1;

	if (ImGui::IsKeyPressed(562) && io.KeyShift)	// 562 = q
		*open = false;

	if (ImGui::IsKeyPressed(563) && io.KeyShift) {	// 563 = r
		Stop();
		ClearGridOf(GridSquare_Path);
		ClearGridOf(GridSquare_Considered);
		ClearGridOf(GridSquare_ToConsider);
	}

	if (ImGui::IsKeyPressed(553) && io.KeyShift)	// 553 = h
		ImGui::OpenPopup("Keybinds");

	if (ImGui::IsKeyPressed(548))			// 548 = c
		ClearGrid();

	if (ImGui::IsKeyPressed(564) && !io.KeyShift)	// 564 = s
		Setup();

	if (ImGui::IsKeyPressed(551))			// 551 = f
		FillGrid(rate);

	if (ImGui::IsKeyPressed(565))			// 565 = t
		Tick();

	if (ImGui::IsKeyPressed(561) && running)	// 561 = p
		running = false;

	if (ImGui::IsKeyPressed(554))			// 554 = i
	{ Setup(); running = false; }

	if (!exclusivemode) {
		if (ImGui::TreeNode("Keybinds")) {
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

			ImGui::TreePop();
		}

		ImGui::ColorEdit4("Empty"	, &col_none.x);
		ImGui::ColorEdit4("Wall"	, &col_wall.x);
		ImGui::ColorEdit4("Start"	, &col_start.x);
		ImGui::ColorEdit4("End"		, &col_end.x);
		ImGui::ColorEdit4("Path"	, &col_path.x);
		ImGui::ColorEdit4("Considered"	, &col_considered.x);
		ImGui::ColorEdit4("To consider"	, &col_toConsider.x);

		ImGui::Separator();

		ImGui::PushID("Resets");
		if (ImGui::Button("Reset##1"))
			grid_width = 30;
		ImGui::SameLine();
		if (ImGui::Button("Reset##2"))
			grid_height = 30;
		ImGui::SameLine();
		if (ImGui::Button("Reset##3"))
			rate = 0.25f;
		ImGui::SameLine();
		if (ImGui::Button("Reset##4"))
			grid_size = 10;
		ImGui::PopID();

		ImGui::PushID("Vertical Sliders");
		ImGui::VSliderInt("##1", ImVec2(43, 160), &grid_width, 1, 100, "%i");
		if (ImGui::IsItemActive() || ImGui::IsItemHovered())
			ImGui::SetTooltip("Height of grid (default: 30)");
		ImGui::SameLine();
		ImGui::VSliderInt("##2", ImVec2(43, 160), &grid_height, 1, 100, "%i");
		if (ImGui::IsItemActive() || ImGui::IsItemHovered())
			ImGui::SetTooltip("Width of grid (default: 30)");
		ImGui::SameLine();
		ImGui::VSliderFloat("##3", ImVec2(43, 160), &rate, 0.0f, 1.0f, "%.3f");
		if (ImGui::IsItemActive() || ImGui::IsItemHovered())
			ImGui::SetTooltip("Fill rate (default: 0.25)");
		ImGui::SameLine();
		ImGui::VSliderFloat("##4", ImVec2(43, 160), &grid_size, 1.0f, 20.0f, "%.0f");
		if (ImGui::IsItemActive() || ImGui::IsItemHovered())
			ImGui::SetTooltip("Square size (default: 10)");
		ImGui::PopID();

		if (ImGui::Button("Fill grid"))
			FillGrid(rate);
		ImGui::SameLine();
		if (ImGui::Button("Clear grid"))
			ClearGridOf(GridSquare_Wall);
		ImGui::SameLine();
		ImGui::Checkbox("Setting start?", &startsetting);

		if (running) {
			ImGui::BeginDisabled();
			ImGui::Button("Start");
			ImGui::EndDisabled();
			Tick();
		}
		else
			if (ImGui::Button("Start"))
				Setup();
		ImGui::SameLine();  // In each branch of the `if' above, we -- guaranteed -- have a button.
		if (ImGui::Button("Reset algorithm")) {
			Stop();  // Handles most things, but in this case we also want to clear stuff.
			ClearGridOf(GridSquare_Path);
			ClearGridOf(GridSquare_Considered);
			ClearGridOf(GridSquare_ToConsider);
		}
	}

	if (ImGui::BeginPopup("Keybinds")) {
		// Yanked from keybinds tree above and should be synced with that tree.
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
		ImGui::EndPopup();
	}

	// Note: ImGui guarantees (enough for me at least) that grid_height won't ever be >100.
	// I can add an assert or a check if really needed.
	if ((size_t) grid_height != grid.size()) {
		grid.resize(grid_height);
		for (size_t i = 0; i < grid.size(); i++) {
			grid[i].resize(grid_width);
		}
	}
	if ((size_t) grid_width != grid[0].size()) {
		for (size_t i = 0; i < grid.size(); i++) {
			grid[i].resize(grid_width);
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
				for (size_t i = 0; i < grid.size(); i++) {
					for (size_t j = 0; j < grid[i].size(); j++) {
						if (grid[i][j] == GridSquare_Start)
							grid[i][j] = GridSquare_None;
					}
				}
				SetSquareAtMouse(GridSquare_Start);
				start_pos = under_mouse;
			}
			else
				SetSquareAtMouse(GridSquare_Wall);
		}
		else if (ImGui::IsMouseDown(1)) {
			// Right clicked
			if (startsetting) {
				// Make sure there is only one start and end and update start_pos
				for (size_t i = 0; i < grid.size(); i++) {
					for (size_t j = 0; j < grid[i].size(); j++) {
						if (grid[i][j] == GridSquare_End)
							grid[i][j] = GridSquare_None;
					}
				}
				SetSquareAtMouse(GridSquare_End);
				end_pos = under_mouse;
			}
			else
				SetSquareAtMouse(GridSquare_None);
		}
	}

	if (!InvalidPos(under_mouse) && GetSquareAt(under_mouse) == GridSquare_Path && !running) {
		// There are only paths after having ran the algorithm at least once.
		// IDEA: Get score of toConsider node (on demand as there is no easy way to query every frame)
		ImGui::SetTooltip("Path length: %u", path_length);
	}

	DrawGrid();

	if (!exclusivemode && ImGui::Button("Close"))
		*open = false;

	ImGui::PopStyleVar();
	ImGui::End();
}

