// NOLINT(legal/copyright)
#include "./main.hpp"


namespace Tetris {

Block Block_States[7][4][4][4] = {
{
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_I, Block_I, Block_I, Block_I},
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_I, Block_None},
                {Block_None, Block_None, Block_I, Block_None},
                {Block_None, Block_None, Block_I, Block_None},
                {Block_None, Block_None, Block_I, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_None, Block_None, Block_None},
                {Block_I, Block_I, Block_I, Block_I},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_I, Block_None, Block_None},
                {Block_None, Block_I, Block_None, Block_None},
                {Block_None, Block_I, Block_None, Block_None},
                {Block_None, Block_I, Block_None, Block_None}
        }
},
{
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_J, Block_None, Block_None, Block_None},
                {Block_J, Block_J, Block_J, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_J, Block_J, Block_None},
                {Block_None, Block_J, Block_None, Block_None},
                {Block_None, Block_J, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_None, Block_None, Block_None},
                {Block_J, Block_J, Block_J, Block_None},
                {Block_None, Block_None, Block_J, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_J, Block_None, Block_None},
                {Block_None, Block_J, Block_None, Block_None},
                {Block_J, Block_J, Block_None, Block_None}
        }
},
{
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_None, Block_L, Block_None},
                {Block_L, Block_L, Block_L, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_L, Block_None, Block_None},
                {Block_None, Block_L, Block_None, Block_None},
                {Block_None, Block_L, Block_L, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_None, Block_None, Block_None},
                {Block_L, Block_L, Block_L, Block_None},
                {Block_L, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_L, Block_L, Block_None, Block_None},
                {Block_None, Block_L, Block_None, Block_None},
                {Block_None, Block_L, Block_None, Block_None}
        }
},
{
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_O, Block_O, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        }
},
{
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_S, Block_S, Block_None},
                {Block_S, Block_S, Block_None, Block_None},
                {Block_None, Block_None, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_S, Block_None, Block_None},
                {Block_None, Block_S, Block_S, Block_None},
                {Block_None, Block_None, Block_S, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_None, Block_None, Block_None},
                {Block_None, Block_S, Block_S, Block_None},
                {Block_S, Block_S, Block_None, Block_None}
        },
        {
                {Block_None, Block_None, Block_None, Block_None},
                {Block_S, Block_None, Block_None, Block_None},
                {Block_S, Block_S, Block_None, Block_None},
                {Block_None, Block_S, Block_None, Block_None}
        }
}
};

Tetromino::Tetromino(Block type, ImVec2 pos, int rotation = 0) {
        this->Pos = pos;
        this->Rotation = rotation;
        this->Type = type;
        memcpy(this->Piece, Block_States[type][rotation], sizeof(Block_States[type][rotation]));
}

void Tetromino::Display() {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        std::cout << this->Piece[i][j] << " ";
                }
                std::cout << std::endl;
        }
}

void Tetromino::Rotate() {
        this->Rotation = (this->Rotation + 1) % 4;
        memcpy(this->Piece, Block_States[this->Type][this->Rotation], sizeof(Block_States[this->Type][this->Rotation]));
}

Board::Board(ImVec2 size, ImVec2 pos, ImVec2 block_size) {
        this->Matrix = std::vector<std::vector<Block>>(size.y, std::vector<Block>(size.x, Block_None));
        this->PlayTetromino = Tetromino(Block_I, ImVec2(1, 1));
        this->Pos = pos;
        this->Block_Size = block_size;
        this->col_None = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        this->col_I    = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
        this->col_J    = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
        this->col_L    = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
        this->col_O    = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        this->col_S    = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        this->col_T    = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
        this->col_Z    = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
}

void Board::Draw() {
        static ImU32 this_col;
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        for (size_t i = 0; i < this->Matrix.size(); i++) {
                for (size_t j = 0; j < this->Matrix[i].size(); j++) {
                        switch (this->Matrix[i][j]) {
                                case Block_None:
                                        this_col = ImColor(this->col_None);
                                        break;
                                case Block_I:
                                        this_col = ImColor(this->col_I);
                                        break;
                                case Block_J:
                                        this_col = ImColor(this->col_J);
                                        break;
                                case Block_L:
                                        this_col = ImColor(this->col_L);
                                        break;
                                case Block_O:
                                        this_col = ImColor(this->col_O);
                                        break;
                                case Block_S:
                                        this_col = ImColor(this->col_S);
                                        break;
                                case Block_T:
                                        this_col = ImColor(this->col_T);
                                        break;
                                case Block_Z:
                                        this_col = ImColor(this->col_Z);
                                        break;
                        };
                        // I'm making the origin top left, although the kick tables disagree. Ah well, seems like we'll
                        // be fighting them when they come :shrug: (aka it's a problem for future me)
                        ImVec2 square_pos = this->Pos + ImVec2(j * this->Block_Size.x, i * this->Block_Size.y);
                        draw_list->AddRectFilled(square_pos, square_pos + this->Block_Size, this_col);
                }
        }
        ImGui::SetCursorScreenPos(ImVec2(this->Pos.x, this->Pos.y + this->Matrix.size() * this->Block_Size.y + 4));
}

void UpdateWindow(bool *open) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_NoDecoration;
        flags |= ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoResize;

        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        static Tetromino test(Block_L, ImVec2(0, 0));
        test.Display();
        test.Rotate();
        std::cout << test.Type << std::endl;
        std::cout << test.Rotation << std::endl;

        ImGui::Begin("Tetris", open, flags);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 4));

        ImGui::Text("TODO");

        ImGui::PopStyleVar();
        ImGui::End();
}

};  // namespace Tetris

