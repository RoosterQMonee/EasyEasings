#include "EasyEasings.hpp"

#include "DemoDependencies/imgui.h"
#include "DemoDependencies/imgui_impl_glfw.h"
#include "DemoDependencies/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // include opengl32.lib
#include <string>
#include <vector>
#include <cmath>
#include <map>


using namespace EasyEasings;

template <typename Func>
std::vector<ImVec2> Sample(Func&& func, int resolution = 200) {
    std::vector<ImVec2> points;
    for (int i = 0; i <= resolution; ++i) {
        float x = static_cast<float>(i) / resolution;
        float y = static_cast<float>(func(x));
        points.emplace_back(x, 1.0f - y); // Flip Y for top-left origin
    }
    return points;
}

int main() {
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Easing Function Demo", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::vector<std::pair<std::string, std::vector<ImVec2>>> curves = {
        { "EaseInSine", Sample(EaseInSine<float>) },
        { "EaseOutSine", Sample(EaseOutSine<float>) },
        { "EaseInOutSine", Sample(EaseInOutSine<float>) },
        { "EaseInQuad", Sample(EaseInQuad<float>) },
        { "EaseOutQuad", Sample(EaseOutQuad<float>) },
        { "EaseInOutQuad", Sample(EaseInOutQuad<float>) },
        { "EaseInCubic", Sample(EaseInCubic<float>) },
        { "EaseOutCubic", Sample(EaseOutCubic<float>) },
        { "EaseInOutCubic", Sample(EaseInOutCubic<float>) },
        { "EaseInQuart", Sample(EaseInQuart<float>) },
        { "EaseOutQuart", Sample(EaseOutQuart<float>) },
        { "EaseInOutQuart", Sample(EaseInOutQuart<float>) },
        { "EaseInQuint", Sample(EaseInQuint<float>) },
        { "EaseOutQuint", Sample(EaseOutQuint<float>) },
        { "EaseInOutQuint", Sample(EaseInOutQuint<float>) },
        { "EaseInExpo", Sample(EaseInExpo<float>) },
        { "EaseOutExpo", Sample(EaseOutExpo<float>) },
        { "EaseInOutExpo", Sample(EaseInOutExpo<float>) },
        { "EaseInCirc", Sample(EaseInCirc<float>) },
        { "EaseOutCirc", Sample(EaseOutCirc<float>) },
        { "EaseInOutCirc", Sample(EaseInOutCirc<float>) },
        { "EaseInBack", Sample(EaseInBack<float>) },
        { "EaseOutBack", Sample(EaseOutBack<float>) },
        { "EaseInOutBack", Sample(EaseInOutBack<float>) },
        { "EaseInElastic", Sample(EaseInElastic<float>) },
        { "EaseOutElastic", Sample(EaseOutElastic<float>) },
        { "EaseInOutElastic", Sample(EaseInOutElastic<float>) },
        { "EaseInBounce", Sample(EaseInBounce<float>) },
        { "EaseOutBounce", Sample(EaseOutBounce<float>) },
        { "EaseInOutBounce", Sample(EaseInOutBounce<float>) },
    };

    static bool resized = false;

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 padding = style.WindowPadding;

    constexpr int plot_width = 160;
    constexpr int plot_height = 100;
    constexpr int columns = 6;
    constexpr int rows = 6;
    constexpr int spacing_x = 8;
    constexpr int spacing_y = 7;

    int total_width = columns * plot_width + (columns - 1) * spacing_x + static_cast<int>(padding.x * 2);
    int total_height = rows * (plot_height + ImGui::GetTextLineHeight()) + (rows - 1) * spacing_y + static_cast<int>(padding.y * 2);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2((float)total_width, (float)total_height));
        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
        ImGui::Begin("Easing Function Demo", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

        if (!resized) {
            glfwSetWindowSize(window, total_width, total_height);
            resized = true;
        }

        for (size_t i = 0; i < curves.size(); ++i) {
            const auto& [name, points] = curves[i];

            ImGui::BeginGroup();
            ImGui::Text("%s", name.c_str());
            ImGui::PlotLines(
                ("##" + name).c_str(),
                [](void* data, int idx) -> float {
                    return static_cast<float>(((ImVec2*)data)[idx].y);
                },
                (void*)points.data(),
                static_cast<int>(points.size()),
                0, nullptr, -0.375f, 1.375f,
                ImVec2(160, 100)
            );
            ImGui::EndGroup();

            if ((i + 1) % columns != 0)
                ImGui::SameLine();
        }

        ImGui::End();
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}