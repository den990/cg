#pragma once
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include "const.h"

class Smesharik
{
public:
	Smesharik(Point center, GLFWwindow* window);
	void Draw();
	bool isDrag();
	void SetPosition(Point point);
	Point GetPosition();
	void SetDrag(bool drag);
	void SetWindow(GLFWwindow* window);
	bool IsClickInside(Point point);

private:
	void DrawBody();
	void DrawLeftEar();
	void DrawRightEar();
	void DrawLeftHand();
	void DrawRightHand();
	void DrawEyes(); 
	void DrawNose(); 
	void DrawMouth();
	void DrawTeeths(); 
	void DrawLeftLeg();
	void DrawRightLeg();

	//void DrawPixels(std::vector<Point>& controlPointsFirst, std::vector<Point>& controlPointsSecond);
	//void FindMinMaxXY(const std::vector<Point>& controlPoints, float& minX, float& maxX, float& minY, float& maxY);

	void DrawBezierCurve(const std::vector<Point> controlPoints);
	void DrawCircle(float centerX, float centerY, float radius, int segments, std::vector<float>& color);
	void DrawEllipse(float centerX, float centerY, float radiusA, float radiusB, int segments, std::vector<float>& color, int type);
	void DrawHalfEllipse(float centerX, float centerY, float radiusA, float radiusB, int segments, std::vector<float>& color, int type);
	void DrawLine(Point& a, Point& b, std::vector<float>& color);

	void FindMaxAndMinPoint(Point point);

	void DrawDashedRectangle();

	GLFWwindow* m_window;
	bool m_isDragging = false;
	Point m_position = { 0, 0 }, m_rectMax, m_rectMin;
};