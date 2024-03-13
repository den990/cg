#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Параметры кривой Безье
struct BezierCurve {
    ImVec2 P0, P1, P2, P3; // Контрольные точки
    std::vector<ImVec2> points; // Точки ломаной линии
};

// Инициализация кривой Безье
void InitializeBezierCurve(BezierCurve& bezierCurve) {
    // Инициализация контрольных точек
    bezierCurve.P0 = ImVec2(100, 100);
    bezierCurve.P1 = ImVec2(200, 300);
    bezierCurve.P2 = ImVec2(400, 300);
    bezierCurve.P3 = ImVec2(500, 100);

    // Вычисление точек ломаной линии
    for (float t = 0; t <= 1; t += 0.01f) {
        float u = 1.0f - t;
        float w1 = u * u * u;
        float w2 = 3 * u * u * t;
        float w3 = 3 * u * t * t;
        float w4 = t * t * t;

        float x = w1 * bezierCurve.P0.x + w2 * bezierCurve.P1.x + w3 * bezierCurve.P2.x + w4 * bezierCurve.P3.x;
        float y = w1 * bezierCurve.P0.y + w2 * bezierCurve.P1.y + w3 * bezierCurve.P2.y + w4 * bezierCurve.P3.y;

        bezierCurve.points.emplace_back(x, y);
    }
}

// Отрисовка кривой Безье и контрольных точек
void RenderBezierCurve(const BezierCurve& bezierCurve) {
    // Отрисовка кривой
    glBegin(GL_LINE_STRIP);
    for (const auto& point : bezierCurve.points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    // Отрисовка контрольных точек
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2f(bezierCurve.P0.x, bezierCurve.P0.y);
    glVertex2f(bezierCurve.P1.x, bezierCurve.P1.y);
    glVertex2f(bezierCurve.P2.x, bezierCurve.P2.y);
    glVertex2f(bezierCurve.P3.x, bezierCurve.P3.y);
    glEnd();
}

// Обработка изменения размеров окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Инициализация GLFW и создание окна
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Bezier Curve with Bonus", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Инициализация Glad для загрузки современных версий OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize Glad" << std::endl;
        return -1;
    }

    // Инициализация ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();

    // Инициализация кривой Безье
    BezierCurve bezierCurve;
    InitializeBezierCurve(bezierCurve);

    // Главный цикл приложения
    while (!glfwWindowShouldClose(window)) {
        // Обработка событий GLFW
        glfwPollEvents();

        // Начало рендеринга ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Отрисовка настроек и контроля мышью
        ImGui::Begin("Bezier Curve Settings");

        // Редактирование контрольных точек
        ImGui::SliderFloat2("P0", &bezierCurve.P0.x, 0, 800);
        ImGui::SliderFloat2("P1", &bezierCurve.P1.x, 0, 800);
        ImGui::SliderFloat2("P2", &bezierCurve.P2.x, 0, 800);
        ImGui::SliderFloat2("P3", &bezierCurve.P3.x, 0, 800);

        ImGui::End();

        // Завершение рендеринга ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Отрисовка кривой Безье
        glClear(GL_COLOR_BUFFER_BIT);
        RenderBezierCurve(bezierCurve);

        // Завершение кадра
        glfwSwapBuffers(window);
    }

    // Очистка ресурсов
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
