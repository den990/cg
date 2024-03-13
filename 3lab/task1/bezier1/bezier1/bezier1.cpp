#include <GLFW/glfw3.h>
#include <cmath>
#include <stdexcept>

const double controlPointSize = 10.0;
const double curveResolution = 100.0;

struct Point {
    double x, y;
};
//при уменьшении , центрировалась и уменьшалось
// point в class окна
Point controlPoints[4] = {
    {50.0, 50.0},
    {100.0, 200.0},
    {200.0, 250.0},
    {300.0, 100.0}
};

int selectedPoint = -1;

class GLFWInitializer final
{
public:
    GLFWInitializer()
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    GLFWInitializer(const GLFWInitializer&) = delete;
    GLFWInitializer& operator=(const GLFWInitializer&) = delete;

    ~GLFWInitializer()
    {
        glfwTerminate();
    }
};

class BaseWindow
{
public:
    BaseWindow(int w, int h, const char* title)
        : m_window{ CreateWindow(w, h, title) }
    {
        if (!m_window)
        {
            throw std::runtime_error("Failed to create window");
        }

        glfwMakeContextCurrent(m_window);
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
            Draw(w, h);
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

private:
    virtual void Draw(int width, int height) = 0;

    static GLFWwindow* CreateWindow(int w, int h, const char* title)
    {
        return glfwCreateWindow(w, h, title, nullptr, nullptr);
    }
    GLFWwindow* m_window;
};

class Window : public BaseWindow
{
public:
    using BaseWindow::BaseWindow;

private:
    void Draw(int width, int height) override
    {
        glClearColor(1.0, 1.0, 1.0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        DrawBezierCurve();
        DrawCoordinateAxes();
        DrawControlPoints();
        DrawDashedLines();
    }


    void DrawCoordinateAxes() {
        int w, h;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-w / 2, 0);
        glVertex2f(w / 2, 0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0, -h / 2);
        glVertex2f(0, h / 2);
        glEnd();
    }

    void DrawControlPoints() {
        glColor3f(0.0, 0.0, 1.0);
        glPointSize(controlPointSize);

        glBegin(GL_POINTS);
        for (int i = 0; i < 4; ++i) {
            glVertex2f(controlPoints[i].x, controlPoints[i].y);
        }
        glEnd();
    }

    void DrawBezierCurve() {
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= curveResolution; ++i) {
            double t = i / curveResolution;

            double x = pow(1 - t, 3) * controlPoints[0].x +
                3 * pow(1 - t, 2) * t * controlPoints[1].x +
                3 * (1 - t) * pow(t, 2) * controlPoints[2].x +
                pow(t, 3) * controlPoints[3].x;

            double y = pow(1 - t, 3) * controlPoints[0].y +
                3 * pow(1 - t, 2) * t * controlPoints[1].y +
                3 * (1 - t) * pow(t, 2) * controlPoints[2].y +
                pow(t, 3) * controlPoints[3].y;

            glVertex2f(x, y);
        }

        glEnd();
    }

    void DrawDashedLines() {
        glColor3f(0.5, 0.5, 0.5);
        glLineStipple(1, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);

        glBegin(GL_LINES);
        for (int i = 0; i < 3; ++i) {
            glVertex2f(controlPoints[i].x, controlPoints[i].y);
            glVertex2f(controlPoints[i + 1].x, controlPoints[i + 1].y);
        }
        glEnd();

        glDisable(GL_LINE_STIPPLE);
    }


};



void Reshape(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);
    int w, h;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
    if (width > height) {
        w = static_cast<int>(height * aspectRatio);
        h = height;
    }
    else {
        w = width;
        h = static_cast<int>(width / aspectRatio);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {

    if (selectedPoint != -1) {
        int w, h;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

        controlPoints[selectedPoint].x = xpos - w / 2;
        controlPoints[selectedPoint].y = h / 2 - ypos;
    }
}


void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int w, h;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

        for (int i = 0; i < 4; ++i) {
            double dx = xpos - (controlPoints[i].x + w / 2);
            double dy = (h / 2 - ypos) - controlPoints[i].y;
            if (sqrt(dx * dx + dy * dy) < controlPointSize) {
                selectedPoint = i;
                break;
            }
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        selectedPoint = -1;
    }
}

int main() {

    GLFWInitializer initGLFW;
    Window window{1900, 1000, "OpenGL Bezier Curve" };

    glfwMakeContextCurrent(glfwGetCurrentContext());

    glfwSetCursorPosCallback(glfwGetCurrentContext(), CursorPositionCallback);
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), MouseButtonCallback);

    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), Reshape);

    window.Run();


    glfwTerminate();
    return 0;
}
