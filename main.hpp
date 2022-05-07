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
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <random>
#include <cctype>
#include <cstdio>
#include <cmath>
#include <stack>
#include <list>

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/imgui_internal.h"

#define BUFFER_SIZE 2048

// Function prototypes & namespaces
namespace WordleEncryption {
        void UpdateWindow(bool *open);
        int EncryptFilter(ImGuiInputTextCallbackData* data);
        void Encrypt(char in[], char out[]);
        void Decrypt(char in[], char out[]);
        void UpdateInfoWindow(bool *open);
}

namespace Utils {
        void ClearBuffer(char buf[]);
        void ClearBuffer(unsigned char buf[]);
        void SeedPRNG();
        double Random();
        bool Equal(ImVec2 a, ImVec2 b);
        ImVec2 v_abs(ImVec2 __val);
}

namespace Origins {
        void UpdateWindow(bool *open);
        void UpdateLoadWindow(bool *open);
        void UpdateEditWindow(bool *open);
}

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

void UpdateWindow(bool *open);
int Tick();
void Setup();
void Stop();
int Verify();
};  // namespace BF

namespace Images {
        void                            UpdateWindow(bool *open);
        ImVec2                          GetCoordsAtMouse();
        std::vector<bool>::reference    GetAt(ImVec2 pos);
        void                            Display();
};
