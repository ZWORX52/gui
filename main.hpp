// NOLINT(legal/copyright)
#pragma once

#define IMGUI_USER_CONFIG "../gui/imgui_config.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS
#endif

#ifdef WINDOWS
#include <Windows.h>
#include <wincrypt.h>
#else
#include <sys/syscall.h>
#include <linux/random.h>
#endif

#include <GLFW/glfw3.h>  // Will drag system OpenGL headers

#include <functional>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <bitset>
#include <vector>
#include <random>
#include <cctype>
#include <stack>
#include <list>

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/imgui_internal.h"

#define BUFFER_SIZE 2048
#define LARGE_BUFFER_SIZE 32768

// Function prototypes & namespaces
namespace WordleEncryption {
        void UpdateWindow(bool *open);
        int EncryptFilter(ImGuiInputTextCallbackData* data);
        void Encrypt(char in[], char out[]);
        void Decrypt(char in[], char out[]);
        void UpdateInfoWindow(bool *open);
};  // namespace WordleEncryption

namespace Utils {
        void ClearBuffer(char buf[]);
        void ClearBuffer(unsigned char buf[]);
        void SeedPRNG();
        double Random();
        ImVec2 v_abs(ImVec2 __val);
        bool v_eq(ImVec2 __a, ImVec2 __b);
};  // namespace Utils

namespace Origins {
        void UpdateWindow(bool *open);
        void UpdateLoadWindow(bool *open);
        void UpdateEditWindow(bool *open);
};  // namespace Origins

namespace AStar {
enum GridSquare {
        GridSquare_None                 = 0,
        GridSquare_Wall                 = 1,
        GridSquare_Start                = 2,
        GridSquare_End                  = 3,
        GridSquare_Path                 = 4,
        GridSquare_Considered           = 5,
        GridSquare_ToConsider           = 6
};

class Node {
 public:
        ImVec2 pos;
        int generation;
        Node *parent;  // Stored in grid
        double stored_distance;
        double stored_score;
        // bool real_type;

        GridSquare type;
        // IDEA: (Temporary) visual-only type to show paths, maybe triggered with a flag
        // (boolean) that says whether to show real type?
        GridSquare virtual_type;

        explicit Node(ImVec2 new_pos);  // Casting from an ImVec2... No. Don't do it. Why would you?
        double ComputeDistanceToEnd();
        double ComputeScore();
};

void            UpdateWindow(bool *open);
void            ShowKeybinds();
void            SetSquareAtMouse(GridSquare type);
void            SetSquareAt(ImVec2 pos, GridSquare type);
Node*           GetSquareAt(ImVec2 pos);
ImVec2          GetGridLocationUnderMouse();
void            DrawGrid();
void            DrawGrid(float size);
void            DrawGrid(ImVec2 pos);
void            DrawGrid(ImVec2 pos, float size);
void            DrawGrid(ImVec2 pos, ImVec2 size);
void            FillGrid(double rate);
void            ClearGrid();
size_t          ClearGridOf(GridSquare toClear);
bool            InvalidPos(ImVec2 pos);
bool            Comp(Node *left, double right);
// Actual algorithm functions
void            Tick();
void            CalculatePath(Node *from);
void            CalculateTempPath(Node *from);
void            AddToConsider(Node *toAdd, Node *parent);
void            Setup();
void            Stop();
};  // namespace AStar

namespace BF {
class Log {
 public:
         ImGuiTextBuffer buf;
         // TODO(ZWORX52): add filter
};
enum LogType {
        LogType_Update,                 // For informing user on updates on program run state
        LogType_Note,                   // For giving no-severity comments/notes to the user
        LogType_Warn,                   // For telling the user: "this CAN be here, but shouldn't really"
        LogType_Error                   // For telling the user, bluntly: "This can't be here. Deal with it."
};

void                            UpdateWindow(bool *open);
int                             Tick();
void                            Setup();
void                            Stop();
int                             Verify();
};  // namespace BF

namespace Images {
void                            UpdateWindow(bool *open);
ImVec2                          GetCoordsAtMouse();
std::vector<bool>::reference    GetAt(ImVec2 pos);
void                            Display();
bool                            InvalidPos(ImVec2 coords);
void                            Encode();
void                            Encode(char *dst);
void                            ClearImage();
void                            Decode();
void                            Decode(char *src);
void                            ResizeImage();
};  // namespace Images

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
        Block Piece[4][4];
        Block Type;
        ImVec2 Pos;
        int ShadowDistanceDown;
        int Rotation;

        Tetromino(Block type, ImVec2 pos, int rotation);
        Tetromino();
        void Write(std::vector<std::vector<Block>> &board);
        void Erase(std::vector<std::vector<Block>> &board);
        bool IsValid(std::vector<std::vector<Block>> &board);
        void UpdatePiece();
        bool Move(float amount, std::vector<std::vector<Block>> &board);
        bool MoveDown(float amount, std::vector<std::vector<Block>> &board);
        bool RotateClockwise(std::vector<std::vector<Block>> &board);
        bool RotateCounterClockwise(std::vector<std::vector<Block>> &board);
        bool Rotate180(std::vector<std::vector<Block>> &board);
        void UpdateShadowDistanceDown(std::vector<std::vector<Block>> &board);
        void HardDrop();
};

class Board {
 public:
        std::vector<std::vector<Tetris::Block>> Matrix;
        Tetris::Tetromino PlayTetromino;
        // Tetris::Block HeldTetromino;
        // std::vector<Tetris::Block> Bag;
        ImVec2 Pos;
        ImVec2 Block_Size;
        ImVec4 col_None;
        ImVec4 col_I;
        ImVec4 col_J;
        ImVec4 col_L;
        ImVec4 col_O;
        ImVec4 col_S;
        ImVec4 col_T;
        ImVec4 col_Z;

        ImVec4 col_I_Shadow;
        ImVec4 col_J_Shadow;
        ImVec4 col_L_Shadow;
        ImVec4 col_O_Shadow;
        ImVec4 col_S_Shadow;
        ImVec4 col_T_Shadow;
        ImVec4 col_Z_Shadow;

        float DAS;  // Delay before the key repeat, in frames
        float DAS_timer;
        bool prev_frame_dir_key_pressed;  // Whether the previous frame had a directional key pressed
        float DCD;  // Delay before switching DAS directions, if the user presses the opposite key
        float ARR;  // Key repeat rate, measured in frames per movement
        float ARR_timer;

        Board(ImVec2 size, ImVec2 pos, ImVec2 block_size);
        void Draw(ImVec2 pos);
        void CalculateInputs();
};

void                            UpdateWindow(bool *open);
void                            DrawGrid();
};  // namespace Tetris

