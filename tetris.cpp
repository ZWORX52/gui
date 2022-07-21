// NOLINT(legal/copyright)
// #include "./main.hpp"
#include "tetris/tetris.hpp"
#include "tetris/impl.hpp"


namespace Tetris {

#include "tetris/block_states.hpp"

Tetromino::Tetromino(Block type, ImVec2 pos, int rotation = 0) {
        this->Pos = pos;
        this->Rotation = rotation;
        this->Type = type;
        memcpy(this->Piece, Block_States[type][rotation], sizeof(Block_States[type][rotation]));
}

Tetromino::Tetromino() {
        // This has to exist because Board::Board calls this when it first runs for some reason, even though I call
        // Tetromino() with arguments later in Board::Board.
        this->Pos = ImVec2(0, 0);
        this->Rotation = 0;
        this->Type = Block_I;
        memcpy(this->Piece, Block_States[Block_I][0], sizeof(Block_States[Block_I][0]));
}

void Tetromino::Write(std::vector<std::vector<Block>> &board) {
        int x = static_cast<int>(this->Pos.x);
        int y = static_cast<int>(this->Pos.y);
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        if (x + j >= 0 && x + j < static_cast<int>(board[0].size()) &&
                                        y + i >= 0 && y + i < static_cast<int>(board.size()) &&
                                        this->Piece[i][j] != Block_None) {
                                board.at(y + i).at(x + j) = this->Piece[i][j];
                        }
                        // Write shadow pos to board using the same logic as above.
                        if (x + j >= 0 && x + j < static_cast<int>(board[0].size()) && y + i - this->ShadowDistanceDown >= 0
                                        && y + i - this->ShadowDistanceDown < static_cast<int>(board.size()) &&
                                        this->Piece[i][j] != Block_None) {
                                board.at(y + i - this->ShadowDistanceDown).at(x + j) = static_cast<Block>(this->Piece[i][j] + Block_Shadow + 1);
                        }
                }
        }
}

void Tetromino::Erase(std::vector<std::vector<Block>> &board) {
        int x = static_cast<int>(this->Pos.x);
        int y = static_cast<int>(this->Pos.y);
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        if (x + j >= 0 && x + j < static_cast<int>(board[0].size()) &&
                                        y + i >= 0 && y + i < static_cast<int>(board.size()) &&
                                        this->Piece[i][j] != Block_None) {
                                board.at(y + i).at(x + j) = Block_None;
                        }
                        // Erase shadow blocks using the same logic as above.
                        if (x + j >= 0 && x + j < static_cast<int>(board[0].size()) && y + i - this->ShadowDistanceDown >= 0
                                        && y + i - this->ShadowDistanceDown < static_cast<int>(board.size()) &&
                                        this->Piece[i][j] != Block_None) {
                                board.at(y + i - this->ShadowDistanceDown).at(x + j) = Block_None;
                        }
                }
        }
}

void Tetromino::UpdateShadowDistanceDown(std::vector<std::vector<Block>> &board) {
        int x = static_cast<int>(this->Pos.x);
        int y = static_cast<int>(this->Pos.y);
        int min_distance_down = 0;
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        int distance_down = 0;
                        while (y + i - distance_down >= 0 &&
                                        board.at(y + i - distance_down).at(x + j) == Block_None) {
                                distance_down++;
                        }
                        if (distance_down < min_distance_down || min_distance_down == 0) {
                                min_distance_down = distance_down;
                        }
                }
        }
        this->ShadowDistanceDown = min_distance_down;
}

void Tetromino::HardDrop() {
        // Use the shadow distance down to move the piece the correct number of spaces down.
        this->Pos.y -= this->ShadowDistanceDown;
        this->ShadowDistanceDown = 0;
}

bool Tetromino::RotateClockwise(std::vector<std::vector<Block>> &board) {
        this->Rotation = (this->Rotation + 1) % 4;
        this->UpdatePiece();
        if (!this->IsValid(board)) {
                this->Rotation = (this->Rotation + 3) % 4;
                this->UpdatePiece();
                return false;
        }
        return true;
}

bool Tetromino::RotateCounterClockwise(std::vector<std::vector<Block>> &board) {
        this->Rotation = (this->Rotation + 3) % 4;
        this->UpdatePiece();
        if (!this->IsValid(board)) {
                this->Rotation = (this->Rotation + 1) % 4;
                this->UpdatePiece();
                return false;
        }
        return true;
}

bool Tetromino::Rotate180(std::vector<std::vector<Block>> &board) {
        this->Rotation = (this->Rotation + 2) % 4;
        this->UpdatePiece();
        if (!this->IsValid(board)) {
                this->Rotation = (this->Rotation + 2) % 4;
                this->UpdatePiece();
                return false;
        }
        return true;
}

void Tetromino::UpdatePiece() {
        memcpy(this->Piece, Block_States[this->Type][this->Rotation], sizeof(Block_States[this->Type][this->Rotation]));
}

bool Tetromino::IsValid(std::vector<std::vector<Block>> &board) {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        if (this->Piece[i][j] != Block_None && (this->Pos.x + j < 0 || this->Pos.x + j >= board[0].size() ||
                                        this->Pos.y + i < 0 || this->Pos.y + i >= board.size() ||
                                        board.at(this->Pos.y + i).at(this->Pos.x + j) != Block_None)) {
                                return false;
                        }
                }
        }
        return true;
}

bool Tetromino::Move(float amount, std::vector<std::vector<Block>> &board) {
        this->Pos.x += amount;
        if (!this->IsValid(board)) {
                this->Pos.x -= amount;
                return false;
        }
        return true;
}

bool Tetromino::MoveDown(float amount, std::vector<std::vector<Block>> &board) {
        this->Pos.y += amount;
        if (!this->IsValid(board)) {
                this->Pos.y -= amount;
                return false;
        }
        return true;
}

Board::Board(ImVec2 size, ImVec2 pos, ImVec2 block_size) {
        this->Matrix = std::vector<std::vector<Block>>(size.y, std::vector<Block>(size.x, Block_None));
        this->PlayTetromino = Tetromino(Block_I, ImVec2(1, 1), 0);
        this->PlayTetromino.UpdateShadowDistanceDown(this->Matrix);
        this->Pos = pos;
        this->Block_Size = block_size;
        this->col_None = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
        this->col_I    = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
        this->col_J    = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
        this->col_L    = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
        this->col_O    = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        this->col_S    = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        this->col_T    = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
        this->col_Z    = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        // Make the shadow colors as the same as the main colors but with 0.5 alpha.
        this->col_I_Shadow    = ImVec4(0.0f, 1.0f, 1.0f, 0.5f);
        this->col_J_Shadow    = ImVec4(0.0f, 0.0f, 1.0f, 0.5f);
        this->col_L_Shadow    = ImVec4(1.0f, 0.5f, 0.0f, 0.5f);
        this->col_O_Shadow    = ImVec4(1.0f, 1.0f, 0.0f, 0.5f);
        this->col_S_Shadow    = ImVec4(0.0f, 1.0f, 0.0f, 0.5f);
        this->col_T_Shadow    = ImVec4(1.0f, 0.0f, 1.0f, 0.5f);
        this->col_Z_Shadow    = ImVec4(1.0f, 0.0f, 0.0f, 0.5f);
        // Initialize timers to zero
        this->ARR_timer = 0.0f;
        this->DAS_timer = 0.0f;
        this->prev_frame_dir_key_pressed = false;
}

void Board::Draw(ImVec2 pos) {
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
                                case Block_I_Shadow:
                                        this_col = ImColor(this->col_I_Shadow);
                                        break;
                                case Block_J_Shadow:
                                        this_col = ImColor(this->col_J_Shadow);
                                        break;
                                case Block_L_Shadow:
                                        this_col = ImColor(this->col_L_Shadow);
                                        break;
                                case Block_O_Shadow:
                                        this_col = ImColor(this->col_O_Shadow);
                                        break;
                                case Block_S_Shadow:
                                        this_col = ImColor(this->col_S_Shadow);
                                        break;
                                case Block_T_Shadow:
                                        this_col = ImColor(this->col_T_Shadow);
                                        break;
                                case Block_Z_Shadow:
                                        this_col = ImColor(this->col_Z_Shadow);
                                        break;
                                default:
                                        this_col = ImColor(this->col_None);
                                        break;
                        };
                        ImVec2 square_pos = pos + ImVec2(j * this->Block_Size.x,
                                        (this->Matrix.size() - i) * this->Block_Size.y);
                        // std::cout << "Square pos: " << square_pos.x << " " << square_pos.y << std::endl;
                        draw_list->AddRectFilled(square_pos, square_pos + this->Block_Size, this_col);
                }
        }
        ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + this->Matrix.size() * this->Block_Size.y + 4));
}

void Board::CalculateInputs() {
        bool hard_dropped = false;
        if (ImGui::IsKeyPressed(ImGuiKey_Space)) {
                this->PlayTetromino.Erase(this->Matrix);
                this->PlayTetromino.HardDrop();
                this->PlayTetromino.Write(this->Matrix);
                hard_dropped = true;
        }

        bool right_dir_key_pressed = ImGui::IsKeyDown(ImGuiKey_RightArrow);
        bool movement_key_pressed = right_dir_key_pressed || ImGui::IsKeyDown(ImGuiKey_LeftArrow);
        if (movement_key_pressed) {
                // Handle movement
                // For debug, print every branch
                if (this->prev_frame_dir_key_pressed) {
                        // TODO(ZWORX52): Handle DCD if necessary, otherwise just go to the ARR loop (after this if
                        // statement)
                        if (hard_dropped && DAS_timer == 0) {  // If we hard dropped last frame AND were ARR-ing
                                this->ARR_timer = 0;
                                this->DAS_timer = this->DCD;
                        } else if (this->DAS_timer >= 1) {
                                this->DAS_timer--;
                        } else if (this->ARR_timer == 0) {  // Leave the ARR timer alone if it's timer-ing
                                this->ARR_timer = this->DAS_timer;
                                this->DAS_timer = 0;
                        }
                } else {
                        this->ARR_timer = 0;
                        this->DAS_timer = this->DAS;
                        this->PlayTetromino.Move(right_dir_key_pressed ? 1 : -1, this->Matrix);
                }
                if (this->DAS_timer == 0) {
                        this->ARR_timer--;
                }
                this->prev_frame_dir_key_pressed = true;
                /*
                 *std::cout << "ARR: " << this->ARR << " DAS: " << this->DAS << " DCD: " << this->DCD << " DAS_timer: " <<
                 *        this->DAS_timer << " ARR_timer: " << this->ARR_timer << " hard_dropped: " << hard_dropped <<
                 *        " right_dir_key_pressed: " << right_dir_key_pressed << std::endl;
                 */
        } else {
                this->prev_frame_dir_key_pressed = false;
        }
        while (movement_key_pressed && this->DAS_timer == 0 && this->ARR_timer < 1) {
                this->ARR_timer += this->ARR;
                this->PlayTetromino.Move(right_dir_key_pressed ? 1 : -1, this->Matrix);
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

        ImGui::Begin("Tetris", open, flags);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 4));

        static float ARR = 0.5f;
        static float DAS = 5.0f;
        static float DCD = 0.0f;

        ImGui::SliderFloat("ARR", &ARR, 5.0f, 0.0f);
        ImGui::SliderFloat("DAS", &DAS, 20.0f, 0.0f);
        ImGui::SliderFloat("DCD", &DCD, 20.0f, 0.0f);


        static Board test(ImVec2(10, 20), ImGui::GetCursorScreenPos(), ImVec2(10, 10));
        ImGui::ColorEdit4("I Shadow Color", (float *)&test.col_I_Shadow);
        test.ARR = ARR;
        test.DAS = DAS;
        test.DCD = DCD;
        test.PlayTetromino.Erase(test.Matrix);
        test.PlayTetromino.UpdateShadowDistanceDown(test.Matrix);
        test.CalculateInputs();
        test.PlayTetromino.Write(test.Matrix);
        test.Draw(ImGui::GetCursorScreenPos());

        ImGui::PopStyleVar();
        ImGui::End();
}


};  // namespace Tetris

