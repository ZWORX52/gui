#include "main.hpp"

enum GridSquare {
	GridSquare_None			= 0,
	GridSquare_Wall			= 1,
	GridSquare_Start		= 2,
	GridSquare_End			= 3,
	GridSquare_Path			= 4,
	GridSquare_Considered		= 5,
	GridSquare_ToConsider		= 6
};

std::vector<std::vector<GridSquare>> grid;
const int min = 1;
const int max = 100;

static ImVec4 col_none;
static ImVec4 col_wall;
static ImVec4 col_start;
static ImVec4 col_end;
static ImVec4 col_path;
static ImVec4 col_considered;
static ImVec4 col_toConsider;

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
			ImVec2 square_start = ImVec2(pos.x + j * size.x, pos.y + i * size.y);
			draw_list->AddRectFilled(square_start, VECTOR_ADD(square_start, size), this_col);
			//printf("%lu:%lu ", i, j);
		}
		//printf("\n");
	}
	ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + grid.size() * size.y + 4));
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

	// Width and height of the grid
	static size_t width = 3;
	static size_t height = 3;

	col_none		= ImVec4(0.0f, 0.0f, 0.0f, 1.0f);  // #000000FF Black
	col_wall		= ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // #FF0000FF Red
	col_start		= ImVec4(1.0f, 0.0f, 1.0f, 1.0f);  // #FF00FFFF Purple
	col_end			= ImVec4(1.0f, 1.0f, 0.0f, 1.0f);  // #FFFF00FF Yellow
	col_path		= ImVec4(0.0f, 0.0f, 1.0f, 1.0f);  // #0000FFFF Blue
	col_considered		= ImVec4(1.0f, 0.5f, 0.0f, 1.0f);  // #FF7800FF Orange
	col_toConsider		= ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // #00FF00FF Green

	ImGui::ColorEdit4("Empty"	, &col_none.x);
	ImGui::ColorEdit4("Wall"	, &col_wall.x);
	ImGui::ColorEdit4("Start"	, &col_start.x);
	ImGui::ColorEdit4("End"		, &col_end.x);
	ImGui::ColorEdit4("Path"	, &col_path.x);
	ImGui::ColorEdit4("Considered"	, &col_considered.x);
	ImGui::ColorEdit4("To consider"	, &col_toConsider.x);

	// static float size = 10.0f;
	// static ImVec4 colf = ImVec4(1.0f, 0.4f, 0.0f, 1.0f);

	// ImDrawList *draw_list = ImGui::GetWindowDrawList();

	// const ImVec2 pos = ImGui::GetCursorScreenPos();
	// const ImU32 col = ImColor(colf);

	// draw_list->AddRectFilled(pos, ImVec2(pos.x + size, pos.y + size), col);

	// ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + size + 4));  // So that it looks like ImGui spacing (4px)
	// ImGui::ColorEdit4("Color", &colf.x);
	// ImGui::DragFloat("Size", &size, 1.0f, 1.0f, 1000.0f, "%.1f", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderScalar("Width", ImGuiDataType_S32, &width, &min, &max, "%u");
        ImGui::SliderScalar("Height", ImGuiDataType_S32, &height, &min, &max, "%u");

	if (height != grid.size()) {
		// Resizing is in order! This one is simple enough.
		grid.resize(height);
		// I apparently need to reinit all of the rows. Huh!
		for (size_t i = 0; i < grid.size(); i++) {
			grid[i].resize(width);
		}
		//for (size_t i = 0; i < grid.size(); i++) {
			//for (size_t j = 0; j < grid[i].size(); j++) {
				//printf("%i ", grid[i][j]);
			//}
			//printf("\n");
		//}
	}

	if (width != grid[0].size()) {
		// Assuming two things: grid is at least one value in size, and all rows are the same size
		for (size_t i = 0; i < grid.size(); i++) {
			grid[i].resize(width);
			//printf("%lu:%lu\n", grid.size(), grid[i].size());
		}
	}

	DrawGrid(ImGui::GetCursorScreenPos(), 10);

	if (ImGui::Button("Close"))
		*open = false;

	ImGui::End();
}

