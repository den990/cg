#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Smesharik.h"
class BaseWindow
{
public:
    BaseWindow(int w, int h, const char* title, Smesharik* smesharik)
        : m_window{ CreateWindow(w, h, title) }
        , m_smesharik(smesharik)
    {
        if (!m_window)
        {
            throw std::runtime_error("Failed to create window");
        }

        glfwMakeContextCurrent(m_window);
        m_smesharik->SetWindow(m_window);
    }
    BaseWindow(const BaseWindow&) = delete;
    BaseWindow& operator=(const BaseWindow&) = delete;

    virtual ~BaseWindow()
    {
        glfwDestroyWindow(m_window);
    }

    void Run()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            int w, h;
            glfwGetFramebufferSize(m_window, &w, &h);
            Draw(w, h, m_smesharik);
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

private:
    virtual void Draw(int width, int height, Smesharik* smesharik) = 0;

    static GLFWwindow* CreateWindow(int w, int h, const char* title)
    {
        return glfwCreateWindow(w, h, title, nullptr, nullptr);
    }

    GLFWwindow* m_window;
    Smesharik* m_smesharik;
};

class Window : public BaseWindow
{
public:
    using BaseWindow::BaseWindow;

private:
    void Draw(int width, int height, Smesharik* smesharik) override
    {
        glClearColor(0.17f, 0.67f, 0.89f, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        smesharik->Draw();
    }


};