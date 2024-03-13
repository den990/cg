#include "Smesharik.h"

Smesharik::Smesharik(Point center, GLFWwindow* window)
	: m_window(window)
	, m_rectMax({ -FLT_MAX, -FLT_MAX })
	, m_rectMin({ FLT_MAX, FLT_MAX })
{
}

void Smesharik::Draw()
{
	m_rectMax = { -FLT_MAX, -FLT_MAX };
	m_rectMin = { FLT_MAX, FLT_MAX };
	DrawBody(); 
	DrawLeftEar();
	DrawRightEar();
	DrawLeftHand();
	DrawRightHand();
	DrawEyes();
	DrawNose();
	DrawMouth(); 
	DrawLeftLeg();
	DrawRightLeg();
	DrawDashedRectangle();
}

bool Smesharik::isDrag()
{
	return m_isDragging;
}

Point Smesharik::GetPosition()
{
	return m_position;
}

void Smesharik::SetPosition(Point point)
{
	m_position = point;
}


void Smesharik::SetDrag(bool drag)
{
	m_isDragging = drag;
}

void Smesharik::SetWindow(GLFWwindow* window)
{
	m_window = window;
}

bool Smesharik::IsClickInside(Point point)
{
	if (point.x > m_rectMax.x || point.y > m_rectMax.y || point.x < m_rectMin.x || point.y < m_rectMin.y)
	{
		return false;
	}
	return true;
}

void Smesharik::DrawBody()
{
	glColor3f(0.17f, 0.67f, 0.89f);
	glBegin(GL_TRIANGLE_FAN); 

	float radius = 40.0f;
	int numSegments = 100;

	glVertex2f(0.0f, 0.0f); 

	for (int i = 0; i <= numSegments; ++i) {
		float theta = 2.0f * M_PI * float(i) / float(numSegments); 
		float x = radius * cosf(theta); 
		float y = radius * sinf(theta); 

		glVertex2f(x + m_position.x, y + m_position.y);
		FindMaxAndMinPoint({ x + m_position.x, y + m_position.y });
	}

	glEnd(); 


	radius = 38.0f;
	glLineWidth(3.0f);  
	glColor3f(0.0f, 0.0f, 0.0f); 
	glBegin(GL_LINE_LOOP);  

	for (int i = 0; i <= numSegments; ++i) {
		float theta = 2.0f * M_PI * float(i) / float(numSegments);
		float x = (radius + 2.0f) * cosf(theta);  
		float y = (radius + 2.0f) * sinf(theta);

		glVertex2f(x + m_position.x, y + m_position.y);
		FindMaxAndMinPoint({ x + m_position.x, y + m_position.y });
	}

	glEnd();
	glLineWidth(1.0f); 
}

void Smesharik::DrawLeftEar()
{
	DrawBezierCurve(controlPointsForLeftEar1);

	DrawBezierCurve(controlPointsForLeftEar2);
}

void Smesharik::DrawRightEar()
{
	
	DrawBezierCurve(controlPointsForRightEar1);

	DrawBezierCurve(controlPointsForRightEar2);

}

void Smesharik::DrawLeftHand()
{
	DrawBezierCurve(controlPointsForLeftHand1);

	DrawBezierCurve(controlPointsForLeftHand2);

	DrawBezierCurve(controlPointsForLeftHand3);

	DrawBezierCurve(controlPointsForLeftHand4);

}

void Smesharik::DrawRightHand()
{

	DrawBezierCurve(controlPointsForRightHand1);

	DrawBezierCurve(controlPointsForRightHand2);

	//DrawPixels(controlPointsFirst, controlPointsSecond);

	DrawBezierCurve(controlPointsForRightHand3);

	DrawBezierCurve(controlPointsForRightHand4);
}

void Smesharik::DrawEyes()
{
	std::vector<float> whiteColor = { 1, 1, 1 };
	std::vector<float> blackColor = { 0, 0, 0 };

	DrawEllipse(12, 15, 10, 13, 100, whiteColor, TYPE_FILL);
	DrawEllipse(-12, 15, 10, 13, 100, whiteColor, TYPE_FILL);

	DrawCircle(-8, 15, 5, 100, blackColor);
	DrawCircle(8, 15, 5, 100, blackColor);

	DrawCircle(-5, 15, 2, 100, whiteColor);
	DrawCircle(5, 15, 2, 100, whiteColor);


}

void Smesharik::DrawNose()
{
	std::vector<float> redColor = { 1, 0, 0 };
	DrawCircle(0, 7, 4, 100, redColor);
}

void Smesharik::DrawMouth()
{
	std::vector<float> redColor = { 0, 0, 0 };
	Point a = { 0, 3 }, b = { 0, -3 };
	DrawLine(a, b, redColor);

	DrawBezierCurve(controlPointsForMouth1);

	DrawBezierCurve(controlPointsForMouth2);

	DrawBezierCurve(controlPointsForMouth3);

	DrawTeeths();
}

void Smesharik::DrawTeeths()
{
	std::vector<float> whiteColor = { 1, 1, 1 };

	DrawHalfEllipse(-2, -3.5f, 2, 4, 100, whiteColor, TYPE_FILL);
	DrawHalfEllipse(2, -3.5f, 2, 4, 100, whiteColor, TYPE_FILL);
}

void Smesharik::DrawLeftLeg()
{
	std::vector<float> blackColor = { 0, 0, 0 };
	std::vector<float> blueColor = { 0.17f, 0.67f, 0.89f };
	DrawEllipse(-16, -45, 15, 7, 100, blueColor, TYPE_FILL);
	DrawEllipse(-16, -45, 15, 7, 100, blackColor, TYPE_OUTLINE);
}

void Smesharik::DrawRightLeg()
{
	std::vector<float> blackColor = { 0, 0, 0 };
	std::vector<float> blueColor = { 0.17f, 0.67f, 0.89f };
	DrawEllipse(16, -45, 15, 7, 100, blueColor, TYPE_FILL);
	DrawEllipse(16, -45, 15, 7, 100, blackColor, TYPE_OUTLINE);
}

void Smesharik::DrawBezierCurve(const std::vector<Point> controlPoints) {
	glLineWidth(3.0f);
	glColor3f(0, 0, 0);  
	glBegin(GL_LINE_STRIP);

	double curveResolution = 100.0;
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

		glVertex2f(x + m_position.x, y + m_position.y);
		FindMaxAndMinPoint({ static_cast<float>(x) + m_position.x, static_cast<float>(y) + m_position.y });
	}

	glEnd();
}

void Smesharik::DrawCircle(float centerX, float centerY, float radius, int segments, std::vector<float>& color) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color[0], color[1], color[2]); 
	glVertex2f(centerX + m_position.x, centerY + m_position.y);

	for (int i = 0; i <= segments; ++i) {
		float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
		float x = centerX + radius * cosf(theta);
		float y = centerY + radius * sinf(theta);
		glVertex2f(x + m_position.x, y + m_position.y);
		FindMaxAndMinPoint({ x + m_position.x, y + m_position.y });
	}

	glEnd();
}

void Smesharik::DrawEllipse(float centerX, float centerY, float radiusA, float radiusB, int segments, std::vector<float>& color, int type) {
	if (type == TYPE_FILL)
	{
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(color[0], color[1], color[2]); 
		glVertex2f(centerX + m_position.x, centerY + m_position.y);

		for (int i = 0; i <= segments; ++i) {
			float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
			float x = centerX + radiusA * cosf(theta);
			float y = centerY + radiusB * sinf(theta);
			glVertex2f(x + m_position.x, y + m_position.y);
			FindMaxAndMinPoint({ x + m_position.x, y + m_position.y });
		}

		glEnd();
	}
	else if (type == TYPE_OUTLINE)
	{
		glLineWidth(3.0f);
		glBegin(GL_LINE_LOOP);
		glColor3f(color[0], color[1], color[2]); 
		for (int i = 0; i < segments; ++i) {
			float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
			float x = centerX + radiusA * cosf(theta);
			float y = centerY + radiusB * sinf(theta);
			glVertex2f(x + m_position.x, y + m_position.y);
			FindMaxAndMinPoint({ x + m_position.x, y + m_position.y });
		}
		glEnd();
	}
}

void Smesharik::DrawHalfEllipse(float centerX, float centerY, float radiusA, float radiusB, int segments, std::vector<float>& color, int type)
{
	int halfSegments = segments / 2;
	if (type == TYPE_FILL)
	{
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(color[0], color[1], color[2]); 
		glVertex2f(centerX + m_position.x, centerY + m_position.y);


		for (int i = halfSegments; i <= segments; ++i) {
			float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
			float x = centerX + radiusA * cosf(theta);
			float y = centerY + radiusB * sinf(theta);
			glVertex2f(x + m_position.x, y + m_position.y);
			FindMaxAndMinPoint({ x + m_position.x, y + m_position.y });
		}

		glEnd();
	}
	else if (type == TYPE_OUTLINE)
	{
		glLineWidth(3.0f);
		glBegin(GL_LINE_LOOP);
		glColor3f(color[0], color[1], color[2]);
		for (int i = halfSegments; i <= segments; ++i) {
			float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
			float x = centerX + radiusA * cosf(theta);
			float y = centerY + radiusB * sinf(theta);
			glVertex2f(x + m_position.x, y + m_position.y);
			FindMaxAndMinPoint({ x + m_position.x, y + m_position.y });
		}
		glEnd();
	}
}

void Smesharik::DrawLine(Point& a, Point& b, std::vector<float>& color)
{
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f(a.x + m_position.x, a.y + m_position.y);
	glVertex2f(b.x + m_position.x, b.y + m_position.y);
	glEnd();
}

void Smesharik::FindMaxAndMinPoint(Point point)
{
	if (point.x > m_rectMax.x)
	{
		m_rectMax.x = point.x;
	}

	if (point.y > m_rectMax.y)
	{
		m_rectMax.y = point.y;
	}

	if (point.x < m_rectMin.x)
	{
		m_rectMin.x = point.x;
	}

	if (point.y < m_rectMin.y)
	{
		m_rectMin.y = point.y;
	}
}

void Smesharik::DrawDashedRectangle() {
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x00FF);  // 0x00FF - шаблон для пунктира

	glColor3f(1.0f, 0.0f, 0.0f);  // Красный цвет
	glLineWidth(2.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(m_rectMax.x, m_rectMax.y);
	glVertex2f(m_rectMin.x, m_rectMax.y);
	glVertex2f(m_rectMin.x, m_rectMin.y);
	glVertex2f(m_rectMax.x, m_rectMin.y);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}




//сделать функцию от типа заливка или контур, и под углом

//void Smesharik::DrawPixels(std::vector<Point>& controlPointsFirst, std::vector<Point>& controlPointsSecond)
//{
//	size_t size;
//	if ((size = controlPointsFirst.size()) == controlPointsSecond.size() && size > 0)
//	{
//		float minX, maxX, minY, maxY;
//		minX = maxX = controlPointsFirst[0].x;
//		minY = maxY = controlPointsFirst[0].y;
//
//		FindMinMaxXY(controlPointsFirst, minX, maxX, minY, maxY);
//
//		// Обновить минимумы и максимумы для второго массива точек
//		FindMinMaxXY(controlPointsSecond, minX, maxX, minY, maxY);
//
//		GLubyte pixel[3]; // RGB значения пикселя будут сохранены здесь
//		glBegin(GL_POINTS);
//		for (float a = minX; a <= maxX; a++)
//		{
//			for (float b = minY; b <= maxY; b++)
//			{
//				glReadPixels(a, b, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
//				if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) {
//					// Если цвет пикселя белый, замените на другой цвет
//					glColor3f(0.17, 0.67, 0.89);
//					glVertex2f(a, b);
//				}
//			}
//		}
//		glEnd();
//	}
//}
//
//void Smesharik::FindMinMaxXY(const std::vector<Point>& controlPoints, float& minX, float& maxX, float& minY, float& maxY) {
//
//	for (const Point& point : controlPoints) {
//		minX = std::min(minX, point.x);
//		maxX = std::max(maxX, point.x);
//		minY = std::min(minY, point.y);
//		maxY = std::max(maxY, point.y);
//	}
//}