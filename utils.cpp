#include "main.h"


void Utils::ClearBuffer(char buf[]) {
	// Resets buffer to '\0' until a null byte is encountered.
	int c = 0;
	while (buf[c]) buf[c++] = '\0';
}

