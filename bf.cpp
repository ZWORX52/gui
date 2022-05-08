// NOLINT(legal/copyright)
#include "./main.hpp"

namespace BF {

// TODO: support null characters in the output

#define MEM_SIZE 30000

std::stack<char*> loop_starts;

// c strings yaaaaaaaaaaaaaaaaaaaaaaaaaay
char            prgm[BUFFER_SIZE]       = { 0 };
unsigned char   output[BUFFER_SIZE]     = { 0 };
char            input[BUFFER_SIZE]      = { 0 };
unsigned char   memory[MEM_SIZE]        = { 0 };

char            *prgm_p                 = NULL;
unsigned char   *out_p                  = NULL;
char            *in_p                   = NULL;
unsigned char   *p                      = NULL;
unsigned char   *mem_end                = NULL;

bool setup = false;
bool done = false;

void Setup() {
        if (!setup) {
                Utils::ClearBuffer(memory);
                Utils::ClearBuffer(output);

                prgm_p  = prgm;
                out_p   = output;
                in_p    = input;
                p       = memory;
                mem_end = memory + MEM_SIZE - 1;
                setup   = true;
        }
}

void Stop() {
        if (setup) {
                prgm_p  = NULL;
                out_p   = NULL;
                in_p    = NULL;
                p       = NULL;
                mem_end = NULL;
                setup   = false;
                done    = false;
        }
}

int Verify() {
        // Checks if bf_prgm is valid, i.e. if all parenthesis are matched.
        int depth = 0;
        char *tmp_prgm_p = prgm;
        while (*tmp_prgm_p) {
                if (*tmp_prgm_p == '[') depth++;
                else if (*tmp_prgm_p == ']') depth--;
                tmp_prgm_p++;
        }
        return depth;
}

int Tick() {
        // Ticks program.
        switch (*prgm_p) {
                case '>' : ++p;
                           if (p >= mem_end) p = memory;
                           break;
                case '<' : --p;
                           if (p < memory) p = mem_end;
                           break;
                case '+' : ++*p;
                           break;
                case '-' : --*p;
                           break;
                case '.' : *out_p++ = *p;
                           break;
                case ',' :  // check if we actually have characters to read
                           if (!*in_p) {
                                   // Input character is a null byte,
                                   // therefore the end of input is reached. Return 1.
                                   return 1;
                           }
                           *p = *in_p++;
                           break;
                case '[' :  // slow down there we should skip the loop if *bf_p = 0
                           if (!*p)
                                   prgm_p = strchr(prgm_p, ']');  // WE CAN ASSUME THERE WILL BE AN END BRACKET!!!
                           loop_starts.push(prgm_p - 1);  // (maybe, if I get the verifier working)
                           break;
                case ']' : if (loop_starts.empty()) {
                                   break;
                           }
                           if (*p) {  // back to start of loop
                                   prgm_p = loop_starts.top();
                           }
                           loop_starts.pop();
                           break;
                case '\0': done = true;
                           break;
                default:
                           break;
        }
        return 0;
}

void UpdateWindow(bool *open) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("Brain____", open, flags);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 4));

        ImGui::InputTextMultiline("Program", prgm, BUFFER_SIZE);
        ImGui::InputTextMultiline("Input", input, BUFFER_SIZE);
        ImGui::Text("Output: %s", output);
        if (ImGui::Button("Run program")) {
                if (!setup)
                        Setup();
                while (*prgm_p) {
                        if (Tick()) {
                                // If there was an error (currently only if input ran out)
                                // Stop running the program and inform the user.
                                // TODO(ZWORX52): Log
                        }
                        prgm_p++;
                }
                if (done)
                        Stop();
        }

        ImGui::SameLine();
        if (setup && !done && ImGui::Button("Tick")) {
                Tick();
                prgm_p++;
        } else if (!setup && ImGui::Button("Setup")) {
                Setup();
        } else if (done && ImGui::Button("Stop")) {
                Stop();
        }

        static int count;
        if (ImGui::Button("Verify"))
                count = Verify();
        ImGui::SameLine();
        ImGui::Text("count = %i", count);

        ImGui::PopStyleVar();
        ImGui::End();
}

}  // namespace BF
