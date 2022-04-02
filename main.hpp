#pragma once

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cmath>

#include <string>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#define BUFFER_SIZE 1024
#define VECTOR_ADD(v1, v2) (ImVec2(v1.x + v2.x, v1.y + v2.y))

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
}

namespace Origins {
	void UpdateWindow(bool *open);
	void UpdateLoadWindow(bool *open);
	void UpdateEditWindow(bool *open);
}

namespace AStar {
	void UpdateWindow(bool *open);
	void DrawGrid(ImVec2 pos, float size);
	void DrawGrid(ImVec2 pos, ImVec2 size);
}

