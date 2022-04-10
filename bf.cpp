// NOLINT(legal/copyright)
#include "./main.hpp"

#define MEM_SIZE 10

std::stack<char*> loop_starts;

// c strings yaaaaaaaaaaaaaaaaaaaaaaaaaay
char            prgm[BUFFER_SIZE]       = { 0 };
unsigned char   output[BUFFER_SIZE]     = { 0 };
char            input[BUFFER_SIZE]      = { 0 };
unsigned char   memory[MEM_SIZE]        = { 0 };

char *prgm_p            = NULL;
unsigned char *out_p    = NULL;
char *in_p              = NULL;
unsigned char *p        = NULL;
unsigned char *mem_end  = NULL;

bool setup = false;
bool done = false;

void BF::Setup() {
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

void BF::Stop() {
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

void BF::Tick() {
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
                case ',' : *p = *in_p;
                           break;
                case '[' : loop_starts.push(prgm_p - 1);
                           // because prgm_p will be incremented when we pop it
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
}

void BF::UpdateWindow(bool *open) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("Brain____", open, flags);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 4));

        ImGui::InputText("Program", prgm, BUFFER_SIZE);
        ImGui::InputText("Input", input, BUFFER_SIZE);
        ImGui::Text("Output: %s", output);
        if (ImGui::Button("Run program")) {
                BF::Setup();
                while (*prgm_p) {
                        BF::Tick();
                        prgm_p++;
                }
                BF::Stop();
        }

        ImGui::SameLine();
        if (setup && !done && ImGui::Button("Tick")) {
                BF::Tick();
                prgm_p++;
        } else if (!setup && ImGui::Button("Setup")) {
                BF::Setup();
        } else if (done && ImGui::Button("Stop")) {
                BF::Stop();
        }

        ImGui::End();
}

