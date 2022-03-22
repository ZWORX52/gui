#pragma once

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <cmath>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#define BUFFER_SIZE 1024

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
}

