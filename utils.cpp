#include "main.hpp"

bool seeded = false;
std::mt19937 gen;

// Yoinked with love from https://stackoverflow.com/questions/45069219/how-to-succinctly-portably-and-thoroughly-seed-the-mt19937-prng
size_t sysrandom(void* dst, size_t dstlen) {
    char* buffer = reinterpret_cast<char*>(dst);
    std::ifstream stream("/dev/urandom", std::ios_base::binary | std::ios_base::in);
    stream.read(buffer, dstlen);

    return dstlen;
}

void Utils::SeedCSPRNG() {
	std::uint_least32_t seed;
	sysrandom(&seed, sizeof(seed));
	gen = std::mt19937(seed);
	seeded = true;
}

void Utils::ClearBuffer(char buf[]) {
	// Resets buffer to '\0' until a null byte is encountered.
	int c = 0;
	while (buf[c]) buf[c++] = '\0';
}

double Utils::Random() {
	// Call upon our friend the CSPRNG (cryptographically-secure pseudo-random number generator)
	// with a lot of code yoinked from StackOverflow.
	if (!seeded)
		SeedCSPRNG();
	return (double) gen() / gen.max();
}

ImVec2 Utils::v_abs(ImVec2 __val) {
	return ImVec2(abs(__val.x), abs(__val.y));
}

bool Utils::Equal(ImVec2 a, ImVec2 b) {
	return a.x == b.x && a.y == b.y;
}

