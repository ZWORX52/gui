// NOLINT(legal/copyright)
#include "./main.hpp"

#define MEM_SIZE 30000

std::stack<char*> loop_starts;

// c strings yaaaaaaaaaaaaaaaaaaaaaaaaaay
char            bf_prgm[BUFFER_SIZE]       = { 0 };
unsigned char   bf_output[BUFFER_SIZE]     = { 0 };
char            bf_input[BUFFER_SIZE]      = { 0 };
unsigned char   bf_memory[MEM_SIZE]        = { 0 };

char            *bf_prgm_p                 = NULL;
unsigned char   *bf_out_p                  = NULL;
char            *bf_in_p                   = NULL;
unsigned char   *bf_p                      = NULL;
unsigned char   *bf_mem_end                = NULL;

bool bf_setup = false;
bool bf_done = false;

void BF::Setup() {
        if (!bf_setup) {
                Utils::ClearBuffer(bf_memory);
                Utils::ClearBuffer(bf_output);

                bf_prgm_p  = bf_prgm;
                bf_out_p   = bf_output;
                bf_in_p    = bf_input;
                bf_p       = bf_memory;
                bf_mem_end = bf_memory + MEM_SIZE - 1;
                bf_setup   = true;
        }
}

void BF::Stop() {
        if (bf_setup) {
                bf_prgm_p  = NULL;
                bf_out_p   = NULL;
                bf_in_p    = NULL;
                bf_p       = NULL;
                bf_mem_end = NULL;
                bf_setup   = false;
                bf_done    = false;
        }
}

int BF::Verify() {
        // Checks if bf_prgm is valid, i.e. if all parenthesis are matched.
        int depth = 0;
        char *p = bf_prgm;
        while (*p) {
                if (*p == '[') depth++;
                else if (*p == ']') depth--;
                p++;
        }
        return depth;
}

int BF::Tick() {
        // Ticks program.
        switch (*bf_prgm_p) {
                case '>' : ++bf_p;
                           if (bf_p >= bf_mem_end) bf_p = bf_memory;
                           break;
                case '<' : --bf_p;
                           if (bf_p < bf_memory) bf_p = bf_mem_end;
                           break;
                case '+' : ++*bf_p;
                           break;
                case '-' : --*bf_p;
                           break;
                case '.' : *bf_out_p++ = *bf_p;
                           break;
                case ',' :  // check if we actually have characters to read
                           if (!*bf_in_p) {
                                   // Input character is a null byte,
                                   // therefore the end of bf_input is reached. Return 1.
                                   return 1;
                           }
                           *bf_p = *bf_in_p++;
                           break;
                case '[' :  // slow down there we should skip the loop if *bf_p = 0
                           if (!*bf_p)
                                   bf_prgm_p = strchr(bf_prgm_p, ']');  // WE CAN ASSUME THERE WILL BE AN END BRACKET!!!
                           loop_starts.push(bf_prgm_p - 1);
                           break;
                case ']' : if (loop_starts.empty()) {
                                   break;
                           }
                           if (*bf_p) {  // back to start of loop
                                   bf_prgm_p = loop_starts.top();
                           }
                           loop_starts.pop();
                           break;
                case '\0': bf_done = true;
                           break;
                default:
                           break;
        }
        return 0;
}

void BF::UpdateWindow(bool *open) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("Brain____", open, flags);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 4));

        ImGui::InputTextMultiline("Program", bf_prgm, BUFFER_SIZE);
        ImGui::InputTextMultiline("Input", bf_input, BUFFER_SIZE);
        ImGui::Text("Output: %s", bf_output);
        if (ImGui::Button("Run program")) {
                if (!bf_setup)
                        BF::Setup();
                while (*bf_prgm_p) {
                        if (BF::Tick()) {
                                // If there was an error (currently only if bf_input ran out)
                                // Stop running the program and inform the user.
                                // TODO: Log
                        }
                        bf_prgm_p++;
                }
                if (bf_done)
                        BF::Stop();
        }

        ImGui::SameLine();
        if (bf_setup && !bf_done && ImGui::Button("Tick")) {
                BF::Tick();
                bf_prgm_p++;
        } else if (!bf_setup && ImGui::Button("Setup")) {
                BF::Setup();
        } else if (bf_done && ImGui::Button("Stop")) {
                BF::Stop();
        }

        static int count;
        if (ImGui::Button("Verify"))
                count = BF::Verify();
        ImGui::SameLine();
        ImGui::Text("count = %i", count);

        ImGui::PopStyleVar();
        ImGui::End();
}

