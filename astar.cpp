#include "main.hpp"

std::vector<std::vector<AStar::GridSquare>> grid;

std::vector<AStar::Node> toConsider;
std::vector<AStar::Node> considered;
std::vector<AStar::Node> finalPath;

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

void AStar::Node::ComputeScore() {
	// Side effect. Computes score
	this->score = ComputeDistanceToEnd() + this->generation;
}

void AStar::CalculatePath(Node *from) {
	// TODO
	while (from != NULL) {
		// The start node will have a NULL parent. Then, we stop.
		SetSquareAt(from->pos, GridSquare_Path);
		from = from->parent;
	}
	return;
}

void AStar::AddToBeConsidered(AStar::Node toAdd) {
	toAdd.ComputeScore();
	// TODO
}

AStar::GridSquare AStar::GetSquareAt(ImVec2 pos) {
	return grid[pos.y][pos.x];
}

void AStar::Tick() {
	// Manages everything necessary in one step of the astar algorithm
	if (toConsider.size() == 0) {
		// Nothing more to consider, therefore there is no path.
		// TODO: Highlight closest node to the end (maybe with the path to that node?)
		running = false;
		return;
	}
	Node thisConsider = toConsider.front();  // FIXME: Use pop_back instead of front and, using math, reverse the insertions (effectively reversing the list, putting the best element last)
	toConsider.erase(toConsider.begin());
	if (Utils::Equal(thisConsider.pos, end_pos)) {
		running = false;
		CalculatePath(&thisConsider);
	}
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
		if (GetSquareAt(next_pos) == GridSquare_None || GetSquareAt(next_pos) == GridSquare_End)
			AddToBeConsidered(Node(next_pos, &thisConsider));
	}
}

void AStar::SetSquareAtMouse(AStar::GridSquare type) {
	SetSquareAt((mouse_pos - grid_pos) / grid_size, type);
}

void AStar::SetSquareAt(ImVec2 pos, AStar::GridSquare type) {
	// Pos is the PIXEL COORDINATE in the grid. Small checks for whether it's actually in the grid are in order, though.
	if (pos.x > grid_width || pos.y > grid_height)
		return;
	grid[pos.y][pos.x] = type;
}

void AStar::DrawGrid() {
	DrawGrid(grid_pos, ImVec2(grid_size, grid_size));
}

void AStar::DrawGrid(ImVec2 pos) {
	DrawGrid(pos, ImVec2(grid_size, grid_size));
}

void AStar::DrawGrid(float size) {
	DrawGrid(grid_pos, ImVec2(size, size));
}

void AStar::DrawGrid(ImVec2 pos, float size) {
	DrawGrid(pos, ImVec2(size, size));
}

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

	if (ImGui::IsKeyPressed(551))			// 551 = f
		FillGrid(rate);

	if (ImGui::IsKeyPressed(548))			// 548 = c
		ClearGrid();

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

			ImGui::Text("c: Clear board");
			ImGui::Text("s: Start");
			ImGui::Text("f: Fill board");

			ImGui::TreePop();
		}

		ImGui::ColorEdit4("Empty"	, &col_none.x);
		ImGui::ColorEdit4("Wall"	, &col_wall.x);
		ImGui::ColorEdit4("Start"	, &col_start.x);
		ImGui::ColorEdit4("End"		, &col_end.x);
		ImGui::ColorEdit4("Path"	, &col_path.x);
		ImGui::ColorEdit4("Considered"	, &col_considered.x);
		ImGui::ColorEdit4("To consider"	, &col_toConsider.x);

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

		if (ImGui::Button("Fill grid"))
			FillGrid(rate);
		ImGui::SameLine();
		if (ImGui::Button("Clear grid"))
			ClearGrid();
		ImGui::SameLine();
		ImGui::Checkbox("Setting start?", &startsetting);
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
	if (io.MousePos.x > grid_pos.x && io.MousePos.x < grid_pos.x + grid_width * grid_size &&
			io.MousePos.y > grid_pos.y && io.MousePos.y < grid_pos.y + grid_height * grid_size) {
		if (ImGui::IsMouseDown(0))
			// Left clicked
			SetSquareAtMouse(startsetting ? GridSquare_Start : GridSquare_Wall);
		else if (ImGui::IsMouseDown(1))
			// Right clicked
			SetSquareAtMouse(startsetting ? GridSquare_End : GridSquare_None);
	}

	DrawGrid();

	if (!exclusivemode && ImGui::Button("Close"))
		*open = false;

	ImGui::PopStyleVar();
	ImGui::End();
}

