// NOLINT(legal/copyright)
#include "./main.hpp"

bool seeded = false;
std::mt19937 gen;

// Yoinked with love from https://stackoverflow.com/questions/45069219/how-to-succinctly-portably-and-thoroughly-seed-the-mt19937-prng
#ifdef WINDOWS
bool acquire_context(HCRYPTPROV* ctx) {
    if (!CryptAcquireContext(ctx, nullptr, nullptr, PROV_RSA_FULL, 0)) {
        return CryptAcquireContext(ctx, nullptr, nullptr, PROV_RSA_FULL, CRYPT_NEWKEYSET);
    }
    return true;
}


size_t sysrandom(void* dst, size_t dstlen) {
    HCRYPTPROV ctx;
    if (!acquire_context(&ctx)) {
        throw std::runtime_error("Unable to initialize Win32 crypt library.");
    }

    BYTE* buffer = reinterpret_cast<BYTE*>(dst);
    if (!CryptGenRandom(ctx, dstlen, buffer)) {
        throw std::runtime_error("Unable to generate random bytes.");
    }

    if (!CryptReleaseContext(ctx, 0)) {
        throw std::runtime_error("Unable to release Win32 crypt library.");
    }

    return dstlen;
}
#else
size_t sysrandom(void* dst, size_t dstlen) {
    char* buffer = reinterpret_cast<char*>(dst);
    std::ifstream stream("/dev/urandom", std::ios_base::binary | std::ios_base::in);
    stream.read(buffer, dstlen);

    return dstlen;
}
#endif

void Utils::SeedPRNG() {
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

void Utils::ClearBuffer(unsigned char buf[]) {
        // Resets buffer to '\0' until a null byte is encountered.
        int c = 0;
        while (buf[c]) buf[c++] = '\0';
}

double Utils::Random() {
        // Call upon our good friend the PRNG (pseudo-random number generator)
        // with a lot of code yoinked from StackOverflow.
        if (!seeded)
                SeedPRNG();
#undef max
        return static_cast<double>(gen()) / static_cast<double>(gen.max());
}

ImVec2 Utils::v_abs(ImVec2 __val) {
        return ImVec2(abs(__val.x), abs(__val.y));
}

bool Utils::v_eq(ImVec2 a, ImVec2 b) {
        return a.x == b.x && a.y == b.y;
}

