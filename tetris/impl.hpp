// NOLINT(legal/copyright)

#define IMGUI_USER_CONFIG "../gui/imgui_config.h"

// I'm actually surprised
// wow only vector!!!
#include <vector>

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/imgui_internal.h"

namespace Tetris {
enum Block {
        Block_I,
        Block_J,
        Block_L,
        Block_O,
        Block_S,
        Block_T,
        Block_Z,
        Block_Shadow,  // Add this (and one) to a normal block to make it a shadow block
        Block_I_Shadow,
        Block_J_Shadow,
        Block_L_Shadow,
        Block_O_Shadow,
        Block_S_Shadow,
        Block_T_Shadow,
        Block_Z_Shadow,
        Block_None
};

class Tetromino {
 public:
        Block                   Piece[4][4];
        Block                   Type;
        ImVec2                  Pos;
        int                     ShadowDistanceDown;
        int                     Rotation;

                                Tetromino(Block type, ImVec2 pos, int rotation);
                                Tetromino();
        void                    Write(std::vector<std::vector<Block>> &board);
        void                    Erase(std::vector<std::vector<Block>> &board);
        bool                    IsValid(std::vector<std::vector<Block>> &board);
        void                    UpdatePiece();
        bool                    Move(float amount, std::vector<std::vector<Block>> &board);
        bool                    MoveDown(float amount, std::vector<std::vector<Block>> &board);
        bool                    RotateClockwise(std::vector<std::vector<Block>> &board);
        bool                    RotateCounterClockwise(std::vector<std::vector<Block>> &board);
        bool                    Rotate180(std::vector<std::vector<Block>> &board);
        void                    UpdateShadowDistanceDown(std::vector<std::vector<Block>> &board);
        void                    HardDrop();
};

class Board {
 public:
        std::vector<std::vector<Tetris::Block>>
                                Matrix;
        Tetris::Tetromino       PlayTetromino;
        // Tetris::Block HeldTetromino;
        // std::vector<Tetris::Block> Bag;
        ImVec2                  Pos;
        ImVec2                  Block_Size;
        ImVec4                  col_None;
        ImVec4                  col_I;
        ImVec4                  col_J;
        ImVec4                  col_L;
        ImVec4                  col_O;
        ImVec4                  col_S;
        ImVec4                  col_T;
        ImVec4                  col_Z;

        ImVec4                  col_I_Shadow;
        ImVec4                  col_J_Shadow;
        ImVec4                  col_L_Shadow;
        ImVec4                  col_O_Shadow;
        ImVec4                  col_S_Shadow;
        ImVec4                  col_T_Shadow;
        ImVec4                  col_Z_Shadow;

        float                   DAS;  // Delay before the key repeat, in frames
        float                   DAS_timer;
        bool                    prev_frame_dir_key_pressed;  // Whether the previous frame had a directional key pressed
        float                   DCD;  // Delay before switching DAS directions, if the user presses the opposite key
        float                   ARR;  // Key repeat rate, measured in frames per movement
        float                   ARR_timer;

                                Board(ImVec2 size, ImVec2 pos, ImVec2 block_size);
        void                    Draw(ImVec2 pos);
        void                    CalculateInputs();
};

void                            DrawGrid();
};

