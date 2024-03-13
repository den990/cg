#define _USE_MATH_DEFINES
#include "Smesharik.h"
#include "Window.hpp"
#include "GLFWInitializer.hpp"
#include <iostream>

//glortho

Smesharik* smesharik = new Smesharik({ 0,0 }, NULL);

void Reshape(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);//матрица проекции
    glLoadIdentity();//в единичную матрицу, сбрасывает что было до
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height); // соотношение размеров окна
    glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    float centerX = static_cast<float>(windowWidth) / 2.0f;
    float centerY = static_cast<float>(windowHeight) / 2.0f;

    float correctedX = (xpos - centerX) * 200.0f / windowWidth * aspectRatio;
    float correctedY = (centerY - ypos) * 200.0f / windowHeight;

    if (button == GLFW_MOUSE_BUTTON_LEFT && smesharik->IsClickInside({ correctedX, correctedY })) {
        if (action == GLFW_PRESS) {
            smesharik->SetDrag(true);
        }
        else if (action == GLFW_RELEASE) {
            smesharik->SetDrag(false);
        }
    }
}

void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (smesharik->isDrag()) {

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

        float centerX = static_cast<float>(windowWidth) / 2.0f;
        float centerY = static_cast<float>(windowHeight) / 2.0f;

        float correctedX = (xpos - centerX) * 200.0f / windowWidth * aspectRatio;
        float correctedY = (centerY - ypos) * 200.0f / windowHeight;

        smesharik->SetPosition({ correctedX, correctedY });
    }
}

int main() {
    GLFWInitializer initGLFW;
    Window window{ 1900, 1000, "Smesharik", smesharik };
    glfwMakeContextCurrent(glfwGetCurrentContext());

    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), Reshape);
    glfwSetCursorPosCallback(glfwGetCurrentContext(), CursorPositionCallback);
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), MouseButtonCallback);

    window.Run();
   

    glfwTerminate();
    return 0;
}
