//#include "CBezierDrawing.h"
//
//CBezierDrawing::CBezierDrawing(GLFWwindow* window, const int width, const int height, std::vector<Point>& points, double resolution, int& selectedPoint, double pointsize)
//	:m_window(window)
//    ,m_height(height)
//    ,m_width(width)
//    ,m_curveResolution(resolution)
//    ,m_points(points)
//    ,m_selectedPoint(selectedPoint)
//    ,m_pointSize(pointsize)
//{
//}
//
//
//void CBezierDrawing::Start()
//{
//
//    while (!glfwWindowShouldClose(m_window)) {
//        Draw();
//        glfwPollEvents();
//    }
//    glfwTerminate();
//}
//
//void CBezierDrawing::DrawCoordinateAxes() {
//    glBegin(GL_LINES);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex2f(-m_width / 2, 0);
//    glVertex2f(m_width / 2, 0);
//
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex2f(0, -m_height / 2);
//    glVertex2f(0, m_height / 2);
//    glEnd();
//}
//
//void CBezierDrawing::DrawControlPoints() {
//    glColor3f(0.0, 0.0, 1.0);
//    glPointSize(m_pointSize);
//
//    glBegin(GL_POINTS);
//    for (int i = 0; i < 4; ++i) {
//        glVertex2f(m_points[i].x, m_points[i].y);
//    }
//    glEnd();
//}
//
//void CBezierDrawing::DrawBezierCurve() {
//    glColor3f(0.0, 1.0, 1.0);
//    glBegin(GL_LINE_STRIP);
//
//    for (int i = 0; i <= m_curveResolution; ++i) {
//        double t = i / m_curveResolution;
//
//        double x = pow(1 - t, 3) * m_points[0].x +
//            3 * pow(1 - t, 2) * t * m_points[1].x +
//            3 * (1 - t) * pow(t, 2) * m_points[2].x +
//            pow(t, 3) * m_points[3].x;
//
//        double y = pow(1 - t, 3) * m_points[0].y +
//            3 * pow(1 - t, 2) * t * m_points[1].y +
//            3 * (1 - t) * pow(t, 2) * m_points[2].y +
//            pow(t, 3) * m_points[3].y;
//
//        glVertex2f(x, y);
//    }
//
//    glEnd();
//}
//
//void CBezierDrawing::DrawDashedLines() {
//    glColor3f(0.5, 0.5, 0.5);
//    glLineStipple(1, 0xAAAA);
//    glEnable(GL_LINE_STIPPLE);
//
//    glBegin(GL_LINES);
//    for (int i = 0; i < 3; ++i) {
//        glVertex2f(m_points[i].x, m_points[i].y);
//        glVertex2f(m_points[i + 1].x, m_points[i + 1].y);
//    }
//    glEnd();
//
//    glDisable(GL_LINE_STIPPLE);
//}
//
//void CBezierDrawing::Draw() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    DrawBezierCurve();
//    DrawCoordinateAxes();
//    DrawControlPoints();
//    DrawDashedLines();
//
//    glfwSwapBuffers(glfwGetCurrentContext());
//}
//
