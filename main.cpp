// NOLINT(legal/copyright)
#include "./main.hpp"

static void glfw_error_callback(int error, const char* description) {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) return 1;

        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        GLFWwindow *window = glfwCreateWindow(1280, 720, "Program", NULL, NULL);

        if (window == NULL) return 1;

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);  // Enable vsync

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // So we can clear the screen every frame
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        bool open = true;

        bool show_demo_window = false;

        bool show_wordle_encrypt = false;
        bool show_wordle_encrypt_info_window = false;
        bool show_origins = false;
        bool show_astar = false;

        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_MenuBar;
        flags |= ImGuiWindowFlags_AlwaysAutoResize;

        // Finally done with setup (I hope)
        // Time for some real code!
        while (!glfwWindowShouldClose(window)) {
                // Keyboard & Mouse events
                glfwPollEvents();
                // Initiate new frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                ImGui::Begin("Main window", &open, flags);

                if (ImGui::IsKeyPressed(562) &&                 // 562 = q
                                io.KeyShift && io.KeyCtrl)
                        break;

                if (ImGui::BeginMenuBar()) {
                        if (ImGui::BeginMenu("About")) {
                                if (ImGui::BeginMenu("Encryption")) {
                                        ImGui::MenuItem("Wordle info", NULL, &show_wordle_encrypt_info_window);
                                        ImGui::EndMenu();
                                }
                                ImGui::EndMenu();
                        }

                        if (ImGui::BeginMenu("Debug")) {
                                ImGui::MenuItem("Show demo window", NULL, &show_demo_window);
                                ImGui::EndMenu();
                        }

                        if (ImGui::BeginMenu("Minecraft")) {
                                ImGui::MenuItem("Origins datapack generator", NULL, &show_origins);
                                ImGui::EndMenu();
                        }

                        if (ImGui::BeginMenu("Algorithms")) {
                                ImGui::MenuItem("A* (AStar)", NULL, &show_astar);
                                ImGui::MenuItem("Wordle encryption", NULL, &show_wordle_encrypt);
                                ImGui::EndMenu();
                        }

                        ImGui::EndMenuBar();
                }

                ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);

                if (show_demo_window && ImGui::Button("Close demo window"))
                        show_demo_window = false;

                if (ImGui::Button("Exit")) {
                        break;
                }
                ImGui::End();

                if (show_wordle_encrypt)
                        WordleEncryption::UpdateWindow(&show_wordle_encrypt);

                if (show_demo_window)
                        ImGui::ShowDemoWindow();

                if (show_origins)
                        Origins::UpdateWindow(&show_origins);

                if (show_astar)
                        AStar::UpdateWindow(&show_astar);

                // Display frame
                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(window, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                                clear_color.z * clear_color.w, clear_color.w);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                glfwSwapBuffers(window);
        }
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();

        return 0;
}

