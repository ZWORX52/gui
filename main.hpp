#pragma once

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cmath>

#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <memory>
#include <list>

#include <sys/syscall.h>
#include <linux/random.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
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
	void SeedCSPRNG();
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
	class Node {
		public:
			ImVec2 pos;
			int generation;
			Node *parent;
			double distance;
			double score;

			Node(ImVec2 pos, Node *parent);
			double ComputeDistanceToEnd();
			double ComputeScore();
			bool operator<(double other);
	};

	enum GridSquare {
		GridSquare_None			= 0,
		GridSquare_Wall			= 1,
		GridSquare_Start		= 2,
		GridSquare_End			= 3,
		GridSquare_Path			= 4,
		GridSquare_Considered		= 5,
		GridSquare_ToConsider		= 6
	};

	void 		UpdateWindow(bool *open);
	void 		SetSquareAtMouse(GridSquare type);
	void 		SetSquareAt(ImVec2 pos, GridSquare type);
	GridSquare 	GetSquareAt(ImVec2 pos);
	ImVec2		GetGridLocationUnderMouse();
	void 		DrawGrid();
	void 		DrawGrid(float size);
	void 		DrawGrid(ImVec2 pos);
	void 		DrawGrid(ImVec2 pos, float size);
	void 		DrawGrid(ImVec2 pos, ImVec2 size);
	void 		FillGrid(double rate);
	void		ClearGrid();
	size_t		ClearGridOf(GridSquare toClear);
	bool		InvalidPos(ImVec2 pos);
	// Actual algorithm functions
	void 		Tick();
	void 		CalculatePath(Node *from);
	void		AddToConsider(Node toAdd);
	void		Setup();
	void		Stop();
}

